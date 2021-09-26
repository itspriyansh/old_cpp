#include <bits/stdc++.h>
#define i64 long long
using namespace std;
int N;
i64 M;
vector<int> *adj;
i64 *dp1, *dp2;

void iteration1(int u, int p) {
	i64 ans = 1;
	for(int v: adj[u]) {
		if(v != p) {
			iteration1(v, u);
			ans = (ans*(dp1[v]+1)%M)%M;
		}
	}
	dp1[u] = ans;
}

void iteration2(int u, int p, i64 pa) {
	dp2[u] = (dp1[u] * (pa+1)) % M;
	int n = adj[u].size()-(p!=-1);
	i64 prefix[n], suffix[n];
	if(n) prefix[0] = suffix[n-1] = 1;
	for(int i=0,j=0;i<n;i++,j++) {
		if(adj[u][j]==p) {
			i--;
			continue;
		}
		if(i+1<n) prefix[i+1] = (dp1[adj[u][j]]+1)%M;
		if(i) suffix[i-1] = (dp1[adj[u][j]]+1)%M;
	}
	for(int i=1;i<n;i++) {
		prefix[i] = (prefix[i] * prefix[i-1]) % M;
	}
	for(int i=n-2;i>=0;i--) {
		suffix[i] = (suffix[i] * suffix[i+1]) % M;
	}
	for(int i=0,j=0;i<n;i++,j++) {
		int v = adj[u][j];
		if(v == p) {
			i--;
			continue;
		}
		i64 ans = ((prefix[i] * suffix[i])%M * (pa+1)%M) % M;
		iteration2(v, u, ans);
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin>>N>>M;
	adj = new vector<int>[N];
	int x,y;
	for(int i=1;i<N;i++) {
		cin>>x>>y;
		adj[x-1].push_back(y-1);
		adj[y-1].push_back(x-1);
	}
	dp1 = new i64[N];
	dp2 = new i64[N];
	iteration1(0, -1);
	iteration2(0, -1, 0);
	for(int i=0;i<N;i++) {
		cout<<dp2[i]<<endl;
	}

	return 0;
}