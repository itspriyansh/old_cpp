#include <bits/stdc++.h>
#define pb push_back
using namespace std;

int n, m, *par, **sparse, *timein, *timeout;
vector<int> *adj;

void dfs(int u) {
	static int tt = -1;
	timein[u] = ++tt;
	sparse[u][0] = par[u];
	for(int j=1;j<m;j++) {
		sparse[u][j] = sparse[sparse[u][j-1]][j-1];
	}
	for(int v: adj[u]) {
		dfs(v);
	}
	timeout[u] = tt;
}

bool isAncestor(int a, int b) {
	return timein[a]<=timein[b] && timeout[a]>=timeout[b];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int t;cin>>t;
	for(int c=1;c<=t;c++) {
		printf("Case %d:\n", c);
		cin>>n;
		m = log2(n)+1;
		adj = new vector<int>[n];
		par = new int[n];
		par[0] = 0;
		sparse = new int*[n];
		timein = new int[n];
		timeout = new int[n];
		int x, y;
		for(int i=0;i<n;i++) {
			sparse[i] = new int[m];
			//sparse[i][0] = par[i];
			cin>>x;
			while(x--) {
				cin>>y;
				par[y-1]=i;
				adj[i].pb(y-1);
			}
		}
		dfs(0);
		int q;
		cin>>q;
		while(q--) {
			cin>>x>>y;
			x--;y--;
			if(isAncestor(x, y)) {
				cout<<x+1<<'\n';
			} else if(isAncestor(y, x)) {
				cout<<y+1<<'\n';
			} else {
				for(int j=m-1;j>=0;j--) {
					int p = sparse[x][j];
					if(!isAncestor(p,y)) {
						x = p;
					}
				}
				cout<<par[x]+1<<'\n';
			}
		}
	}
	return 0;
}