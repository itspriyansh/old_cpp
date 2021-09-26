#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define MOD 1000000007
#define pair pair<int, int>
#define pb push_back
#define endl '\n'
using namespace std;
int path[2000000], tree[80000001], timein[100000], timeout[100000], height[100000], counts=0;

void dfs(int u, int p, vector<int> adj[], int h=1) {
	timein[u] = counts;
	path[counts++] = u;
	height[u] = h;
	for(int v: adj[u]) {
		if(p==v) continue;
		dfs(v, u, adj, h+1);
		path[counts++] = u;
	}
	timeout[u] = counts;
	path[counts++] = u;
}

bool isAncestor(int p, int u) {
	return timein[p] <= timein[u] && timeout[p] >= timeout[u];
}

void buildTree(int l, int r, int i=0) {
	if(l==r) {
		tree[i] = path[l];
		return;
	}
	int m = (l+r)/2;
	buildTree(l, m, 2*i+1);
	buildTree(m+1, r, 2*i+2);
	int x = tree[2*i+1], y = tree[2*i+2];
	tree[i] = (height[x] <= height[y] ? x : y);
}

int query(int a, int b, int l, int r, int i=0) {
	if(l>b || r<a) {
		return -1;
	}
	if(l>=a && r<=b) {
		return tree[i];
	}
	int m = (l+r)/2;
	int x = query(a, b, l, m, 2*i+1);
	int y = query(a, b, m+1, r, 2*i+2);
	if(x==-1) return y;
	if(y==-1) return x;
	return (height[x] <= height[y] ? x : y);
}

void scanint(int &x) {
    register int c = getchar_unlocked();
    x = 0;
    for(;(c<48 || c>57);c = getchar_unlocked());
    for(;c>47 && c<58;c = getchar_unlocked()) {x = (x<<1) + (x<<3) + c - 48;}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	//fastio

	int t;
	cin>>t;
	while(t--) {
		int n,a,b,q;
		scanint(n);
		scanint(q);
		vector<int> adj[n];
		for(int i=1;i<n;i++) {
			scanint(a);
			scanint(b);
			adj[a-1].pb(b-1);
			adj[b-1].pb(a-1);
		}
		dfs(0, -1, adj);
		buildTree(0, counts-1);
		while(q--) {
			int k,d,ans=0;
			cin>>k>>d;
			int cr[k];
			for(int i=0;i<k;i++) {
				scanint(cr[i]);
				cr[i]--;
				for(int j=0;j<i;j++) {
					int lca = query(min(timein[cr[i]], timein[cr[j]]), max(timein[cr[i]], timein[cr[j]]), 0, counts-1);
					if(height[cr[i]]+height[cr[j]] == d + 2*height[lca]) {
						ans++;
					}
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}