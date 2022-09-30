#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class EulerTour {
    public:
    EulerTour();
    int n;
    int num_edges;
    int root;
    pair<int,int> first_edge;
    vector<vector<int>> adj;
    vector<pair<int,int>> edges;
    vector<int> successor;
    vector<int> predecessor;
    unordered_map<int,int> reverse_map;
    vector<int> dist;

    void find_successors();
    void list_ranking();
    void print_successors();
    void print_tour();
};