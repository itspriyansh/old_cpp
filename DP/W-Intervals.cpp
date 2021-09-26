#include <bits/stdc++.h>
#define i64 long long
#define par pair<pair<int, int>, i64>
#define F first
#define S second
#define pb push_back
using namespace std;
int N,M;
i64 *tree, *lazy;
vector<par> *intervals;

void resolve(int i, int l, int r) {
	if(lazy[i]) {
		tree[i] += lazy[i];
		if(l!=r) {
			lazy[2*i+1] += lazy[i];
			lazy[2*i+2] += lazy[i];
		}
		lazy[i] = 0;
	}
}

void update(int l, int r, int a, int b, i64 val, int i=0) {
	resolve(i, l, r);
	if(l>b || r<a) {
		return;
	}
	if(l>=a && r<=b) {
		lazy[i] += val;
		resolve(i, l, r);
		return;
	}
	int m = (l+r)/2;
	update(l, m, a, b, val, 2*i+1);
	update(m+1, r, a, b, val, 2*i+2);
	tree[i] = max(tree[2*i+1], tree[2*i+2]);
}

i64 query(int l, int r, int a, int b, int i=0) {
	resolve(i, l, r);
	if(l>b || r<a) {
		return 0;
	}
	if(l>=a && r<=b) {
		return tree[i];
	}
	int m = (l+r)/2;
	return max(query(l,m,a,b,2*i+1), query(m+1,r,a,b,2*i+2));
}

i64 solve() {
	for(int i=0;i<N;i++) {
		i64 mx = i ? max(0LL, query(0, N-1, 0, i-1)) : 0;
		update(0, N-1, i, i, mx);
		for(auto score: intervals[i]) {
			update(0, N-1, score.F.F, score.F.S, score.S);
		}
	}
	return max(0LL, query(0, N-1, 0, N-1));
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin>>N>>M;
	tree = new i64[4*N+1];
	lazy = new i64[4*N+1];
	memset(tree, 0, (4*N+1)*sizeof(int));
	memset(lazy, 0, (4*N+1)*sizeof(int));
	intervals = new vector<par>[N];

	int l,r;
	i64 v;
	for(int i=0;i<M;i++) {
		cin>>l>>r>>v;
		l--;r--;
		intervals[r].pb({{l, r}, v});
	}
	cout<<solve();

	return 0;
}