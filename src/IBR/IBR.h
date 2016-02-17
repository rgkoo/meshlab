#ifndef IBR_H
#define IBR_H
#include <opencv2/core/core.hpp>
#include <vector>
#include <string>
#include "DataStruct.h"
#include "LoopyBP.h"

namespace ibr{
	struct Camera
	{
		float focal;
		cv::Mat R, t;
		cv::Mat invK;

		float x, y, z; // position
		float nx, ny, nz; // normal

		Camera()
		{
			R = cv::Mat::zeros(3, 3, CV_32F);
			t = cv::Mat::zeros(3, 1, CV_32F);
		}
	};

	struct Face
	{
		int image_num;
		unsigned int v1, v2, v3;
		float x, y, z; // centre of triangle
		float nx, ny, nz;
		float u[3], v[4]; // texture UV coords
		std::vector <int> visible_in;
	};
	struct Point3D
	{
		float x, y, z;
		std::vector <int> visible_in;
	};

	void GetImageInfo(const std::string &filename, int &width, int &height);
	void LoadPlyMesh(const std::string &filename, std::vector<Vertex> &vertex, std::vector <Face> &face);
	void LoadBundle(const std::string &filename, std::vector <Camera> &cameras);
	bool LoadPMVSPatch(const std::string& patch_file, std::vector <Point3D> &points);
	void NormalFrom3Vertex(const Vertex &v1, const Vertex &v2, const Vertex &v3, float &nx, float &ny, float &nz);
	void AssignTexture(const std::vector <Vertex> &vertexes, const std::vector <Camera> &cameras, std::vector <Face> &faces);
	void AssignVisibleCameras(const std::vector <Vertex> &vertexes, const std::vector <Point3D> &points, const std::vector <Camera> &cameras, std::vector <Face> &faces);
	void SaveFaces(const std::string &filename, const std::vector <Face> &faces, const std::vector <Vertex> &vertexes, const std::vector <Camera> &cameras);
	void SavePoints(const std::string &filename, std::vector <Point3D> &points);
	void SaveWavefrontOBJ(const std::string &filename, const std::vector <Face> &faces, const std::vector <Vertex> &vertexes, const std::vector <Camera> &cameras);

	// Loopy BP related
	void FindGraphConnections(const std::vector <Face> &faces, const std::vector <Vertex> &vertexes, std::vector < std::vector<int> > &connections);
	void InitDataCost(const std::vector <Face> &faces, const std::vector <Camera> &cameras, std::vector <LBPNode> &nodes);
}
#endif