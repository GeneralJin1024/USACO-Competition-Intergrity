#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int parent[1000];
int x[1000];
int y[1000];
struct Edge {
	int x,y,w;
	bool operator < (const Edge &e) const{
		return w < e.w;
	}
};
int find(int curr){
	return parent[curr] == curr ? curr : (parent[curr] = find(parent[curr]));
}
void merge(int x, int y){
	parent[find(x)] = find(y);
}
int main() {
	ifstream fin("moocast.in");
	ofstream fout("moocast.out");
	int n=0;
	fin>>n;
	for (int i = 0; i < n; i++) {
		fin>>x[i]>>y[i];
	}
	vector<Edge> edges;
	for (int i = 0; i < n; i++) {
		parent[i] = i;
		for (int j = 0; j < i; j++) {
			int distance = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
			Edge temp;
			temp.x = i;
			temp.y = j;
			temp.w = distance;
			edges.push_back(temp);
		}
	}
	sort(edges.begin(), edges.end());
	int lastWeight = 0;
	int numComponents = n;
	for(int i = 0; i < edges.size(); i++) {
		if(find(edges[i].x) != find(edges[i].y)) {
			merge(edges[i].x, edges[i].y);
			lastWeight = edges[i].w;
			if (--numComponents == 1) {
				break;
			}
		}
	}
	fout<<lastWeight<<endl;
	return 0;
}
