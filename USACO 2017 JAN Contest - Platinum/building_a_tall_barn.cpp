#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1e5+5;

ll n, k, a[MAXN];

ll ct(double x) {
	ll tot = 0;
	for (int i = 0; i < n; ++i)
                // Using the quadratic formula to solve a[i]/(c(c+1)) >= x
		tot += ll((sqrt(1 + 4*a[i]/x)-1)/2);
	return tot;
}

int main() {
	cin >> n >> k;
	k -= n;
	
	for (int i = 0; i < n; ++i)
		cin >> a[i];

	double lo = 0, hi = 1e18;
	for (int i = 0; i < 200; ++i) {
		double mid = (lo+hi)/2;
		if (ct(mid) >= k)
			lo = mid;
		else
			hi = mid;
	}

	double ans = 0;
	ll tot = 0;

	for (int i = 0; i < n; ++i) {
		ll x = ll((sqrt(1 + 4*a[i]/lo)-1)/2);
		ans += 1.0*a[i]/(x+1);
		tot += x;
	}
    
	cout << (ll)round(ans - (k-tot)*lo) << endl;
}