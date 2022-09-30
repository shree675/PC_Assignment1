#include <iostream>
#include <vector>
#include <unordered_map>

#define MAX_FACTOR 1000

using namespace std;

class EulerTour {
    public:
    int n;
    int num_edges;
    // root node
    int root;
    pair<int,int> first_edge;
    vector<vector<int>> adj;
    vector<pair<int,int>> edges;
    vector<int> successor;
    vector<int> predecessor;
    /*
    * reverse map stores the reverse
    * mapping of edge numbers to
    * edges of type pair<u,v>
    */
    unordered_map<int,int> reverse_map;
    vector<int> dist;
    vector<int> tour_order;

    EulerTour();
    
    void find_successors();
    void list_ranking();
    void print_successors();
    void print_tour();
    void store_order();
};