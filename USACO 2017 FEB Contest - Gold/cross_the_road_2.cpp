#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int N;
int A[1000][1000];
int S[1000], T[1000];

int main(void)
{
  ifstream fin("nocross.in");
  ofstream fout("nocross.out");
  fin >> N; 
  for (int i=0; i<N; i++) fin >> S[i];
  for (int i=0; i<N; i++) fin >> T[i];
  A[0][0] = abs(S[0]-T[0])<=4;
  for (int i=1; i<N; i++) A[i][0] = max(A[i-1][0], (int)(abs(S[i]-T[0]) <= 4));
  for (int i=1; i<N; i++) A[0][i] = max(A[0][i-1], (int)(abs(S[0]-T[i]) <= 4));
  for (int i=1; i<N; i++)
    for (int j=1; j<N; j++)
      A[i][j] = max( max(A[i-1][j], A[i][j-1]), A[i-1][j-1]+(abs(S[i]-T[j])<=4));
  fout << A[N-1][N-1] << "\n";
  return 0;
}