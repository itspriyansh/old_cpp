#include <bits/stdc++.h>
using namespace std;
vector<int> *adj;
int *dp;

int solve(int u) {
	if(adj[u].empty()) {
		return 0;
	}
	if(dp[u]) {
		return dp[u];
	}
	for(int v: adj[u]) {
		dp[u] = max(dp[u], 1+solve(v));
	}
	return dp[u];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n,m;
	cin>>n>>m;
	adj = new vector<int>[n];
	dp = new int[n];
	memset(dp, 0, n*sizeof(int));
	int x,y;
	while(m--) {
		cin>>x>>y;
		adj[x-1].push_back(y-1);
	}
	int ans = 0;
	for(int i=0;i<n;i++) {
		ans = max(ans, solve(i));
	}
	cout<<ans;

	return 0;
}