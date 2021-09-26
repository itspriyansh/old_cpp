#include <bits/stdc++.h>
using namespace std;
double p[2999], dp[3000][3000];

double solve(int n, int t) {
	if(t<0 || t>n) {
		return 0.0;
	}
	if(!n) {
		return t ? 0.0 : 1.0;
	}
	if(dp[n][t]+1) {
		return dp[n][t];
	}
	return dp[n][t] = solve(n-1, t-1)*p[n-1]+solve(n-1, t)*(1.00-p[n-1]);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n;
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>p[i];
		fill(dp[i+1], dp[i+1]+i+2, -1);
	}
	double ans = 0;
	for(int i=(n+1)/2;i<=n;i++) {
		ans += solve(n, i);
	}
	cout<<fixed<<setprecision(10)<<ans;

	return 0;
}