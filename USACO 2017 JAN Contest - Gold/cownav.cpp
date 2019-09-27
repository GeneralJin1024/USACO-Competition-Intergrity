#include <iostream>
#include <fstream>
#include <deque>
using namespace std;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int n;
char grid[25][25];
int dp[25][25][4][25][25][4];
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct State {
	int ax, ay, ad;
	int bx, by, bd;
	State turnLeft() {
		State temp;
		temp.ax = ax;
		temp.ay = ay;
		temp.ad = (ad+3)%4;
		temp.bx = bx;
		temp.by = by;
		temp.bd = (bd+3)%4;
		return temp;
	}
	State turnRight() {
		State temp;
		temp.ax = ax;
		temp.ay = ay;
		temp.ad = (ad+1)%4;
		temp.bx = bx;
		temp.by = by;
		temp.bd = (bd+1)%4;
		return temp;
	}
	State advance() {
		int nax = ax;
		int nay = ay;
		if (nax != 0 || nay != n-1) {
			if(nax + dx[ad] >= 0 && nax + dx[ad] < n) {
					nax += dx[ad];
			}
			if(nay + dy[ad] >= 0 && nay + dy[ad] < n) {
				nay += dy[ad];
			}
			if(grid[nax][nay] == 'H') {
				nax = ax;
				nay = ay;
			}
		}
		int nbx = bx;
		int nby = by;
		if(nbx != 0 || nby != n-1) {
			if(nbx + dx[bd] >= 0 && nbx + dx[bd] < n) {
				nbx += dx[bd];
			}
			if(nby + dy[bd] >= 0 && nby + dy[bd] < n) {
				nby += dy[bd];
			}
			if(grid[nbx][nby] == 'H') {
				nbx = bx;
				nby = by;
			}
		}
		State temp;
		temp.ax = nax;
		temp.ay = nay;
		temp.ad = ad;
		temp.bx = nbx;
		temp.by = nby;
		temp.bd = bd;
		return temp;
	}
	void genTransitions(State s[]) {
		s[0] = turnLeft();
		s[1] = turnRight();
		s[2] = advance();
	}
};
int main() {
	ifstream fin("cownav.in");
	ofstream fout("cownav.out");
	fin>>n;
	for(int i = 0; i < n; i++) {
		fin>>grid[i];
	}
	dp[n-1][0][0][n-1][0][1] = 1;
	deque<State> q;
	State temp;
	temp.ax = n-1;
	temp.ay = 0;
	temp.ad = 0;
	temp.bx = n-1;
	temp.by = 0;
	temp.bd = 1;
	q.push_back(temp);
	while (q.size() > 0) {
		State curr = q[0];
		if(curr.ax == 0 && curr.bx == 0 && curr.ay == n-1 && curr.by == n-1) {
			fout<<dp[curr.ax][curr.ay][curr.ad][curr.bx][curr.by][curr.bd] - 1<<endl;
			break;
		}
		State anext[3];
		curr.genTransitions(anext);
		for(int i = 0; i < 3; i++) {
			State next = anext[i];
			if(dp[next.ax][next.ay][next.ad][next.bx][next.by][next.bd] == 0) {
				dp[next.ax][next.ay][next.ad][next.bx][next.by][next.bd] = dp[curr.ax][curr.ay][curr.ad][curr.bx][curr.by][curr.bd] + 1;
				q.push_back(next);
			}
		}
		q.pop_front();
	}
	return 0;
}
