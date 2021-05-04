#include "graph.h"
#include <iostream>

int main()
{
    /*
    Graph *g = new Graph(9);

    g->set_edge(0, 1, 1);
    g->set_edge(0, 2, 1);
    g->set_edge(1, 3, 1);
    g->set_edge(1, 4, 1);
    g->set_edge(2, 5, 1);
    g->set_edge(2, 6, 1);
    g->set_edge(3, 7, 1);
    g->set_edge(4, 8, 1);
    */
    
    Graph *g = new Graph(6);

    g->set_edge(0, 1, 1);
    g->set_edge(0, 2, 1);
    g->set_edge(0, 3, 1);
    g->set_edge(1, 4, 1);
    g->set_edge(2, 5, 1);
    g->set_edge(1, 2, 1);
    g->set_edge(5, 3, 1);
    
 

    cout << "BFS output: " << endl;
    g->bfs(0);

    cout << endl;
    cout << "DFS output: " << endl;
    g->dfs();

    delete g;

    return 0;
} 
