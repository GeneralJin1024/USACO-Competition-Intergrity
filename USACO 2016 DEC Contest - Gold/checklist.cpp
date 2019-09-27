#include <iostream>
#include <fstream>
#include <vector>
#include <memory.h>
#include <limits.h>
#define min(a,b) (a > b ? b : a)
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct STATE{
	int x,y;
	STATE(int a, int b) : x(a),y(b) {};
	int dist(STATE s){
		return (x-s.x)*(x-s.x) + (y-s.y)*(y-s.y);
	}
};
long long dp[1001][1001][2];
int main() {
	ifstream fin("checklist.in");
	ofstream fout("checklist.out");
	int n = 0,m = 0;
	vector<STATE>holstein,guernsey;
	fin>>n>>m;
	for (int i = 0; i < n; i++){
		int x,y;
		fin>>x>>y;
		holstein.push_back(STATE(x,y));
	}
	for (int i = 0; i < m; i++){
		int x,y;
		fin>>x>>y;
		guernsey.push_back(STATE(x,y));
	}
	for (int i = 0; i < n+1; i++) {
		for (int j = 0; j < m+1; j++) {
			for (int k = 0; k < 2; k++) {
				dp[i][j][k] = 1LL<<63-1;
			}
		}
	}
	dp[1][0][0] = 0;
	for (int i = 0; i < n+1; i++){
		for (int j = 0; j < m+1; j++) {
			for (int k = 0; k < 2; k++){
				if(k == 0 && i == 0) continue;
				if(k == 1 && j == 0) continue;
				STATE source(0, 0);
				if(k == 0) source = STATE(holstein[i-1].x, holstein[i-1].y);
				else source = STATE(guernsey[j-1].x, guernsey[j-1].y);
				if(i < n) {
					dp[i+1][j][0] = min(dp[i+1][j][0], dp[i][j][k] + source.dist(holstein[i]));
				}
				if(j < m) {
					dp[i][j+1][1] = min(dp[i][j+1][1], dp[i][j][k] + source.dist(guernsey[j]));
				}
			}
		}
	}
	fout<<dp[n][m][0]<<endl;
	return 0;
}
