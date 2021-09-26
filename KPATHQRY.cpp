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
int path[800000], tree[32000001], timein[100000], timeout[100000], height[100000], counts=0;

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

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

	int t;
	cin>>t;
	while(t--) {
		int n,a,b;
		cin>>n;
		vector<int> adj[n];
		for(int i=1;i<n;i++) {
			cin>>a>>b;
			adj[a-1].pb(b-1);
			adj[b-1].pb(a-1);
		}
		dfs(0, -1, adj);
		buildTree(0, counts-1);
		int q;
		cin>>q;
		while(q--) {
			int K;
			cin>>K;
			int cr[K];
			for(int i=0;i<K;i++) {
				cin>>cr[i];
				cr[i]--;
			}
			int a=-1,b=-1;
			for(int c: cr) {
				if(a==-1 || isAncestor(a, c)) {
					a = c;
				}
			}
			for(int c: cr) {
				if(!isAncestor(c, a) && (b==-1 || isAncestor(b, c))) {
					b = c;
				}
			}
			if(b == -1) {
				cout<<"YES\n";
				continue;
			}
			int lca = query(min(timein[a], timein[b]), max(timein[a], timein[b]), 0, counts-1);
			bool possible = true;
			for(int c: cr) {
				if((!isAncestor(c,a) && !isAncestor(c,b)) || (height[c] < height[lca])) {
					possible = false;
					break;
				}
			}
			cout<<(possible ? "YES" : "NO")<<endl;
		}
	}
	return 0;
}