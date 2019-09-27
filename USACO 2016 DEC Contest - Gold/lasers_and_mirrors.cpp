#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Line{
	int val;
	bool horizontal;
	int hashCode() {
		const int prime = 31;
		int result = 1;
		result = prime * result + (horizontal ? 1231 : 1237);
		result = prime * result + val;
		return result;
	}
	bool equals(Line other) {
		if (horizontal != other.horizontal)
			return false;
		if (val != other.val)
			return false;
		return true;
	}
	bool operator < (const Line &other) const  //although we won't use this in the code
	{										  //It's necessary for creating a map which uses Line as the key type
         if (val < other.val)        
         {
             return true;
         }
         return false;
    }
};
map<Line, int> dist;
vector<Line> q;
map< int, vector<int> > xtoY, ytoX;
void init_line(int v, bool b){
	Line temp;
	temp.val = v;
	temp.horizontal = b;
	q.push_back(temp);
	dist[temp] = 0;
}
int main() {
	ifstream fin("lasers.in");
	ofstream fout("lasers.out");
	int n,x1,y1,x2,y2;
	fin>>n>>x1>>y1>>x2>>y2;
	init_line(y1, true);
	init_line(x1, false);
	for(int i = 0; i < n; i++) {
		int x, y;
		fin>>x>>y;
		xtoY[x].push_back(y);
		ytoX[y].push_back(x);
	}
	int ret = -1;
	int last = q.size();
	int begin = 0;
	while(begin < last) {
		Line curr = q[begin];
		if(curr.horizontal && curr.val == y2) {
			ret = dist[curr];
			break;
		}
		if(!curr.horizontal && curr.val == x2) {
			ret = dist[curr];
			break;
		}
		map< int, vector<int> > &source = curr.horizontal ? ytoX : xtoY;
		if(source.count(curr.val)) {
			for(int i = 0; i < source[curr.val].size(); i++) {
				Line nextLine;
				nextLine.val = source[curr.val][i];
				nextLine.horizontal = !curr.horizontal;
				if(dist.find(nextLine) == dist.end()) {
					dist[nextLine] = dist[curr] + 1;
					q.push_back(nextLine);
					last++;
				}
			}
		}
		begin++;
	}
	fout<<ret<<endl;
	return 0;
}
