#ifndef __LOOPYBP_H__
#define __LOOPYBP_H__

#include <vector>

using namespace std;

typedef double DATA_TYPE;

struct LBPNode
{
    vector <DATA_TYPE> data_cost;
    vector < vector<DATA_TYPE> > msg; // [neighour node id], [neighbours][labels]
    vector < pair<int,int> > send_to; // message passing schedule, neighbour + neighbour's msg box

    int best_label;
};

void RunBP(vector <LBPNode> &all_nodes, int iterations, DATA_TYPE lambda);
DATA_TYPE CalcMAPandEnergy(vector <LBPNode> &all_nodes);
void SendMsg(LBPNode &node, vector <LBPNode> &all_nodes, int t, int id);
void CreateLBPGraph(const vector < vector<int > > &connections, int num_labels, vector <LBPNode> &nodes);
DATA_TYPE SmoothnessCost(int i, int j);

#endif
