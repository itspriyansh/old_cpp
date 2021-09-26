#include <bits/stdc++.h>
#define pb push_back
using namespace std;

unordered_map<int,int> revers, firstOcc, height;
int *forwar, *parents, *pathTree, L, R, *weights;
vector<int> *adj, path;
unordered_set<int> vis;

void scanint(int &x)
{
    register int c = getchar_unlocked();
    x = 0;
    for(;(c<48 || c>57);c = getchar_unlocked());
    for(;c>47 && c<58;c = getchar_unlocked()) {x = (x<<1) + (x<<3) + c - 48;}
}

struct segment {
	int w;
	segment *left, *right;

	segment(int w): w(w) {
		this->left = this;
		this->right = this;
	}

	segment(int w, segment *left, segment *right): w(w), left(left), right(right) {}

	segment *update(int l, int r, int pos, int val);
};

segment *dummy = new segment(0);
segment **tree;

segment* segment::update(int l, int r, int pos, int val=1) {
	if(l>pos || r<pos) {
		return this;
	}
	if(l == r) {
		return new segment(this->w+val, dummy, dummy);
	}
	int m = (l+r)/2;
	return new segment(this->w+val, this->left->update(l, m, pos, val), this->right->update(m+1, r, pos, val));
}

void dfs(int u, segment *par=dummy, int h=1) {
	vis.insert(u);
	path.pb(u);
	firstOcc[u] = path.size()-1;
	height[u] = h;
	tree[u] = par->update(L, R, revers[weights[u]]);

	for(int v: adj[u]) {
		if(!vis.count(v)) {
			parents[v] = u;
			dfs(v, tree[u], h+1);
			path.pb(u);
		}
	}
}

void buildPathTree(int l, int r, int ind=0) {
	if(l==r) {
		pathTree[ind] = path[l];
		return;
	}
	int m = (l+r)/2;
	buildPathTree(l, m, 2*ind+1);
	buildPathTree(m+1, r, 2*ind+2);
	if(height[pathTree[2*ind+1]] < height[pathTree[2*ind+2]]) {
		pathTree[ind] = pathTree[2*ind+1];
	} else {
		pathTree[ind] = pathTree[2*ind+2];
	}
}

int queryPathTree(int l, int r, int a, int b, int ind = 0) {
	if(b<a) {
		swap(a,b);
	}
	if(r<a || l>b) {
		return -1;
	}
	if(l>=a && r<=b) {
		return pathTree[ind];
	}
	int m = (l+r)/2;
	int ll = queryPathTree(l, m, a, b, 2*ind+1);
	int rr = queryPathTree(m+1, r, a, b, 2*ind+2);
	if(ll == -1) return rr;
	if(rr == -1) return ll;
	return (height[ll] < height[rr] ? ll : rr);
}

int query(segment *u, segment *v, segment *p, segment *g, int l, int r, int k) {
	if(l == r) {
		return l;
	}
	int m = (l+r)/2;
	int sum = u->left->w + v->left->w - p->left->w - g->left->w;
	if(sum >= k) {
		return query(u->left, v->left, p->left, g->left, l, m, k);
	}
	return query(u->right, v->right, p->right, g->right, m+1, r, k-sum);
}

int main() {
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	// #else
	// // online submission
	// #endif
	int n,m;
	scanint(n);
	scanint(m);
	int ar[n];
	weights = new int[n];
	for(int i=0;i<n;i++) {
		scanint(ar[i]);
		weights[i] = ar[i];
	}
	sort(ar, ar+n);
	forwar = new int[n];
	L=0, R=0;
	for(int i=0;i<n;i++) {
		if(!i || ar[i]!=ar[i-1]) {
			revers[ar[i]] = R;
			forwar[R++] = ar[i];
		}
	}
	R--;

	parents = new int[n];
	tree = new segment*[n];
	parents[0] = -1;
	adj = new vector<int>[n];
	path.reserve(3*n);

	int u,v,w;
	for(int i=0;i<n-1;i++) {
		scanint(u);
		scanint(v);
		adj[u-1].pb(v-1);
		adj[v-1].pb(u-1);
	}

	dfs(0);
	pathTree = new int[4*path.size()+1];
	buildPathTree(0, path.size()-1);


	while(m--) {
		scanint(u);
		scanint(v);
		scanint(w);
		u--;v--;
		int pi = queryPathTree(0, path.size()-1, firstOcc[u], firstOcc[v]);
		segment *parent = tree[pi];
		int ans = query(tree[u], tree[v], parent, (parents[pi] != -1 ? tree[parents[pi]] : dummy), L, R, w);
		printf("%d\n", forwar[ans]);
	}
	return 0;
}