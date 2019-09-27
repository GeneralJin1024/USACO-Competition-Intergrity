#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int a[55];
int dp[55][55][55][55];
int solve(int i, int j, int k, int m) {
	if(dp[i][j][k][m] != -1) return dp[i][j][k][m];
	if (k > m) return -(1 << 29); //impossible case
	if (i > j) return 0;
    if (i == j) {
        if (a[i] >= k && a[i] <= m) return 1;
        else return 0;
    }
    // max value from interval [i,j] given we've taken k from prefix and m from suffix
    int res = 0;
    // case 1: swap i and j
    // case 1a: don't include a[i] or a[j]
    res = max(res, solve(i+1,j-1,k,m));
    // case 1b: include a[j]
    if (a[j] >= k)
        res = max(res, solve(i+1,j-1,a[j],m)+1);
    // case 1c: include a[i]
    if (a[i] <= m)
        res = max(res, solve(i+1,j-1,k,a[i])+1);
    // case 1d: include both
    if (k <= a[j] && a[j] <= a[i] && a[i] <= m) 
        res = max(res, solve(i+1,j-1,a[j],a[i])+2);
    

    // case 2: don't swap, move i forward
    // case 2a: don't include a[i]
	res = max(res, solve(i+1,j,k,m));
    // case 2b: include a[i]
    if (a[i] >= k)
        res = max(res, solve(i+1,j,a[i],m)+1);

    // case 3: don't swap, move j backward
    // case 3a: don't include a[j]
    res = max(res, solve(i,j-1,k,m));
    // case 3b: include a[j]
    if (a[j] <= m)
        res = max(res, solve(i,j-1,k,a[j])+1);
	
	return dp[i][j][k][m] = res;
}
int main() {
	ifstream fin("subrev.in");
	ofstream fout("subrev.out");
	int n;
	fin>>n;
	for (int i = 0; i < n; i++) {
		fin>>a[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < 51; k++) {
				for (int l = 0; l < 51; l++) {
					dp[i][j][k][l] = -1;
				}
			}
		}
	}
	fout<<solve(0,n-1,0,50)<<endl;
	return 0;
}
