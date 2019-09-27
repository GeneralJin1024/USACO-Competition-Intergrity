#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int l[100005], locOf[100005], leaf[400005];
int size;
void update(int, int, int, int, int);
int query(int, int, int, int, int);
void update(int index, int val) {
	update(1, 0, size-1, index, val);
}
void update(int index, int l, int r, int i, int v) {
	if (l == r) {
		leaf[index] = v;
	}	
	else {
		int m = (l+r)/2;
		if (i <= m) {
			update(2*index, l, m, i, v);
		}
		else {
			update(2*index+1, m+1, r, i, v);
		}
		leaf[index] = max(leaf[2*index], leaf[2*index+1]);
	}
}
int query(int l, int r) {
	return query(1, 0, size-1, l, r);
}
int query(int index, int l, int r, int lhs, int rhs) {
	if(l >= lhs && r <= rhs) {
		return leaf[index];
	}
	int ret = 0;
	int m = (l+r)/2;
	if (m >= lhs) {
		ret = max(ret, query(2*index, l, m, lhs, rhs));
	}
	if(m+1 <= rhs) {
		ret = max(ret, query(2*index+1, m+1, r, lhs, rhs));
	}
	return ret;
}
int main() {
	ifstream fin("nocross.in");
	ofstream fout("nocross.out");
	int n;
	fin>>n;
	for(int i = 0; i < n; i++){
		fin>>l[i];
		l[i]--;
	}
	for(int i = 0; i < n; i++){
		int x;
		fin>>x;
		locOf[x-1] = i;
	}
	size = n+1;
	for(int i = 0; i < n; i++){
		vector<int> indices;
		for(int a = max(0, l[i] - 4); a < min(n, l[i] + 5); a++) {
			indices.push_back(locOf[a]);
		} 
		sort(indices.begin(), indices.end());
		for(int a = indices.size()-1; a >= 0; a--) {
			update(indices[a]+1, query(0, indices[a]) + 1);
		}
	}
	fout<<query(0, n)<<endl;
	return 0;
}
