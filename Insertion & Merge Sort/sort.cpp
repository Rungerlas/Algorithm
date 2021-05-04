#include <cstdio>
#include <cstdlib>

#include "sort.h"


int ivector_length(int* v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];

  return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int** A, int n, int l, int r)
{ 
  int i;
  int* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

/*
*   TO IMPLEMENT: Improved Insertion Sort for problem 1.
*/
void insertion_sort_im(int** A, int n, int l, int r)
{
    int i;
    int* key;
    int* res = new int[r+1]; //define the result array to store each vectors
    
    // precompute the length of vectors for merge
    for(int i = 0;i <= r;i++){
        res[i]=(ivector_length(A[i], n));
    }
    
    int leftlength;
    // insertion sort
    for (int j = l+1; j <= r; j++)
    {
        key = A[j];
        i = j - 1;
        leftlength=res[j]; //set the rest length of vectors
  while (i >= l && res[i] > leftlength){
        // sorting exchange
          
          res[i+1]= res[i];
          A[i+1] = A[i];
          i= i -1;
        }
        A[i+1] = key;
        res[i+1]=leftlength; //put the left length to the rest
        }
}

/*
*   TO IMPLEMENT: Improved Merge Sort for problem 2.
*/

// define the merge_sort method that combine the two approaches --- merge and sort method
// I first design the merge sort with python and implement this method by following the python design
void sort(int** A,int* res,int* vec_sum, int** vec_arr, int n, int l,int r,int mid){
    int i = l;
    int j = mid+1;
    int k = 0;
    // merge sorting
   
    while(i <= mid && j <= r)
    {
        if(res[i] < res[j]){
            vec_sum[k] = res[i];
            vec_arr[k] = A[i];
            i++;
            k++;
        }
        else{
            vec_sum[k] = res[j];
            vec_arr[k] = A[j];
            j++;
            k++;
        }
    }
    
    while (i <= mid) {
        vec_sum[k] = res[i];
        vec_arr[k] = A[i];
        i++;
        k++;
    }
    while (j <= r) {
        vec_sum[k] = res[j];
        vec_arr[k] = A[j];
        j++;
        k++;
    }
    // set the array with sorted number
    for (int k = 0, i = l; i <=r; i++,k++){
        res[i] = vec_sum[k];
        A[i] = vec_arr[k];
    }
    
    
}

//divide the vector

void merge(int** A,int* res,int* vec_sum, int** vec_arr, int n,int l,int r)
{
    if(l < r)
{
    int mid = (l+r)/2;
   //merge the L R
    merge( A, res, vec_sum, vec_arr, n, l, mid);
    merge( A, res, vec_sum, vec_arr, n, mid+1, r);
  // sort the merge array
    sort( A, res, vec_sum, vec_arr, n, l, r, mid);
        
    }
}


void merge_sort(int** A, int n, int l, int r)
{
    int i;
    // create the array to store the merge array and the vector length
    int* vec_sum = new int [r-l+1];
    int** vec_arr = new int* [r-l+1];
    //stores the length of each vectors
    int * res= new int[r+1];
    
    for(i =0; i <= r; i++)
    {
      res[i]=ivector_length(A[i], n);
    }
    // merge the array
    merge( A, res, vec_sum, vec_arr, n, l, r);

}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}

