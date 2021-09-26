#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define MOD 1000000007
#define pair pair<int, int>
#define pb push_back
#define inf INT32_MAX
#define endl '\n'
using namespace std;

vector<int> adj[100000];
int dist[100000], first[100000], height[100000];
vector<int> path;
int *tree;

void dfs(int u, int p=-1, int h=0) {
	dist[u] = height[u] = h;
	first[u] = path.size();
	path.pb(u);
	for(int v: adj[u]) {
		if(v==p) continue;
		dfs(v, u, h+1);
		path.pb(u);
	}
}



void bfs(int n) {
	queue<int> q;
	q.push(n);
	dist[n] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v: adj[u]) {
			if(dist[v] > dist[u]+1) {
				dist[v] = dist[u]+1;
				q.push(v);
			}
		}
	}
}

void build(int l, int r, int i=0) {
	if(l==r) {
		tree[i] = path[l];
		return;
	}
	int m = (l+r)/2;
	build(l, m, 2*i+1);
	build(m+1, r, 2*i+2);
	tree[i] = height[tree[2*i+1]] < height[tree[2*i+2]] ? tree[2*i+1] : tree[2*i+2];
}

int query(int a, int b, int l, int r, int i=0) {
	if(l>b || r<a) {
		return inf;
	}
	if(l>=a && r<=b) {
		return tree[i];
	}
	int m = (l+r)/2;
	int x = query(a,b,l,m,2*i+1);
	int y = query(a,b,m+1,r,2*i+2);
	if(x==inf) return y;
	if(y==inf) return x;
	return height[x]<height[y] ? x : y;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n,Q;
	cin>>n>>Q;
	int a,b;
	for(int i=1;i<n;i++) {
		cin>>a>>b;
		adj[a-1].pb(b-1);
		adj[b-1].pb(a-1);
	}
	dfs(0);
	tree = new int[4*path.size()+1];
	build(0, path.size()-1);
	int step = sqrt(Q);
	vector<int> qu;
	for(int q=0;q<Q;q++) {
		if(q%step == 0) {
			while(!qu.empty()) {
				int u = qu.back();
				qu.pop_back();
				bfs(u);
			}
		}
		int x,y;
		cin>>x>>y;
		y--;
		if(!x) {
			int ans = dist[y];
			for(int v: qu) {
				int p = query(min(first[y], first[v]), max(first[y], first[v]), 0, path.size()-1);
				ans = min(ans, height[y]+height[v]-2*height[p]);
			}
			cout<<ans<<'\n';
		} else {
			qu.pb(y);
		}
	}
	return 0;
}