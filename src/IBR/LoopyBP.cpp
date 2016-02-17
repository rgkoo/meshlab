#include "LoopyBP.h"
#include <limits>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <minmax.h>

static DATA_TYPE g_lambda = 10;

void RunBP(vector <LBPNode> &all_nodes, int iterations, DATA_TYPE lambda)
{
    g_lambda = lambda;

    // Find the node with the most connections
    int max_t = 0;

    for(size_t i=0; i < all_nodes.size(); i++) {
        max_t = max(max_t, (int)all_nodes[i].send_to.size());
    }

    cout << "Runing LoopyBP ... " << endl;

    for(int iter=0; iter < iterations; iter++) {
        for(int t=0; t < max_t; t++) {
            for(size_t k=0; k < all_nodes.size(); k++) {
                SendMsg(all_nodes[k], all_nodes, t, k);
            }
        }

        DATA_TYPE energy = CalcMAPandEnergy(all_nodes);

        cout << "    iter=" << (iter+1) << "/" << iterations << " energy=" << energy << endl;
    }
}

DATA_TYPE SmoothnessCost(int i, int j)
{
    // Simple binary cost function
    if(i == j) {
        return 0;
    }

    return g_lambda;
}

void CreateLBPGraph(const vector < vector<int > > &connections, int num_labels, vector <LBPNode> &nodes)
{
    nodes.resize(connections.size());

    for(size_t i=0; i < connections.size(); i++) {
        size_t num_neighbours = connections[i].size();
        LBPNode &cur = nodes[i];

        cur.data_cost.resize(num_labels, 0);
        cur.msg.resize(num_neighbours);
        cur.send_to.resize(num_neighbours);

        for(size_t j=0; j < num_neighbours; j++) {
            cur.send_to[j].first = -1; // -1 means 'unused'
        }
    }

    for(size_t i=0; i < connections.size(); i++) {
        size_t num_neighbours = connections[i].size();
        LBPNode &cur = nodes[i];

        for(size_t j=0; j < num_neighbours; j++) {
            int dst = connections[i][j];

            cur.msg[j].resize(num_labels, 0);

            // We want the nodes to send messages to each other at different time 't'
            int t = -1; // time this node sends to dst

            for(size_t k=0; k < cur.send_to.size(); k++) {
                if(cur.send_to[k].first == dst) {
                    t = k;
                    break;
                }
            }

            // We want adjacent messages to send at different time schedule, so they don't send to each other at the same time
            // NOTE: this does not gurantee we get different time for differerent nodes eg. only 2 faces connected to each other
            // IMPORTANT: check for dst = -1, skip if it is
            for(int k=nodes[dst].send_to.size()-1; k >= 0; k--) {
                if(k == t) {
                    continue;
                }

                if(nodes[dst].send_to[k].first == -1) {
                    nodes[dst].send_to[k] = pair<int,int>(i,j);
                    break;
                }
            }
        }
    }
}

void SendMsg(LBPNode &node, vector <LBPNode> &all_nodes, int t, int id)
{
    if(t >= (int)node.send_to.size()) {
        return;
    }

    int dst = node.send_to[t].first;
    int box = node.send_to[t].second;

    if(dst == -1) {
        return;
    }

    int num_labels = node.data_cost.size();
    vector <DATA_TYPE> new_msg(num_labels);

    // Pseudo message normalisation to prevent overflow
    // THIS IS SUPER IMPORTANT! It only takes like 2 BP iterations to overflow
    DATA_TYPE normaliser = (numeric_limits<DATA_TYPE>::max)();

    for(int i=0; i < num_labels; i++) {
        DATA_TYPE min_val = (numeric_limits<DATA_TYPE>::max)();

        for(int j=0; j < num_labels ; j++) {
            DATA_TYPE p = 0;

            p += SmoothnessCost(i,j);
            p += node.data_cost[j];

            for(size_t k=0; k < node.send_to.size(); k++) {
                // Don't return msg back to destination node
                if(t == (int)k) {
                    continue;
                }

                p += node.msg[k][j];
            }

            min_val = min(min_val, p);
        }

        new_msg[i] = min_val;

        // This is something I came up with, don't know if it's 'correct'
        normaliser = min(normaliser, min_val);
    }

    for(int i=0; i < num_labels; i++) {
        // we're implicitly working in log space, we minus the values (not divide)
        all_nodes[dst].msg[box][i] = new_msg[i] - normaliser;
    }
}

DATA_TYPE CalcMAPandEnergy(vector <LBPNode> &all_nodes)
{
    // Finds the MAP assignment as well as calculate the energy

    int num_labels = all_nodes[0].data_cost.size();

    // MAP assignment
    for(size_t i=0; i < all_nodes.size(); i++) {
        LBPNode &cur = all_nodes[i];
        DATA_TYPE best = (numeric_limits<DATA_TYPE>::max)();

        // Find the best label
        for(int j=0; j < num_labels; j++) {
            DATA_TYPE cost = cur.data_cost[j];

            for(size_t k=0; k < cur.msg.size(); k++) {
                cost += cur.msg[k][j];
            }

            if(cost < best) {
                best = cost;
                cur.best_label = j;
            }
        }
    }

    // Energy
    DATA_TYPE energy = 0;

    for(size_t i=0; i < all_nodes.size(); i++) {
        LBPNode &cur = all_nodes[i];
        int cur_label = cur.best_label;

        // Data cost
        energy += cur.data_cost[cur_label];

        for(size_t j=0; j < cur.send_to.size(); j++) {
            int dst = cur.send_to[j].first;

            if(dst == -1) {
                continue;
            }

            energy += SmoothnessCost(cur_label, all_nodes[dst].best_label);
        }
    }

    return energy;
}
