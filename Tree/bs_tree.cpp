
#include "bs_tree.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
bs_tree::bs_tree()
{
    /*
     * create T_nil element
     */
      T_root = new bs_tree_node();
    
      T_root->p = T_nil;
      T_root->left = T_nil;
      T_root->right = T_nil;
    /*
     * root of rb tree
     */
      T_root = T_nil;

} 

bs_tree::~bs_tree()
{
    remove_all(T_root);

}

//help insertion method


void bs_tree::insert(int key, bs_tree_i_info& t_info)
{
    /*
     * wrapper around insert
     * -> creates black node with key
     * -> inserts node
     */
      bs_tree_node* z;

      z = new bs_tree_node;
      
      z->key = key;

      insert(z, t_info);

}

void bs_tree::insert(bs_tree_node* z, bs_tree_i_info& t_info)
{
/*
 * binary tree type insert
 * -> search position, insert new node
 * -> fix properties after insert
 */
  bs_tree_node* x;
  bs_tree_node* y;

  y = T_nil;
  x = T_root;
  while (x != T_nil)
    {
      y = x;
        //check the duplicate
        if(z->key == x->key){
            t_info.i_duplicate++;
            return;
        }

      if (z->key < x->key)
    x = x->left;
      else
    x = x->right;
    }

  z->p = y;
    if (y == T_nil){
        T_root = z;
        count++;
    }
  else
    {
      if (z->key < y->key)
    y->left = z;
      else{
          y->right = z;
      }
        count++;
    }

  z->left = T_nil;
  z->right = T_nil;

}

void bs_tree::inorder_output(bs_tree_node* x, int level)
{ /*<<<*/
/*
 * in order walk through binary tree
 * -> see book or slides
 */
  if (x != T_nil)
    {
      inorder_output(x->left, level+1);
      cout << "(" << x->key << "," << level << ")" << endl;
        //store the element for the question 2
        outputarray[index] = x->key;
        index++;
      inorder_output(x->right, level+1);
    }
} /*>>>*/

void bs_tree::output(bs_tree_node* x, int r_level)
{ /*<<<*/
/*
 * some structured output
 */
  list< pair<bs_tree_node*,int> > l_nodes;
  pair<bs_tree_node*,int> c_node;
  int c_level;

  c_level = r_level;
  l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(x, r_level));

  while (!l_nodes.empty())
    {
      c_node = *(l_nodes.begin());

      if (c_level < c_node.second)
    {
      cout << endl;
      c_level = c_node.second;
    }

      cout << "(" << c_node.first->key << ","<< c_node.first;

      if (c_node.first->p == T_nil)
    cout << ",ROOT) ";
      else
        cout << ",P:" << c_node.first->p->key << ") ";

      if (c_node.first->left != T_nil)
    l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(c_node.first->left,
                                  c_node.second+1));
      if (c_node.first->right != T_nil)
    l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(c_node.first->right,
                                  c_node.second+1));
      l_nodes.erase(l_nodes.begin());
    }

  cout << endl;
} /*>>>*/

void bs_tree::remove_all(bs_tree_node* x)
{ /*<<<*/
/*
 * recursively remove all tree elements
 */
  if (x != T_nil)
    {
      remove_all(x->left);
      remove_all(x->right);

      delete x;
    }
} /*>>>*/

// TODO: modified inorder tree walk method to save the 
// sorted numbers in the first argument: int* array.
// question 2
//use the same method in the rb_tree
int bs_tree::convert(int* array, int n)
{
    int new_n = count;
    outputarray = new int[new_n];
    inorder_output();
    for(int i= 0;i<new_n;i++){
        array[i] = outputarray[i];
    }
    delete [] outputarray;
  return new_n;
  
}



