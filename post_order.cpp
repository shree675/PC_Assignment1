#include <iostream>
#include <unordered_map>
#include <vector>
#include <omp.h>
#include <cmath>
#include "euler_tour.h"

#define MAX_FACTOR 1000

using namespace std;

vector<int> tour_order;

void prefix_sum(vector<int>& weight, EulerTour et){
    int limit=(int) (log2(et.num_edges));
    omp_set_num_threads(et.num_edges);

    for(int i=0;i<limit;i++){
        vector<int> weight2(et.num_edges,-1);
        #pragma omp parallel for
        for(int j=0;j<et.num_edges;j++){
            if(j<(int) pow(2,i)){
                weight2[tour_order[j]]=weight[tour_order[j]];
            }
            else{ 
                weight2[tour_order[j]]=weight[tour_order[j]]+weight[tour_order[j]-(int) pow(2,i)];
            }
        }

        #pragma omp parallel for
        for(int j=0;j<et.num_edges;j++){
            weight[j]=weight2[j];
        }
    }

    for(int i=0;i<et.num_edges;i++){
        cout<<(et.reverse_map[tour_order[i]]/MAX_FACTOR+1)<<" "<<(et.reverse_map[tour_order[i]]%MAX_FACTOR+1)<<" ";
        cout<<weight[tour_order[i]]<<endl;
    }
}

void assign_weights(vector<int>& weight, EulerTour et){
    weight.resize(et.num_edges,-1);
    
    omp_set_num_threads(et.num_edges);

    #pragma omp parallel for
    for(int i=0;i<et.num_edges;i++){
        tour_order[et.dist[i]]=i;
    }

    #pragma omp parallel for
    for(int i=0;i<et.num_edges;i++){
        int u,v;
        u=et.edges[tour_order[i]].first;
        v=et.edges[tour_order[i]].second;
        int j=et.reverse_map[v*MAX_FACTOR+u];
        if(u!=et.root){
            // parent of v is u
            if(et.dist[tour_order[i]]<et.dist[j]){
                weight[tour_order[i]]=0;
            }
            // parent of u is v
            else{
                weight[tour_order[i]]=1;
            }
        }
    }
}

// void postorder(unordered_map<int,int>& weight, EulerTour et){
//     vector<int> postorder(et.n,-1);
//     postorder[et.root]=et.n;
//     omp_set_num_threads(et.num_edges);
//     #pragma omp parallel for
//     for(auto x:weight){
//         int u,v;
//         u=x.first/MAX_FACTOR;
//         v=x.first%MAX_FACTOR;
//         int j=v*MAX_FACTOR+u;
//         if(u!=et.root){
//             // parent of v is u
//             if(et.dist[x.first]>=et.dist[j]){
//                 postorder[u]=x.second;
//             }
//         }
//     }

//     // printing postorder
//     for(int i=0;i<postorder.size();i++){
//         cout<<(i+1)<<" "<<postorder[i]<<endl;
//     }
// }

int main(){
    vector<int> weight;

    // performing Euler tour
    EulerTour et;
    et.find_successors();
    // et.list_ranking();

    // tour_order.resize(et.num_edges,-1);

    // assign_weights(weight,et);
    // prefix_sum(weight,et);
    // postorder(weight,et);
}