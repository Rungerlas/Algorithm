#include <cstring>
#include <iostream>
#include <limits.h>

#include "dynprog.h"

using namespace std;


/*
 * Bottom up implementation of Smith-Waterman algorithm
 */
void SW_bottomUp(char* X, char* Y, char** P, int** H, int n, int m){

    //initialize the matrix
    int p1,p2,p3;
    p1 = p2 =p3 = 0;
    
    for (int i = 0; i<=n; i++){
        H[i][0] = P[i][0] = 0;
    }
    for (int j = 0; j<=m ; j++){
        H[0][j] = P[0][j] = 0;
    }
    
    for (int k = 1; k<=n; k++){
        for (int l = 1; l<=m; l++)
        {
            if (X[k-1] == Y[l -1])
            {
                p1 = H[k -1][l -1] +2;
            }
            else
            {
                p1 = H[k -1][l -1] -1;
            }
            p2 = H[k -1][l] -1;
            p3 = H[k][l -1] -1;
            H[k][l] = std::max(std::max(p1,p2),p3);
            
            //u: upper; l: left; c:upper left corner
            if (H[k][l] == p1)
            {
                P[k][l] = 'c';
            }
            else
            {
                if (H[k][l] == p2){
                    P[k][l] = 'u';
                }
                else
                {
                    P[k][l] = 'l';
                }
            }
        }
    }
}

/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW(char* X, char* Y, char** P, int** H, int n, int m){
    
    for (int i =0; i <=n; i++)
    {
        H[i][0] = P[i][0] = 0;
        
    }
    for (int j = 0; j <= m; j++)
    {
        H[0][j] = P[0][j] = 0;
    }
    
    for (int k = 1; k <=n; k++)
    {
        for (int l = 1; l <=m; l++)
        {
            H[k][l] = INT_MIN;
        }
    }
	
    memoized_SW_AUX(X, Y, P, H, n, m);
}

/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
int memoized_SW_AUX(char* X, char* Y, char** P, int** H, int n, int m){
    
    int p1,p2,p3;
    if (H[n][m] >= -50)
    {
        return H[n][m];
    }
    
    if (!(n ==0 || m ==0))
    {
        if (X[n -1] == Y[m -1])
        {
            p1 = memoized_SW_AUX(X, Y, P, H, n-1, m-1) +2;
        }
        else
        {
            p1 = memoized_SW_AUX(X, Y, P, H, n-1, m-1) -1;
        }
        
        p2 = memoized_SW_AUX(X, Y, P, H, n-1, m) -1;
        
        p3 = memoized_SW_AUX(X, Y, P, H, n, m-1) -1;
        
        H[n][m] = std::max(std::max (p1, p2), p3);
        if (H[n][m] == p1)
        {
            P[n][m] = 'c';
        }
        else
        {
            if (H[n][m] == p2)
            {
                P[n][m] = 'u';
            }
            else
            {
                P[n][m] = 'l';
            }
        }
    }
	
    return  H[n][m];
}

/*
 * Print X'
 */
void print_Seq_Align_X(char* X, char** P, int n, int m){
    
    if (!(n == 0 || m == 0))
    {
        if (P[n][m] == 'c')
        {
            print_Seq_Align_X(X, P, n-1, m-1);
            cout<< X[n -1];
        }
        else
        {
            if (P[n][m] == 'u')
            {
                print_Seq_Align_X(X, P, n-1, m);
                cout<< X[n -1];
                
            }
            else
            {
                print_Seq_Align_X(X, P, n, m-1);
                cout<< "-";
            }
        }
    }
	
}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char* Y, char** P, int n, int m){
    
    if (!(n == 0 || m == 0))
    {
        if (P[n][m] == 'c')
        {
            print_Seq_Align_Y(Y, P, n-1, m-1);
            cout<< Y[m -1];
        }
        else
        {
            if (P[n][m] == 'u')
            {
                print_Seq_Align_Y(Y, P, n-1, m);
                cout<< "-";
                
            }
            else
            {
                print_Seq_Align_Y(Y, P, n, m-1);
                cout<< Y[m -1];
            }
        }
    }
	
}

//Release the memory

void remove_P(char** P, int n){
    
    for (int i = 0; i <n+1; i++)
    {
        delete [] P[i];
    }
    delete [] P;
}

void remove_H(int** H, int n){
    
    for (int j = 0; j <n+1; j++)
    {
        delete [] H[j];
    }
    delete [] H;
}
