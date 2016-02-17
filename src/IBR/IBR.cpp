/*
Code is released under Simplified BSD License.
-------------------------------------------------------------------------------
Copyright 2012 Nghia Ho. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY NGHIA HO ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NGHIA HO OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Nghia Ho.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "DataStruct.h"
#include "ANNWrapper.h"
#include "LoopyBP.h"
#include "IBR.h"
using namespace std;

namespace ibr{
	int IMAGE_WIDTH = -1;
	int IMAGE_HEIGHT = -1;





	int main(int argc, char **argv)
	{
		vector <Camera> cameras;
		vector <Point3D> points;
		vector <Vertex> vertexes;
		vector <Face> faces;
		vector < vector<int> > connections;
		vector <LBPNode> nodes;

		if (argc != 2) {
			cout << "./TextureMesh [pmvs_dir]" << endl;
			return 0;
		}

		string data_dir = argv[1];

		GetImageInfo(data_dir + "/visualize/00000000.jpg", IMAGE_WIDTH, IMAGE_HEIGHT);
		LoadBundle(data_dir + "/bundle.rd.out", cameras);

		for (int i = 0; i < 1000; i++) {
			vector <Point3D> tmp;

			char str[256];
			sprintf(str, "%s/models/option-%04d.patch", data_dir.c_str(), i);

			FILE *fp = fopen(str, "r");

			if (fp == NULL) {
				break;
			}

			fclose(fp);

			LoadPMVSPatch(str, tmp);

			points.insert(points.end(), tmp.begin(), tmp.end());
		}

		assert(points.empty() == false);

		LoadPlyMesh(data_dir + "/models/mesh.ply", vertexes, faces);

		AssignVisibleCameras(vertexes, points, cameras, faces);

		FindGraphConnections(faces, vertexes, connections);
		CreateLBPGraph(connections, cameras.size(), nodes);
		InitDataCost(faces, cameras, nodes);
		RunBP(nodes, 5, 10.0);

		for (size_t i = 0; i < nodes.size(); i++) {
			faces[i].image_num = nodes[i].best_label;
		}

		AssignTexture(vertexes, cameras, faces);

		SaveFaces(data_dir + "/models/output.mesh", faces, vertexes, cameras);
		SavePoints(data_dir + "/models/output.point", points);
		SaveWavefrontOBJ(data_dir + "/models/output.obj", faces, vertexes, cameras);

		cout << "Done!" << endl;

		return 0;
	}

	void GetImageInfo(const string &filename, int &width, int &height)
	{
		cv::Mat img = cv::imread(filename);

		if (!img.data) {
			cerr << "Error opening " << filename << endl;
			exit(1);
		}

		width = img.cols;
		height = img.rows;
	}

	void LoadBundle(const string& filename, vector <Camera> &cameras)
	{
		ifstream bundle(filename.c_str());

		if (!bundle) {
			cerr << "LoadBundle(): Error opening " << filename << " for reading" << endl;
			exit(1);
		}

		cout << "Loading " << filename << " ... " << endl;

		stringstream str;
		char line[1024];
		int num;

		bundle.getline(line, sizeof(line)); // header
		bundle.getline(line, sizeof(line));

		str.str(line);
		str >> num;

		cameras.resize(num);

		cout << "    cameras = " << cameras.size() << endl;

		for (int i = 0; i < num; i++) {
			Camera new_camera;

			bundle.getline(line, sizeof(line)); // focal, r1, r2

			str.str(line);
			str.clear();
			str >> new_camera.focal;

			bundle.getline(line, sizeof(line)); // rotation 1
			str.str(line);
			str.clear();
			str >> new_camera.R.at<float>(0, 0);
			str >> new_camera.R.at<float>(0, 1);
			str >> new_camera.R.at<float>(0, 2);

			bundle.getline(line, sizeof(line)); // rotation 2
			str.str(line);
			str.clear();
			str >> new_camera.R.at<float>(1, 0);
			str >> new_camera.R.at<float>(1, 1);
			str >> new_camera.R.at<float>(1, 2);

			bundle.getline(line, sizeof(line)); // rotation 3
			str.str(line);
			str.clear();
			str >> new_camera.R.at<float>(2, 0);
			str >> new_camera.R.at<float>(2, 1);
			str >> new_camera.R.at<float>(2, 2);

			bundle.getline(line, sizeof(line)); // translation
			str.str(line);
			str.clear();
			str >> new_camera.t.at<float>(0, 0);
			str >> new_camera.t.at<float>(1, 0);
			str >> new_camera.t.at<float>(2, 0);

			// Camera position and normal
			{
				// http://phototour.cs.washington.edu/bundler/bundler-v0.4-manual.html
				// -R' * t
				float r[9];
				float t[3];

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						r[i * 3 + j] = new_camera.R.at<float>(i, j);
					}
				}

				for (int i = 0; i < 3; i++) {
					t[i] = new_camera.t.at<float>(i, 0);
				}

				new_camera.x = -r[6] * t[2] - r[3] * t[1] - r[0] * t[0];
				new_camera.y = -r[7] * t[2] - r[4] * t[1] - r[1] * t[0];
				new_camera.z = -r[8] * t[2] - r[5] * t[1] - r[2] * t[0];

				new_camera.nx = -r[6];
				new_camera.ny = -r[7];
				new_camera.nz = -r[8];;
			}

			cameras[i] = new_camera;
		}

		bundle.close();
	}

	bool LoadPMVSPatch(const string& patch_file, vector <Point3D> &points)
	{
		ifstream input(patch_file.c_str());

		if (!input) {
			cerr << "LoadPMVSPatch(): Error opening " << patch_file << " for reading" << endl;
			return false;
		}

		cout << "Loading " << patch_file << " ... " << endl;

		char line[2048];
		char word[128];
		stringstream str;
		int num_pts;
		float not_used;

		input.getline(line, sizeof(line)); // header
		str.str(line);
		str >> word;

		if (word != string("PATCHES")) {
			cerr << "LoadPMVSPatch(): Incorrect header" << endl;
			return false;
		}

		input.getline(line, sizeof(line)); // number of points
		str.str(line);
		str.clear();
		str >> num_pts;

		cout << "    points = " << num_pts << endl;

		points.resize(num_pts);

		for (int i = 0; i < num_pts; i++) {
			Point3D &pt = points[i];
			int num;

			input.getline(line, sizeof(line)); // another header
			assert(string(line) == "PATCHS");

			input.getline(line, sizeof(line)); // position
			str.str(line);
			str.clear();
			str >> pt.x;
			str >> pt.y;
			str >> pt.z;

			input.getline(line, sizeof(line)); // normal
			str.str(line);
			str.clear();
			str >> not_used;
			str >> not_used;
			str >> not_used;

			input.getline(line, sizeof(line)); // debugging stuff
			input.getline(line, sizeof(line)); // num images visible in
			str.str(line);
			str.clear();
			str >> num;

			assert(num > 0);

			input.getline(line, sizeof(line)); // image index
			str.str(line);
			str.clear();

			for (int j = 0; j < num; j++) {
				int idx;
				str >> idx;
				pt.visible_in.push_back(idx);
			}

			input.getline(line, sizeof(line)); // possibly visible in
			str.str(line);
			str.clear();
			str >> num;

			input.getline(line, sizeof(line)); // image index
			str.str(line);
			str.clear();

			for (int j = 0; j < num; j++) {
				int idx;
				str >> idx;
				pt.visible_in.push_back(idx);
			}

			input.getline(line, sizeof(line)); // blank line

			if (input.eof()) {
				cerr << "LoadPMVSPatch(): Premature end of file" << endl;
				return false;
			}
		}

		return true;
	}

	void SavePoints(const string &filename, vector <Point3D> &points)
	{
		ofstream output(filename.c_str());

		if (!output) {
			cerr << "Can't open " << filename << " for writing" << endl;
			exit(1);
		}

		cout << "Saving " << filename << " ..." << endl;

		output << points.size() << endl;

		for (size_t i = 0; i < points.size(); i++) {
			output.write((char*)&points[i].x, sizeof(float) * 3);
		}
	}

	void LoadPlyMesh(const string &filename, vector <Vertex> &vertexes, vector <Face> &faces)
	{
		ifstream input(filename.c_str());

		if (!input) {
			cerr << "LoadPlyMesh(): Error opening " << filename << " for reading" << endl;
			exit(1);
		}

		cout << "Loading " << filename << " ... " << endl;

		char line[1024];
		string token;

		input.getline(line, sizeof(line));
		stringstream str(line);
		str >> token;

		if (token != "ply") {
			cerr << "Not a PLY format" << endl;
			exit(1);
		}

		size_t num_vertex, num_face;
		while (input.getline(line, sizeof(line))) {
			str.str(line);
			str.clear();
			str >> token;

			if (token == "element") {
				str >> token;

				if (token == "vertex") {
					str >> num_vertex;
				}
				else if (token == "face") {
					str >> num_face;
				}
			}
			else if (token == "end_header") {
				break;
			}
		}

		cout << "    vertexes = " << num_vertex << endl;
		cout << "    faces = " << num_face << endl;

		vertexes.resize(num_vertex);
		faces.resize(num_face);

		for (size_t i = 0; i < num_vertex; i++) {
			input.getline(line, sizeof(line));
			str.str(line);
			str.clear();

			str >> vertexes[i].x;
			str >> vertexes[i].y;
			str >> vertexes[i].z;
		}

		for (size_t i = 0; i < num_face; i++) {
			int n;

			input.getline(line, sizeof(line));
			str.str(line);
			str.clear();

			str >> n;
			str >> faces[i].v1;
			str >> faces[i].v2;
			str >> faces[i].v3;

			faces[i].x = (vertexes[faces[i].v1].x + vertexes[faces[i].v2].x + vertexes[faces[i].v3].x) / 3.0;
			faces[i].y = (vertexes[faces[i].v1].y + vertexes[faces[i].v2].y + vertexes[faces[i].v3].y) / 3.0;
			faces[i].z = (vertexes[faces[i].v1].z + vertexes[faces[i].v2].z + vertexes[faces[i].v3].z) / 3.0;

			NormalFrom3Vertex(vertexes[faces[i].v1], vertexes[faces[i].v2], vertexes[faces[i].v3], faces[i].nx, faces[i].ny, faces[i].nz);
		}
	}

	void NormalFrom3Vertex(const Vertex &v1, const Vertex &v2, const Vertex &v3, float &nx, float &ny, float &nz)
	{
		float x1 = v2.x - v1.x;
		float y1 = v2.y - v1.y;
		float z1 = v2.z - v1.z;

		float x2 = v3.x - v2.x;
		float y2 = v3.y - v2.y;
		float z2 = v3.z - v2.z;

		float mag1 = sqrt(x1*x1 + y1*y1 + z1*z1);
		float mag2 = sqrt(x2*x2 + y2*y2 + z2*z2);

		x1 /= mag1;
		y1 /= mag1;
		z1 /= mag1;

		x2 /= mag2;
		y2 /= mag2;
		z2 /= mag2;

		nx = y1*z2 - z1*y2;
		ny = z1*x2 - x1*z2;
		nz = x1*y2 - y1*x2;
	}

	void AssignTexture(const vector <Vertex> &vertexes, const vector <Camera> &cameras, vector <Face> &faces)
	{
		cv::Mat X(3, 1, CV_32F);
		float cx = IMAGE_WIDTH*0.5f;
		float cy = IMAGE_HEIGHT*0.5f;

		for (size_t i = 0; i < faces.size(); i++) {
			Vertex v[3];
			v[0] = vertexes[faces[i].v1];
			v[1] = vertexes[faces[i].v2];
			v[2] = vertexes[faces[i].v3];

			// Pick the first image
			int image_num = faces[i].image_num;

			const Camera &camera = cameras[image_num];

			for (int j = 0; j < 3; j++) {
				X.at<float>(0, 0) = v[j].x;
				X.at<float>(1, 0) = v[j].y;
				X.at<float>(2, 0) = v[j].z;

				X = camera.R*X + camera.t;

				float xx = -X.at<float>(0, 0) / X.at<float>(2, 0);
				float yy = -X.at<float>(1, 0) / X.at<float>(2, 0);

				float u = (xx*camera.focal + cx) / IMAGE_WIDTH;
				float v = (yy*camera.focal + cy) / IMAGE_HEIGHT;

				// Hmm due to some numerical issue, it is possible to (u,v) that are slightly outside [0,1]
				// Will look into it when it becomes a problem!
				//assert(u >= 0 && u <= 1);
				//assert(v >= 0 && v <= 1);

				faces[i].u[j] = u;
				faces[i].v[j] = v;
			}
		}
	}

	void AssignVisibleCameras(const vector <Vertex> &vertexes, const vector <Point3D> &points, const vector <Camera> &cameras, vector <Face> &faces)
	{
		ANNWrapper ann;

		vector <Vertex> tmp(points.size());

		for (size_t i = 0; i < tmp.size(); i++) {
			tmp[i].x = points[i].x;
			tmp[i].y = points[i].y;
			tmp[i].z = points[i].z;
		}

		ann.SetPoints(tmp);

		for (size_t i = 0; i < faces.size(); i++) {
			Vertex v[3];
			v[0] = vertexes[faces[i].v1];
			v[1] = vertexes[faces[i].v2];
			v[2] = vertexes[faces[i].v3];

			Vertex c;

			c.x = (v[0].x + v[1].x + v[2].x) / 3.0;
			c.y = (v[0].y + v[1].y + v[2].y) / 3.0;
			c.z = (v[0].z + v[1].z + v[2].z) / 3.0;

			double dist2;
			int index;

			ann.FindClosest(c, &dist2, &index);

			faces[i].visible_in = points[index].visible_in;
		}
	}

	void SaveFaces(const string &filename, const vector <Face> &faces, const vector <Vertex> &vertexes, const vector <Camera> &cameras)
	{
		ofstream output(filename.c_str());

		if (!output) {
			cerr << "Can't open " << filename << " for writing" << endl;
			exit(1);
		}

		cout << "Saving " << filename << " ..." << endl;

		output << faces.size() << " " << cameras.size() << endl;

		for (size_t i = 0; i < faces.size(); i++) {
			Vertex v[3];

			v[0] = vertexes[faces[i].v1];
			v[1] = vertexes[faces[i].v2];
			v[2] = vertexes[faces[i].v3];

			for (int j = 0; j < 3; j++) {
				output << v[j].x << " ";
				output << v[j].y << " ";
				output << v[j].z << " ";
			}

			output << faces[i].image_num << " ";

			for (int j = 0; j < 3; j++) {
				output << faces[i].u[j] << " ";
				output << faces[i].v[j] << " ";
			}

			output << endl;
		}
	}

	void SaveWavefrontOBJ(const string &filename, const vector <Face> &faces, const vector <Vertex> &vertexes, const vector <Camera> &cameras)
	{
		int start = filename.find_last_of('/');
		int end = filename.find_last_of('.');
		int len = end - start;

		string base_name = filename.substr(start + 1, len - 1);
		string mtl_name = filename.substr(0, end) + ".mtl";

		ofstream output(filename.c_str());
		ofstream mtl(mtl_name.c_str());

		if (!output) {
			cerr << "Can't open " << filename << " for writing" << endl;
			exit(1);
		}

		if (!output) {
			cerr << "Can't open " << mtl_name << " for writing" << endl;
			exit(1);
		}

		cout << "Saving " << filename << " ..." << endl;
		cout << "Saving " << mtl_name << " ..." << endl;

		// MTL file
		for (size_t i = 0; i < cameras.size(); i++) {
			mtl << "newmtl Texture_" << i << endl;
			mtl << "Ka 1 1 1" << endl;
			mtl << "Kd 1 1 1" << endl;
			mtl << "Ks 0 0 0" << endl;
			mtl << "d 1.0" << endl;
			mtl << "illum 2" << endl;
			mtl << "map_Kd ../visualize/" << setfill('0') << setw(8) << i << ".jpg" << endl;
			mtl << endl;
		}

		// Writing OBJ file
		output << "mtllib " << base_name << ".mtl" << endl;

		// Write vertices
		for (size_t i = 0; i < vertexes.size(); i++) {
			output << "v " << vertexes[i].x << " " << vertexes[i].y << " " << vertexes[i].z << endl;
		}

		// Write texture coordinates, ordered by camera and face
		for (size_t c = 0; c < cameras.size(); c++) {
			for (size_t f = 0; f < faces.size(); f++) {
				if (faces[f].image_num != (int)c) {
					continue;
				}

				for (int j = 0; j < 3; j++) {
					output << "vt " << faces[f].u[j] << " " << faces[f].v[j] << endl;
				}
			}
		}

		// Write face
		int idx = 0;
		for (size_t c = 0; c < cameras.size(); c++) {
			output << "usemtl Texture_" << c << endl;
			for (size_t f = 0; f < faces.size(); f++) {
				if (faces[f].image_num != (int)c) {
					continue;
				}

				output << "f ";
				output << (faces[f].v1 + 1) << "/" << (idx + 1) << " ";
				output << (faces[f].v2 + 1) << "/" << (idx + 2) << " ";
				output << (faces[f].v3 + 1) << "/" << (idx + 3) << endl;

				idx += 3;
			}
		}
	}

	void FindGraphConnections(const vector <Face> &faces, const vector <Vertex> &vertexes, vector < vector<int> > &connections)
	{
		vector < vector <int> > vertex_face(vertexes.size() + 1);
		connections.resize(faces.size());

		// Find all the faces that share each vertex
		for (size_t i = 0; i < faces.size(); i++) {
			int v1 = faces[i].v1;
			int v2 = faces[i].v2;
			int v3 = faces[i].v3;

			vertex_face[v1].push_back(i);
			vertex_face[v2].push_back(i);
			vertex_face[v3].push_back(i);
		}

		for (size_t i = 0; i < faces.size(); i++) {
			int v1 = faces[i].v1;
			int v2 = faces[i].v2;
			int v3 = faces[i].v3;

			vector <int> shared_faces;
			vector <int>::iterator it, it2;

			shared_faces.insert(shared_faces.end(), vertex_face[v1].begin(), vertex_face[v1].end());
			shared_faces.insert(shared_faces.end(), vertex_face[v2].begin(), vertex_face[v2].end());
			shared_faces.insert(shared_faces.end(), vertex_face[v3].begin(), vertex_face[v3].end());

			sort(shared_faces.begin(), shared_faces.end());
			it2 = unique(shared_faces.begin(), shared_faces.end());

			for (it = shared_faces.begin(); it != it2; it++) {
				if (*it != (int)i) {
					connections[i].push_back(*it);
				}
			}
		}
	}

	void InitDataCost(const vector <Face> &faces, const vector <Camera> &cameras, vector <LBPNode> &nodes)
	{
		// Cost is based on face normal + direction normal to camera
		// cost = 1 - dot(face_normal, direction_normal)

		const double high_cost = 10.0;

		for (size_t i = 0; i < faces.size(); i++) {
			// Default all to high cost
			nodes[i].data_cost.assign(nodes[i].data_cost.size(), high_cost);

			for (size_t j = 0; j < faces[i].visible_in.size(); j++) {
				int idx = faces[i].visible_in[j];
				const Camera &c = cameras[idx];

				float dx = c.x - faces[i].x;
				float dy = c.y - faces[i].y;
				float dz = c.z - faces[i].z;
				float mag = sqrt(dx*dx + dy*dy + dz*dz);

				dx /= mag;
				dy /= mag;
				dz /= mag;

				// 2 normals per face
				float dot1 = faces[i].nx*dx + faces[i].ny*dy + faces[i].nz*dz;
				float dot2 = -faces[i].nx*dx - faces[i].ny*dy - faces[i].nz*dz;

				nodes[i].data_cost[idx] = 1.0 - max(dot1, dot2);
			}
		}
	}
}