#include <bits/stdc++.h>
#define pb push_back
using namespace std;
vector<int> *adj;
int *low, *timein;
unordered_set<int> vis;
bool breakable = false;

void dfs(int u=0, int par=0) {
	static int tt = -1;
	timein[u] = ++tt;
	vis.insert(u);
	low[u] = timein[u];
	int count = 0;
	for(int v: adj[u]) {
		if(!vis.count(v)) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(timein[u] <= low[v]) {
				count++;
				if(count>1 || u) {
					breakable = true;
				}
			}
		} else {
			low[u] = min(low[u], timein[v]);
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int m,n;
	cin>>m>>n;
	int ar[m][n];
	char C;
	int len = 0;
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) {
			cin>>C;
			ar[i][j] = (C=='d' ? ++len : 0);
		}
	}
	adj = new vector<int>[len];
	low = new int[len];
	timein = new int[len];
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) {
			if(ar[i][j]) {
				int u = ar[i][j]-1;
				for(int k=-1;k<=1;k+=2) {
					if(i+k>=0 && i+k<m && ar[i+k][j]) {
						adj[u].pb(ar[i+k][j]-1);
					}
					if(j+k>=0 && j+k<n && ar[i][j+k]) {
						adj[u].pb(ar[i][j+k]-1);
					}
				}
			}
		}
	}
	dfs();
	if(vis.size() < len) {
		cout<<0;
	} else if(breakable) {
		cout<<1;
	} else {
		cout<<2;
	}
	return 0;
}