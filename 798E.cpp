#include <bits/stdc++.h>
#define pair pair<int, int>
#define F first
#define S second
#define pb push_back
#define mp make_pair
using namespace std;

bool comp(pair a, pair b) {
	if(a.F == b.F) {
		return a.S>b.S;
	}
	return a.F<b.F;
}

void build(int l, int r, int i, pair tree[], int b[]) {
	if(l==r) {
		tree[i] = {b[l], l};
		return;
	}
	int m = (l+r)>>1;
	build(l, m, 2*i+1, tree, b);
	build(m+1, r, 2*i+2, tree, b);
	tree[i] = max(tree[2*i+1], tree[2*i+2], comp);
}

void del(int k, int l, int r, int i, pair tree[], int b[]) {
	if(k<l || k>r) return;
	if(l==r) {
		tree[i] = {-1,l};
		return;
	}
	int m = (l+r)>>1;
	del(k, l, m, 2*i+1, tree, b);
	del(k, m+1, r, 2*i+2, tree, b);
	tree[i] = max(tree[2*i+1], tree[2*i+2], comp);
}

pair query(int a, int b, int l, int r, int i, pair tree[], int B[]) {
	if(l>b || r<a) {
		return {-1, 0};
	}
	if(l>=a && r<=b) {
		return tree[i];
	}
	int m = (l+r)/2;
	return max(query(a,b,l,m,2*i+1,tree,B), query(a,b,m+1,r,2*i+2,tree,B), comp);
}

vector<int> path;
void dfs(int u, int n, unordered_set<int> &vis, pair tree[], int a[], int b[]) {
	vis.insert(u);
	del(u, 0, n-1, 0, tree, b);
	if(b[u]!=n && !vis.count(b[u])) {
		dfs(b[u], n, vis, tree, a, b);
	}
	while(1) {
		auto it = query(0, a[u]-1, 0, n-1, 0, tree, b);
		if(it.F > u) {
			dfs(it.S, n, vis, tree, a, b);
		} else {
			break;
		}
	}
	path.pb(u);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	int n;
	cin>>n;
	int a[n], b[n];
	fill(a, a+n, n);
	fill(b, b+n, n);
	for(int i=0,j;i<n;i++) {
		cin>>j;
		if(j != -1) {
			a[i] = j-1;
			b[j-1] = i;
		}
	}
	pair tree[4*n+1];
	build(0, n-1, 0, tree, b);
	unordered_set<int> vis;
	for(int i=0;i<n;i++) {
		if(!vis.count(i)) {
			dfs(i, n, vis, tree, a, b);
		}
	}
	int ans[n];
	for(int i=0;i<n;i++) {
		ans[path[i]] = i+1;
	}
	for(int a: ans) {
		cout<<a<<' ';
	}
	return 0;
}