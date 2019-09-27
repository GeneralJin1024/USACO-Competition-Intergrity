#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
list<int> children[100005];
int size[100005];
int start[100005];
int leaf[100005];
int numSeen;
void dfs(int index) {
	start[index] = numSeen++;
	size[index]++;
	list<int> child = children[index];
	list<int>::iterator iter;
	for(iter = child.begin(); iter != child.end(); iter++) {
		int out = *iter;
		dfs(out);
		size[index] += size[out];
	}
}
struct State {
	int index, val;
	bool operator < (const State &s) const {
		return val > s.val;
	}
};
void increment(int x) {
	x+=2;
	while(x < sizeof(leaf)/sizeof(leaf[0])) {
		leaf[x]++;
		x += x & -x;
	}
}
int query(int x) {
	int ret = 0;
	x+=2;
	while(x > 0) {
		ret += leaf[x];
		x -= x & -x;
	}
	return ret;
}
int main() {
	ifstream fin("promote.in");
	ofstream fout("promote.out");
	int n;
	fin>>n;
	State l[n];
	for(int i = 0; i < n; i++) {
		l[i].index = i;
		fin>>l[i].val;
	}
	sort(l, l+n);
	for(int i = 1; i < n; i++) {
		int x;
		fin>>x;
		children[x-1].push_back(i);
	}
	dfs(0);
	int ret[n];
	for(int i = 0; i < n; i++) {
		ret[i] = 0;
	}
	for(int i = 0; i < n; i++) {
		State out = l[i];
		int rhs = start[out.index] + size[out.index] - 1;
		int lhs = start[out.index];
		ret[out.index] = query(rhs) - query(lhs);
		increment(start[out.index]);
	}
	for(int i = 0; i < n; i++) {
		fout<<ret[i]<<endl;
	}
	return 0;
}
