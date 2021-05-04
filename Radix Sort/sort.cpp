#include <cstdio>
#include <cstdlib>

#include "sort.h"

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
	return -1;
      else
	return 1;
    }
}

//design the compare method for the digit string compare

int digit_compare(char* s1, char* s2, int A_len, int lenkey, int d)
{
    // if d in the string // string compare
    int res = 0;
    if(d<=A_len && d<=lenkey)
    {
        if(s1[d-1] == s2[d-1]) //get the d-1 to the real d index
            res = 0;
        else
        {
            if(s1[d-1]<s2[d-1])
            res =  -1;
        else
            res =  1;
        }
    }
    
    
    //if d not in the string
    else if(d>A_len && d>lenkey)
        res =  0;
    else
    {
        if(d>A_len && d<lenkey)
            res =  -1;
        else if (d<=A_len && d>lenkey)
            res =  1;
    }
    return res;
}

void insertion_sort(char** A, int l, int r)
{ 
  int i;
  char* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (string_compare(A[i], key) > 0))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

// follow the method insertion sort to design
void insertion_sort_digit(char** A, int* A_len, int l, int r, int d)
{
    int i;
    char* key;
    int lenkey;
    for (int j=l+1; j<=r; j++) {
        key = A[j];
        lenkey = A_len[j];
        i = j-1;
        while ((i>=l)&&(digit_compare(A[i], key, A_len[i], lenkey, d)>0)) {
            A[i+1] = A[i];
            A_len[i+1] = A_len[i];
            i = i-1;
        }
        A[i+1] = key;
        A_len[i+1] = lenkey;
    }

}

void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d)
{
    //use int C[256] to store the counters/positions.
    int size = 256;
    int* C = new int[size];
    for(int i=0;i<=size;i++){
        C[i] = 0;
    }
    for (int j=0; j<n; j++) {
        if(A_len[j]>=d){
            C[A[j][d-1]] = C[A[j][d-1]] +1;
        }
        else{
            C[0] ++;
        }
    }
    for (int k=1; k<=size; k++) {
        C[k] = C[k]+C[k-1];
    }
    for (int l=n-1; l>=0; l--) {
        if (d<=A_len[l]) {
            B[C[A[l][d-1]]-1] = A[l];
            B_len[C[A[l][d-1]]-1] = A_len[l];
            C[A[l][d-1]] = C[A[l][d-1]]-1;
        }else{ // d out of string
            B[C[0]-1] = A[l];
            B_len[C[0]-1] = A_len[l];
            C[0] =C[0]-1;
        }
    }
    
    //sorted
    for (int m=0; m<n; m++) {
        A[m] = B[m];
        A_len[m] = B_len[m];
    }
    delete[] C;
}

void radix_sort_is(char** A, int* A_len, int n, int m)
{
    int i = m;
    for (; i>0; i--) {
        insertion_sort_digit(A, A_len, 0, n-1, i);
    }

}

void radix_sort_cs(char** A, int* A_len, int n, int m)
{
    char** B = new char*[n];
    int* B_len =new int[n];
    int i = m;
    for (;i>0; i--) {
        counting_sort_digit(A, A_len, B, B_len, n, i);
    }
    delete[] B;
    delete[] B_len;
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}
