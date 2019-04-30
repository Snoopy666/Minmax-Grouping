#include <iostream>
#include <algorithm>
using namespace std;

void dp(int A[], int C[][4], int X[][4], int N, int M){
    for(int j=2; j<=M; j++){
        for(int i=j; i<=N; i++){
            int temp[i+1]; //min value of every k
            for(int t=0; t<=i; t++){
                temp[t] = 0;
            }
            int maxvalue = 0; //max value of every C[i,j]
            int index = 0; //x of previous level
            for(int k=j-1; k<i; k++){
                int sum = 0;
                for(int l=k+1; l<=i; l++){
                    sum += A[l-1];
                }
                temp[k] = min(C[k][j-1],sum);
            }
            for(int k=j-1; k<i; k++){
                if (maxvalue < temp[k]){
                    maxvalue = temp[k];
                    index = k;
                }
            }
            X[i][j] = index;
            C[i][j] = maxvalue;
        }
    }
}

void traceback(int X[][4], int G[], int N, int M){
    int temp = N;
    for(int i=M; i>=1; i--){
        G[i] = temp;
        temp = X[temp][i];
        G[i] -= temp;
    }
}

int main(int argc, char *argv[])
{
    int A[]={3,9,7,8,2,6,5,10,1,7,6,4};
    //int A[]={1,3,5,7,9,11,13,15,17,19,21,23};
    //int A[]={2,4,6,8,10,12,14,16,18,20,22,24};
    int M = 3;
    //int M = 4;
    //int M = 5;
    int N =sizeof(A)/sizeof(*A);
    int C[N+1][4],X[N+1][4],G[M+1];
    for(int i=0; i<N+1; i++){
        for(int j=0; j<M+1; j++){
            C[i][j] = 0;
            X[i][j] = 0;
        }
    }
    for(int i=0; i<M+1; i++){
        G[i] = 0;
    }
    for(int i=1; i<=N; i++){
        C[i][1] = C[i-1][1] + A[i-1];
    }
    dp(A,C,X,N,M);
    traceback(X,G,N,M);
    for(int i=1; i<=M; i++){
        cout<<"G["<<i<<"]: "<<G[i]<<endl;
    }
    cout<<"Maximized minimum element of array A is "<<C[N][M]<<endl;
    cout<<"Memorization Table:"<<endl;
    cout<<"   ";
    for(int i=0; i<N; i++){
        cout<<A[i]<<"  ";
    }
    cout<<endl;
    for(int j=1; j<=M; j++){
        cout<<j<<"  ";
        for(int i=1; i<=N; i++){
            cout<<C[i][j]<<"  ";
        }
        cout<<endl;
    }
    return 0;
}
