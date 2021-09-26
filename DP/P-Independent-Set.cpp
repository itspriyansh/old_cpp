#include <bits/stdc++.h>
#define i64 long long
#define MOD 1000000007LL
#define pb push_back
using namespace std;
vector<int> *adj;
int dp[100000][2];

int solve(int u, int p, int color) {
	if(adj[u].empty() or (adj[u].size()==1 and adj[u][0] == p)) {
		return !color+1;
	}
	if(dp[u][!color]+1) {
		return (dp[u][0] + (!color ? dp[u][1] : 0)) % MOD;
	}
	i64 ans1 = 1, ans2 = 1;
	for(int v: adj[u]) {
		if(v != p) {
			ans1 = (ans1 * solve(v, u, 0)) % MOD;
			ans2 = (ans2 * solve(v, u, 1)) % MOD;
		}
	}
	dp[u][0] = ans1;
	dp[u][1] = ans2;
	return (dp[u][0] + (!color ? dp[u][1] : 0)) % MOD;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	memset(dp, -1, sizeof dp);
	int n,x,y;
	cin>>n;
	adj = new vector<int>[n];
	for(int i=0;i<n-1;i++) {
		cin>>x>>y;
		adj[x-1].pb(y-1);
		adj[y-1].pb(x-1);
	}
	cout<<solve(0, -1, 0);
	return 0;
}