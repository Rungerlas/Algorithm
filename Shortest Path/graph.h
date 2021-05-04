#ifndef __AM_GRAPH_H__
#define __AM_GRAPH_H__

#include <limits.h>
#include "random_generator.h"

class graph
{
protected:
  int**	m_edge;
  int		no_vert;


public:
    int* v_d;
    int* v_pi;
  graph(int);
  ~graph();

  int get_no_of_vertices()
  { return no_vert; }

  void generate_random(int, int);
  bool bellman_ford(int);
  void init_source(int);
  void floyd_warshall(int**&, int**&);
  void relax(int,int, int**);
    void BF_out();

  void output(int** = 0, int** = 0);
 // void remove_matrix(int**);
protected:
  void initialize();
  void permutation(int*, int);
};



#endif
