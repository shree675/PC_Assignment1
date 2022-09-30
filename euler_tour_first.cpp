// #include <iostream>
// #include <unordered_map>
// #include <vector>
// #include <omp.h>
// #include <cmath>

// #define MAX_FACTOR 1000

// using namespace std;

// class EulerTour{
//     public:
//     int n=11;
//     int root;
//     int num_edges;
//     vector<vector<int>> adj;
//     unordered_map<int,int> successor;
//     unordered_map<int,int> predecessor;
//     unordered_map<int,int> dist;
//     vector<pair<int,int>> edges;

//     /*
//     * the input should be such that
//     * root node must be pushed first
//     * followed by nodes from left to right
//     * into the adj list
//     */
//     EulerTour(){
//         adj.resize(n,vector<int> ());
//         // edges.resize(2*num_edges+1,{-1,-1});
//         // manually creating the graph
//         adj[0].push_back(7);
//         adj[0].push_back(1);
//         adj[0].push_back(9);
//         adj[0].push_back(10);

//         adj[1].push_back(0);
        
//         adj[2].push_back(3);
        
//         adj[3].push_back(7);
//         adj[3].push_back(6);
//         adj[3].push_back(2);
        
//         adj[4].push_back(7);
//         adj[4].push_back(5);
//         adj[4].push_back(8);
        
//         adj[5].push_back(4);
        
//         adj[6].push_back(3);
        
//         adj[7].push_back(3);
//         adj[7].push_back(0);
//         adj[7].push_back(4);
        
//         adj[8].push_back(4);
        
//         adj[9].push_back(0);
        
//         adj[10].push_back(0);
//         root=7;

//         find_successors();
//     }

//     void find_successors(){
//         #pragma omp parallel num_threads(n)
//         {
//             unordered_map<int,int> partial_successor;
//             unordered_map<int,int> partial_predecessor;
//             #pragma omp for
//             for(int i=0;i<n;i++){
//                 int u,v;
//                 int hashed_lhs,hashed_rhs;
//                 for(int j=0;j<adj[i].size();j++){
//                     v=i;
//                     u=adj[i][j];
//                     hashed_lhs=u*MAX_FACTOR+v;
//                     hashed_rhs=v*MAX_FACTOR+adj[i][(j+1)%adj[i].size()];
//                     if(i==root && j==adj[i].size()-1){
//                         // set the last edge to point to itself
//                         continue;
//                     }
                    
//                     partial_successor[hashed_lhs]=hashed_rhs;
//                     partial_predecessor[hashed_rhs]=hashed_lhs;
//                     if(adj[u].size()==1){
//                         partial_successor[v*MAX_FACTOR+u]=hashed_lhs;
//                         partial_predecessor[hashed_lhs]=v*MAX_FACTOR+u;
//                     }
//                 }
//             }
//             #pragma omp critical
//             {
//                 successor.insert(partial_successor.begin(),partial_successor.end());
//                 predecessor.insert(partial_predecessor.begin(),partial_predecessor.end());
//             }
//         }
//         // print_successors();

//         // perform list ranking on predecessor
//         list_ranking();
//     }

//     void list_ranking(){
//         num_edges=predecessor.size();
//         int limit=(int) (log2(num_edges)+1);
//         // #pragma omp parallel num_threads(num_edges)
//         // {
//             #pragma omp parallel for
//             /*
//             * setting dist[first_node]=0 is not required
//             * because unordered_map stores 0 by default
//             * if not specified
//             */
//             for(size_t b=0;b<predecessor.bucket_count();b++)
//             for(auto x=predecessor.begin(b);x!=predecessor.end(b);x++){
//                 dist[x->first]=1;
//             }
//         // }
//         for(int i=0;i<0;i++){
//             unordered_map<int,int> dist2;
//             unordered_map<int,int> predecessor2;
//             // #pragma omp parallel num_threads(num_edges)
//             // {   
//                 #pragma omp parallel for
//                 for(size_t b=0;b<predecessor.bucket_count();b++){
//                     for(auto x=predecessor.begin(b);x!=predecessor.end(b);x++){
//                         if(x->first!=0){
//                             dist2[x->first]=dist[x->first]+dist[x->second];
//                             predecessor2[x->first]=predecessor[x->second];
//                         }
//                     }
//                 }
                
//                 // #pragma omp parallel for
//                 // for(size_t b=0;b<predecessor2.bucket_count();b++)
//                 // for(auto x=predecessor2.begin(b);x!=predecessor2.end(b);x++){
//                 //     if(x->first!=0){
//                 //         predecessor[x->first]=x->second;
//                 //     }
//                 // }
                
//                 // #pragma omp parallel for
//                 // for(size_t b=0;b<dist2.bucket_count();b++)
//                 // for(auto x=dist2.begin(b);x!=dist2.end(b);x++){
//                 //     if(x->first!=0){
//                 //         dist[x->first]=x->second;
//                 //     }
//                 // }
                
//             // }
//         }
//         #pragma omp barrier
//         print_dist();
//     }

//     void print_dist(){
//         /*
//         * printing need not be parallelized
//         * 
//         * printing is not considered for time complexity
//         * but it can be parallelized nevertheless
//         * just like the previous parallel loops
//         */
//        cout<<dist.size()<<endl;
//         cout<<"Euler tour:\n";
//         for(auto x:dist){
//             int u=x.first/MAX_FACTOR+1;
//             int v=x.first%MAX_FACTOR+1;
//             cout<<u<<"->"<<v<<": "<<(x.second+1)<<endl;
//         }
//         cout<<endl;
//     }

//     void print_successors(){
//         for(auto x:predecessor){
//             int u=x.first/MAX_FACTOR+1;
//             int v=x.first%MAX_FACTOR+1;
//             cout<<u<<" "<<v<<" -> ";
//             u=x.second/MAX_FACTOR+1;
//             v=x.second%MAX_FACTOR+1;
//             cout<<u<<" "<<v<<endl;
//         }
//         cout<<successor.size()<<" "<<predecessor.size()<<endl;
//     }
// };

// int main(){
//     EulerTour et;
// }