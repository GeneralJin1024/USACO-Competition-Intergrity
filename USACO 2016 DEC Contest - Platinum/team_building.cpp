#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int value;
    bool isFj;

    bool operator<(Node const& other) const {
        if (value == other.value) {
            return isFj && !other.isFj;
        }
        return value < other.value;
    }
};

#define NMAX 1000
#define KMAX 10

#define MOD 1000000009

unsigned int dp[2 * NMAX + 1][KMAX + 1][KMAX + 1];

int main() {
    int n, m, k;
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);

    vector<Node> nodes;
    for (int i = 0; i < n; i++) {
        Node n;
        scanf("%d", &n.value);
        n.isFj = true;
        nodes.push_back(n);
    }
    for (int i = 0; i < m; i++) {
        Node n;
        scanf("%d", &n.value);
        n.isFj = false;
        nodes.push_back(n);
    }

    sort(nodes.begin(), nodes.end());

    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k; j++) {
            dp[nodes.size()][i][j] = (i == 0 && j == 0 ? 1 : 0);
        }
    }

    for (int pos = nodes.size() - 1; pos >= 0; pos--) {
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= k; j++) {
                if (j > i) {
                    dp[pos][i][j] = 0;
                } else {
                    if (nodes[pos].isFj) {
                        dp[pos][i][j] = (dp[pos+1][i][j] + (i > 0 ? dp[pos+1][i-1][j] : 0)) % MOD;
                    } else {
                        dp[pos][i][j] = (dp[pos+1][i][j] + (j > 0 ? dp[pos+1][i][j-1] : 0)) % MOD;
                    }
                }
            }
        }
    }

    printf("%d\n", dp[0][k][k]);
}