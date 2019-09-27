#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct State{
	int height, index;
	bool operator < (const State &s) const {
		return height > s.height;
	}
};
int tree[100005];
void update(int index, int val) {
	index++;
	while(index < sizeof(tree)/sizeof(tree[0])) {
		tree[index] += val;
		index += index & -index;
	}
}
int query(int index) {
	int ret = 0;
	index++;
	while(index > 0) {
		ret += tree[index];
		index -= index & -index;
	}
	return ret;
}
int main() {
	ifstream fin("bphoto.in");
	ofstream fout("bphoto.out");
	int n;
	fin>>n;
	vector<State> l;
	for(int i = 0; i < n; i++) {
		State temp;
		fin>>temp.height;
		temp.index = i;
		l.push_back(temp);
	}
	sort(l.begin(), l.end());
	int ret = 0;
	int seen = 0;
	for(int i = 0; i < l.size(); i++) {
		State &curr = l[i];
		int lhs = query(curr.index);
		int rhs = seen - lhs;
		if(max(lhs, rhs) > 2 * min(lhs, rhs)) {
			ret++;
		}
		update(curr.index, 1);
		seen++;
	}
	fout<<ret<<endl;
	return 0;
}
