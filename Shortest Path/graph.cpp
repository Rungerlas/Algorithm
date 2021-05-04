#include "graph.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
graph::graph(int n)
{ /*<<<*/
  no_vert = (n > 0) ? n : 1;


/*
 * allocate adjacency matrix
 */
  m_edge = new int*[no_vert];
  for (int i = 0; i < no_vert; i++)
    m_edge[i] = new int[no_vert];

  initialize();
} /*>>>*/

graph::~graph()
{ /*<<<*/ 
/*
 * delete nil element and all other allocated nodes
 */
  for (int i = 0; i < no_vert; i++)
    delete[] m_edge[i];
  delete[] m_edge;

} /*>>>*/


void graph::initialize()
{ /*<<<*/
/*
 * initialize adjacency matrix
 * -> use infinity to allow 0 weight edges
 */
  for (int i = 0; i < no_vert; i++)
    for (int j = 0; j < no_vert; j++)
      m_edge[i][j] = INT_MAX;

} /*>>>*/

void graph::permutation(int* perm, int n)
{ /*<<<*/
  random_generator rg;
  int p_tmp, p_pos;

  for (int i = 0; i < n; i++)
    perm[i] = i;
  
  for (int i = 0; i < n; i++)
    {
      rg >> p_pos;
      p_pos = (p_pos % (n - i)) + i;

      p_tmp = perm[i];
      perm[i] = perm[p_pos];
      perm[p_pos] = p_tmp;
    }
} /*>>>*/

void graph::output(int** m_out, int** m_out_2)
{ /*<<<*/
  if (!m_out)
    m_out = m_edge;

  cout << "[";
  for (int i = 0; i < no_vert; i++)
    {
      cout << "[\t";
      for (int j = 0; j < no_vert; j++)
  if (m_out[i][j] == INT_MAX)
    cout << "inf\t";
  else
    cout << m_out[i][j] << "\t";

      if (m_out_2)
  {
    cout << "]\t\t[\t";
    for (int j = 0; j < no_vert; j++)
      if (m_out_2[i][j] == INT_MAX)
        cout << "inf\t";
      else
        cout << m_out_2[i][j] << "\t";
  }

      cout << "]" << endl;
    }
  cout << "]" << endl;
} /*>>>*/


// TODO: Implement problem 1
void graph::generate_random(int n_edges, int max_weight)
{
    random_generator rg;
    
    int* perm =new int[no_vert];
    int count = 0;
    
    int weight = max_weight;
    int  edges = n_edges;
    while (true) {
        if (count>=edges)
        {
            break;
        }
        permutation(perm, no_vert);
        int i =0;
        while (count<edges && i<=(no_vert -2))
        {
            int perm1 = perm[i];
            int perm2 = perm[i+1];
            if (m_edge[perm1][perm2] == INT_MAX)
            {
                int wr;
                rg>>wr;
                int w = weight;
                wr = wr%(1+2*w)-w;
                m_edge[perm1][perm2] = wr;
                count++;
            }
            ++i;
        }
    }
    delete [] perm;
    
 /*   while (count<n_edges)
    {
        permutation(perm, no_vert);
        for (int i =0;i<no_vert-1;i++)
        {
            if(m_edge[perm[i]][perm[i+1]] ==INT_MAX)
            {
                rg >>max_weight;
                max_weight = (max_weight %(2*max_weight+1)-max_weight);
                m_edge[perm[i]][perm[i+1]] =max_weight;
                count ++;
                
                if(count == max_weight)
                {
                    break;
                }
            }
        }
    }
    delete [] perm;
*/
}


// TODO: Implement problem 3
void graph::init_source(int s)
{
    for (int i =0;i <no_vert;i++)
    {
        v_d[i] =INT_MAX;
        v_pi[i] = -1;
    }
    v_d[s] =0;
}
bool graph::bellman_ford(int s)
{
    v_d = new int[no_vert];
    v_pi = new int[no_vert];
   
    
    for (int j =0;j <no_vert;j++)
    {
        for (int k =0;k <no_vert;k++)
        {
            for (int l =0;l <no_vert;l++)
            {
                if (m_edge[k][l] !=INT_MAX)
                {
                    relax(k, l,m_edge);
                }
            }
           
        }
       
    }
    
  return true;
}

void graph::relax(int u,int v, int** w)
{
    if (v_d[u] !=INT_MAX)
    {
        if (v_d[v] >v_d[u]+w[u][v])
        {
            v_d[v] = v_d[u]+w[u][v];
            v_pi[v] =u;
        }
    }
}

void graph::BF_out()
{
    cout << endl << "Bellman-Ford:" << endl;
    cout << "D: [\t";
    for (int i = 0; i < graph::get_no_of_vertices(); i++)
        cout << v_d[i] << "\t";
    cout << "]" << endl;
    cout << "Pi: [\t";
    for (int i = 0; i < graph::get_no_of_vertices(); i++)
        cout << v_pi[i] << "\t";
    cout << "]" << endl;
}


// TODO: Implement problem 4
void graph::floyd_warshall(int**& d, int**& pi)
{
    d =new int*[no_vert];
    pi =new int*[no_vert];
    for (int i = 0; i < no_vert; i++)
        d[i] = new int[no_vert];
    
    for (int i = 0; i < no_vert; i++)
        pi[i] = new int[no_vert];
    
    for (int i=0;i<no_vert;i++)
    {
        for (int j=0;j<no_vert;j++)
        {
            if (i !=j && m_edge[i][j] <INT_MAX)
            {
                pi[i][j] =i;
            }
            else
            {
                pi[i][j] =INT_MAX;
            }
        }
    }
    
    for (int k=0;k <no_vert;k++)
    {
        for (int l=0;l<no_vert;l++)
        {
            if (k==l)
            {
                d[k][l] =0;
            }
            else
            {
                d[k][l] =m_edge[k][l];
            }
        }
    }
    
    for (int i =0;i<no_vert;i++)
    {
        for (int j=0;j<no_vert;j++)
        {
            for (int k=0;k<no_vert;k++)
            {
                if (d[j][i] !=INT_MAX && d[i][j] !=INT_MAX)
                {
                    if (d[j][i]+d[i][j] <d[j][k])
                    {
                        d[j][k] =d[j][i] +d[i][k];
                        pi[j][k] =pi[i][k];
                    }
                }
            }
        }
    }
    
    /*
            {
                d[i][j]=INT_MAX;
                pi[i][j]=-100;
                if (m_edge[i][j]!=INT_MAX)
                {
                    d[i][j]=m_edge[i][j];
                    pi[i][j]=i;
                    //cout<<"edge= "<<m_edge[i][j]<<", pie= "<<Pie[i][j]<<endl;
                }
            }
            d[i][i]=0;
            pi[i][i]=-100;
    */
         

     
     /*
      for (int k = 0; k < no_vert; k++)
            for (int i=0;i<no_vert;i++)
                for (int j = 0; j < no_vert; j++)
                {
                    if (d[i][k]==INT_MAX || d[k][j]==INT_MAX)
                    {
                        continue;
                    }
                    //   cout<<"D["<<i<<"]["<<j<<"]= "<<D[i][j]<<", D["<<i<<"]["<<k<<"]= "<<D[i][k]<<", D["<<k<<"]["<<j<<"]= "<<D[k][j]<<endl;
                    else if (d[i][j]>d[i][k]+d[k][j])
                    {
                        d[i][j]=d[i][k]+d[k][j];
                        //cout<<"new D["<<i<<"]["<<j<<"]= "<<D[i][j]<<endl;
                        pi[i][j]=pi[k][j];
                    }
                }
      */
    /*
    for (int i =0;i <no_vert;i++)
    {
        delete [] d[i];
        delete [] pi[i];
    }
     */
}
    
    

    
        
       



