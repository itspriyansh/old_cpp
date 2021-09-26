#include <bits/stdc++.h>
#define pb push_back
#define MOD 1000000007
#define i64 long long
#define pair pair<int, int>
#define F first
#define S second
using namespace std;

void dfs(int u, vector<int> adj[], pair points[], i64 &ans, int p=-1) {
	if(p!=-1) {
		points[u].F = (points[p].F*2 + 1) % MOD;
	}
	ans = (ans + points[u].F) % MOD;
	for(int v: adj[u]) {
		if(v==p) continue;
		dfs(v, adj, points, ans, u);
		int back = (points[v].S * 2 + 1) % MOD;
		points[u].F = (points[u].F + back) % MOD;
		points[u].S = (points[u].S + back) % MOD;
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int t;cin>>t;while(t--) {
		int n;
		cin>>n;
		vector<int> adj[n];
		int a,b;
		pair points[n];;
		memset(points, 0, sizeof points);
		for(int i=1;i<n;i++) {
			cin>>a>>b;
			adj[a-1].pb(b-1);
			adj[b-1].pb(a-1);
		}
		i64 ans = n;
		dfs(0, adj, points, ans);
		cout<<ans<<'\n';
	}

	return 0;
}