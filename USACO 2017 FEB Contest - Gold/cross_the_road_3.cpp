#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN (1 << 17)

int BT[MAXN];

/* Logically executes array[x] += v. */
void bit_add(int x, int v) {
    for(int i = x | MAXN; i < (MAXN << 1); i += i & -i) {
        BT[i ^ MAXN] += v;
    }
}
 
/* Returns the sum of array[i] for 0 <= i < x */
int bit_get(int x) {
    int ret = 0;
    for(int i = x - 1; x != 0; i &= i - 1) {
        ret += BT[i];
        if(!i) break;
    }
    return ret;
}

int main() {
    int N; cin >> N;

    vector<pair<int, int> > A(N, make_pair(-1, -1));
    for (int i = 0; i < 2 * N; i++) {
        int x; cin >> x; x--;
        if (A[x].first == -1) {
            A[x].first = i;
        } else {
            A[x].second = i;
        }
    }
    sort(A.begin(), A.end());

    int result = 0;
    for (int i = 0; i < A.size(); i++) {
        result += bit_get(A[i].second) - bit_get(A[i].first);
        bit_add(A[i].second, 1);
    }
    cout << result << endl;

    return 0;
}