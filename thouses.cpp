#include <bits/stdc++.h>
#define i64 long long
#define pb push_back
#define pair pair<i64, int>
#define F first
#define S second
#define MOD 1000000007LL
using namespace std;

i64 dummy;
i64 dfs(int u, vector<pair> adj[], int p=-1) {
    i64 child = 1;
    for(int i=0;i<adj[u].size();i++) {
        auto &v = adj[u][i];
        if(v.S==p) continue;
        dummy = dfs(v.S, adj, u);
        v.F = dummy;
    }
    sort(adj[u].begin(), adj[u].end(), greater<pair>());
    for(int i=0;i<adj[u].size();i++) {
        auto &v = adj[u][i];
        if(v.S==p) continue;
        child += v.F * (i+1);
    }
    return child;
}

void solve(int u, i64 &ans, vector<pair> adj[], i64 score[], int p=-1) {
    if(!score[u]) return;
    ans = (ans + score[u]) % MOD;
    i64 avail[adj[u].size()];
    avail[0] = score[u] % MOD;
    for(int i=1;i<adj[u].size();i++) {
        avail[i] = (score[u] + avail[i-1]) % MOD;
    }
    for(int i=0,j=0;i<adj[u].size();i++) {
    	if(adj[u][i].S == p) continue;
        score[adj[u][i].S] = avail[j++];
        solve(adj[u][i].S, ans, adj, score, u);
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int t;cin>>t;while(t--) {
        int n;
        i64 x;
        cin>>n>>x;
        i64 ans = 0;
        vector<pair> adj[n];
        i64 score[n];
        score[0] = x%MOD;
        int a,b;
        for(int i=1;i<n;i++) {
            cin>>a>>b;
            adj[a-1].pb({0, b-1});
            adj[b-1].pb({0, a-1});
        }
        dfs(0, adj);
        solve(0, ans, adj, score);
        cout<<ans<<'\n';
    }

	return 0;
}