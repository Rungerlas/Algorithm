#include "graph.h"

#include<iostream>
#include <queue> //add queue for algorithm to search the graph

using namespace std;

// Creates a graph of size param1
Graph::Graph(int n){
    //check whether the graph is exist by checking the number of the nodes
    if(n <= 0){
        
        cout<<"The graph is not exist."<<endl;
        return;
        
    }
    else{
        //initialize the matrix for store the grpah data
        nodes = n;
        matrix = new int*[n];
        for(int i=0; i<n; i++){
            matrix[i] = new int[n];
        }
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                matrix[i][j] = 0;
            }
        }
        
    }
}

// Creates a graph from an adjacency matrix of size param2
Graph::Graph(int** adjacency_matrix, int n){

        nodes = n;
        matrix = new int*[n];
        for(int i=0; i<n; i++){
            matrix[i] = new int[n];
        }
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                matrix[i][j] = adjacency_matrix[i][j];
            }
        }
}
// Creates a graph from an adjacency matrix of size param2
Graph::~Graph(){
    //free the memory from matrix
    for(int i=0; i<nodes; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Sets the value of the edge (param1, param2) to param3
// param3 is the weight of the edge
bool Graph::set_edge(int parent,int child,int weight){
    
    //set the edge for the graph, the first value is parent and second is children including the weight between these two nodes
    //these nodes' values should be over 0 and below the number of the graph edges
    if(parent <nodes && child <nodes && parent>=0 && child>=0){
        
        matrix[parent][child] = weight;
        return true;
        
    }
    else{
        return false;
    }
    
    
}

//realize the bfs algorithm
void Graph::bfs(int node){
    
    //check whether the root node is exist
    if(node <0 && node >=nodes-1){
        
        cout<<"The start node is not exist"<<endl;
        return;
    }
    else{
        
        //use the set to keep track of the visited nodes instead of coloring them
        set <int>* vnode = new set<int>;
        bfs(node,vnode); // use the helper fuction to apply the bfs
    }
}

// Helper funciton for dfs, takes a start node and a set of visited nodes as args
void Graph::bfs(int node, set<int>* vnode){
    
    //create the queue for the graph to store the visited nodes
    queue <int> vque;
    vque.push(node); //each time visit one node in the graph
    vnode ->insert(node);
    cout<<node;
    //bfs traversal the grpah
    while (!vque.empty()){
        
        int root =vque.front();
        vque.pop();
        for (int i = 0; i < nodes; i++){
            //when visit the next node use the cout instruction to show the sequence
            if (matrix[root][i] ==1 && vnode->count(i) ==0){
                vque.push(i);
                vnode->insert(i);
                cout<<"---->";
                cout<<i;
            }
        }
    }
    cout<<""<<endl;
    
    //free the visited node memory
    delete vnode;
}

//realize the dfs algorithm
//
void Graph::dfs(){
    
    //it is the same as the bfs realization with the set to track the visited nodes
    set <int>* vnode = new set<int>;
    for (int node = 0; node < nodes; node++){
        
        if (vnode->count(node) ==0){
            dfs(node,vnode);
        }
    }
    cout<<endl;
    //free the visited node memory
    delete vnode;
}
// Helper funciton for bfs, takes a start node and a set of visited nodes as args
void Graph::dfs(int node, set<int>* vnode){
    
    vnode->insert(node);
    cout<<node;
    //use the recursion to traversal to the end
    for (int i =0; i <nodes; i++){
        if (matrix[node][i]==1 && vnode->count(i)==0){
            cout<<"---->";
            dfs(i,vnode);
        }
    }
    
}


