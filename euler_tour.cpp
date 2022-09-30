#include <iostream>
#include <unordered_map>
#include <vector>
#include <omp.h>
#include <cmath>
// #include "euler_tour.h"

#define MAX_FACTOR 1000

using namespace std;

vector<int> tour_order;
vector<pair<int,int>> edges2;

class EulerTour{
    public:
    int n=11;
    int num_edges=20;
    int root;
    pair<int,int> first_edge;
    vector<vector<int>> adj;
    vector<pair<int,int>> edges;
    vector<int> successor;
    vector<int> predecessor;
    unordered_map<int,int> reverse_map;
    vector<int> dist;

    /*
    * the input should be such that
    * root node must be pushed first
    * followed by nodes from left to right
    * into the adj list
    */
    EulerTour(){
        adj.resize(n,vector<int> ());
        edges.resize(num_edges,{-1,-1});
        successor.resize(num_edges,-1);
        predecessor.resize(num_edges,-1);
        dist.resize(num_edges,-1);
        n=11;
        num_edges=20;
        // manually creating the graph
        // adj[0].push_back(7);
        // edges[0]={0,7};
        // reverse_map[7]=0;
        // adj[0].push_back(1);
        // edges[1]={0,1};
        // reverse_map[1]=1;
        // adj[0].push_back(9);
        // edges[2]={0,9};
        // reverse_map[9]=2;
        // adj[0].push_back(10);
        // edges[3]={0,10};
        // reverse_map[10]=3;

        // adj[1].push_back(0);
        // edges[21]={1,0}; // i+m
        // reverse_map[1000]=21;
        
        // adj[2].push_back(3);
        // edges[4]={2,3};
        // reverse_map[2003]=4;
        
        // adj[3].push_back(7);
        // edges[5]={3,7};
        // reverse_map[3007]=5;
        // adj[3].push_back(6);
        // edges[6]={3,6};
        // reverse_map[3006]=6;
        // adj[3].push_back(2);
        // edges[24]={3,2}; //
        // reverse_map[3002]=24;
        
        // adj[4].push_back(7);
        // edges[7]={4,7};
        // reverse_map[4007]=7;
        // adj[4].push_back(5);
        // edges[8]={4,5};
        // reverse_map[4005]=8;
        // adj[4].push_back(8);
        // edges[9]={4,8};
        // reverse_map[4008]=9;
        
        // adj[5].push_back(4);
        // edges[28]={5,4}; //
        // reverse_map[5004]=28;
        
        // adj[6].push_back(3);
        // edges[26]={6,3}; //
        // reverse_map[6003]=26;
        
        // adj[7].push_back(3);
        // edges[25]={7,3}; //
        // reverse_map[7003]=25;
        // adj[7].push_back(0);
        // edges[20]={7,0}; //
        // reverse_map[7000]=20;
        // adj[7].push_back(4);
        // edges[27]={7,4}; //
        // reverse_map[7004]=27;
        
        // adj[8].push_back(4);
        // edges[29]={8,4}; //
        // reverse_map[8004]=29;
        
        // adj[9].push_back(0);
        // edges[22]={9,0}; //
        // reverse_map[9000]=22;
        
        // adj[10].push_back(0);
        // edges[23]={10,0}; //
        // reverse_map[10000]=23;
        // root=7;

        adj[0].push_back(7);
        edges[0]={0,7};
        reverse_map[7]=0;
        adj[0].push_back(1);
        edges[1]={0,1};
        reverse_map[1]=1;
        adj[0].push_back(9);
        edges[2]={0,9};
        reverse_map[9]=2;
        adj[0].push_back(10);
        edges[3]={0,10};
        reverse_map[10]=3;

        adj[1].push_back(0);
        edges[4]={1,0}; // i+m
        reverse_map[1000]=4;
        
        adj[2].push_back(3);
        edges[5]={2,3};
        reverse_map[2003]=5;
        
        adj[3].push_back(7);
        edges[6]={3,7};
        reverse_map[3007]=6;
        adj[3].push_back(6);
        edges[7]={3,6};
        reverse_map[3006]=7;
        adj[3].push_back(2);
        edges[8]={3,2}; //
        reverse_map[3002]=8;
        
        adj[4].push_back(7);
        edges[9]={4,7};
        reverse_map[4007]=9;
        adj[4].push_back(5);
        edges[10]={4,5};
        reverse_map[4005]=10;
        adj[4].push_back(8);
        edges[11]={4,8};
        reverse_map[4008]=11;
        
        adj[5].push_back(4);
        edges[12]={5,4}; //
        reverse_map[5004]=12;
        
        adj[6].push_back(3);
        edges[13]={6,3}; //
        reverse_map[6003]=13;
        
        adj[7].push_back(3);
        edges[14]={7,3}; //
        reverse_map[7003]=14;
        adj[7].push_back(0);
        edges[15]={7,0}; //
        reverse_map[7000]=15;
        adj[7].push_back(4);
        edges[16]={7,4}; //
        reverse_map[7004]=16;
        
        adj[8].push_back(4);
        edges[17]={8,4}; //
        reverse_map[8004]=17;
        
        adj[9].push_back(0);
        edges[18]={9,0}; //
        reverse_map[9000]=18;
        
        adj[10].push_back(0);
        edges[19]={10,0}; //
        reverse_map[10000]=19;
        root=7;
    }

    void find_successors(){
        omp_set_num_threads(n);
        #pragma omp parallel for
        for(int i=0;i<n;i++){
            int u,v;
            int hashed_lhs,hashed_rhs;
            for(int j=0;j<adj[i].size();j++){
                if(i==root && j==adj[i].size()-1){
                    // set the last edge to point to itself
                    continue;
                }
                v=i;
                u=adj[i][j];
                hashed_lhs=u*MAX_FACTOR+v;
                hashed_rhs=v*MAX_FACTOR+adj[i][(j+1)%adj[i].size()];
                
                successor[reverse_map[hashed_lhs]]=reverse_map[hashed_rhs];
                predecessor[reverse_map[hashed_rhs]]=reverse_map[hashed_lhs];
                if(adj[u].size()==1){
                    successor[reverse_map[v*MAX_FACTOR+u]]=reverse_map[hashed_lhs];
                    predecessor[reverse_map[hashed_lhs]]=reverse_map[v*MAX_FACTOR+u];
                }
                if(i==root && j==0){
                    first_edge={i,adj[i][j]};
                    predecessor[reverse_map[i*MAX_FACTOR+adj[i][j]]]=reverse_map[i*MAX_FACTOR+adj[i][j]];
                }
            }
        }
        // print_successors();
    }

    void list_ranking(){
        int limit=(int) (log2(num_edges)+1);
        omp_set_num_threads(num_edges);
        
        #pragma omp parallel for
        for(int i=0;i<num_edges;i++){
            if(edges[i]==first_edge){
                dist[i]=0;
            }
            else{
                dist[i]=1;
            }
        }
        for(int j=0;j<limit;j++){
            vector<int> dist2(num_edges,-1);
            vector<int> predecessor2(num_edges,-1);
            #pragma omp parallel for
            for(int i=0;i<num_edges;i++){
                if(edges[i]!=first_edge){
                    dist2[i]=dist[i]+dist[predecessor[i]];
                    predecessor2[i]=predecessor[predecessor[i]];
                }
            }

            #pragma omp parallel for
            for(int i=0;i<num_edges;i++){
                if(edges[i]!=first_edge){
                    predecessor[i]=predecessor2[i];
                }
            }
            
            #pragma omp parallel for
            for(int i=0;i<num_edges;i++){
                if(edges[i]!=first_edge){
                    dist[i]=dist2[i];
                }
            }
        }

        print_tour();
    }

    void print_tour(){
        cout<<"Euler Tour:\n";
        for(int i=0;i<num_edges;i++){
            int u=edges[i].first+1;
            int v=edges[i].second+1;
            cout<<u<<"->"<<v<<": "<<(dist[i]+1)<<endl;
        }
        cout<<endl;
    }

    void print_successors(){
        for(int i=0;i<predecessor.size();i++){
            if(predecessor[i]==-1){
                continue;
            }
            int u=edges[i].first+1;
            int v=edges[i].second+1;
            cout<<u<<" "<<v<<" -> ";
            u=edges[predecessor[i]].first+1;
            v=edges[predecessor[i]].second+1;
            cout<<u<<" "<<v<<endl;
        }
        cout<<successor.size()<<" "<<predecessor.size()<<endl;
    }
};

void postorder(vector<int>& weight, EulerTour et){
    vector<int> post(et.n,0);
    
    #pragma omp parallel for
    for(int i=0;i<et.num_edges;i++){
        int u,v;
        u=edges2[i].first;
        v=edges2[i].second;
        int j=et.reverse_map[v*MAX_FACTOR+u];
        // parent of u is v
        if(et.dist[tour_order[i]]>=et.dist[j]){
            post[u]=weight[i];
        }
    }
    post[et.root]=et.n;

    cout<<"Postorder traversal:\n";
    for(int i=0;i<et.n;i++){
        cout<<(i+1)<<" => "<<(post[i])<<endl;
    }
}

void prefix_sum(vector<int>& weight, EulerTour et){
    int limit=(int) (log2(et.num_edges)+1);
    omp_set_num_threads(et.num_edges);

    vector<int> weight2(et.num_edges,-1);

    #pragma omp parallel for
    for(int i=0;i<et.num_edges;i++){
        weight2[i]=weight[i];
    }

    for(int i=0;i<limit;i++){

        #pragma omp parallel for
        for(int j=0;j<et.num_edges;j++){
            if(j<(int) pow(2,i)){
                weight2[j]=weight[j];
            }
            else{
                weight2[j]=weight[j]+weight[j-(int) pow(2,i)];
            }
        }

        #pragma omp parallel for
        for(int j=0;j<et.num_edges;j++){
            weight[j]=weight2[j];
        }
    }

    // for(int i=0;i<et.num_edges;i++){
    //     cout<<(edges2[i].first+1)<<"->"<<(edges2[i].second+1)<<" ";
    //     cout<<weight[i]<<endl;
    // }
}

void assign_weights(vector<int>& weight, EulerTour et){
    weight.resize(et.num_edges,-1);
    tour_order.resize(et.num_edges,-1);
    edges2.resize(et.num_edges,{-1,-1});
    
    omp_set_num_threads(et.num_edges);

    #pragma omp parallel for
    for(int i=0;i<et.num_edges;i++){
        tour_order[et.dist[i]]=i;
    }

    #pragma omp parallel for
    for(int i=0;i<et.num_edges;i++){
        edges2[i]=et.edges[tour_order[i]];
    }

    #pragma omp parallel for
    for(int i=0;i<et.num_edges;i++){
        int u,v;
        u=edges2[i].first;
        v=edges2[i].second;
        int j=et.reverse_map[v*MAX_FACTOR+u];
        // parent of v is u
        if(et.dist[tour_order[i]]<et.dist[j]){
            weight[i]=0;
        }
        // parent of u is v
        else{
            weight[i]=1;
        }
    }

}

int main(){
    EulerTour et;
    et.find_successors();
    et.list_ranking();

    vector<int> weight;
    assign_weights(weight,et);
    prefix_sum(weight,et);
    postorder(weight,et);
}