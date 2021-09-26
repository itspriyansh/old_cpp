#include <bits/stdc++.h>
#define i64 long long
#define pair pair<i64, i64>
#define F first
#define S second
#define pb push_back
#define ppb pop_back
#define pf pop_front
using namespace std;
i64 N, *h;
i64 C;

long double intersect(pair a, pair b) {
	return (b.S-a.S)/(long double)(a.F-b.F);
}

i64 solve(pair eq, i64 x) {
	return eq.S+eq.F*x;
}

i64 solve() {
	i64 dp[N];
	dp[0] = 0;
	deque<pair> dq;
	dq.pb({-2*h[0], h[0]*h[0]});
	for(int i=1;i<N;i++) {
		dp[i] = h[i]*h[i]+C;
		while(dq.size()>1 && solve(dq[0],h[i])>solve(dq[1],h[i])) {
			dq.pf();
		}
		dp[i] += solve(dq.front(),h[i]);
		pair l = {-2*h[i], h[i]*h[i]+dp[i]};
		while(dq.size()>1 && intersect(l, dq[dq.size()-2]) < intersect(dq.back(), dq[dq.size()-2])) {
			dq.ppb();
		}
		dq.pb(l);
	}
	return dp[N-1];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin>>N>>C;
	h = new i64[N];
	for(int i=0;i<N;i++) {
		cin>>h[i];
	}
	cout<<solve();

	return 0;
}