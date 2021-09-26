#include <bits/stdc++.h>
#define i64 long long
#define MOD 1000000007LL
using namespace std;
i64 *shift, *tree, *lazy;

void update(int l, int r, int a, int b, int val, int ind=0) {
	if(lazy[ind] != -1) {
		tree[ind] = lazy[ind] ? (shift[r-l+1]-1+MOD)%MOD : 0;
		if(l<r) {
			lazy[2*ind+1] = lazy[2*ind+2] = lazy[ind];
		}
		lazy[ind] = -1;
	}
	if(l>b || r<a) {
		return;
	}
	if(l>=a && r<=b) {
		tree[ind] = val ? (shift[r-l+1]-1+MOD)%MOD : 0;
		if(l<r) {
			lazy[2*ind+1] = lazy[2*ind+2] = val;
		}
		return;
	}
	int m = (l+r)/2;
	update(l, m, a, b, val, 2*ind+1);
	update(m+1, r, a, b, val, 2*ind+2);
	tree[ind] = ((tree[2*ind+1] * shift[r-m])%MOD + tree[2*ind+2]) % MOD;
}

i64 query(int l, int r, int a, int b, int ind=0) {
	if(l>b || r<a) {
		return 0;
	}
	if(!lazy[ind] || !tree[ind]) {
		return 0;
	}
	if(lazy[ind] == 1 || tree[ind] == (shift[r-l+1]-1+MOD)%MOD) {
		int c=max(l,a), d=min(r,b);
		return (((shift[d-c+1]-1+MOD)%MOD) * shift[b-d] ) %MOD;
	}
	if(l>=a && r<=b) {
		return tree[ind] * shift[b-r];
	}
	int m = (l+r)/2;
	return (query(l, m, a, b, 2*ind+1) + query(m+1, r, a, b, 2*ind+2) ) %MOD;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	// online submission
	#endif
	int n,q;
	cin>>n>>q;
	shift = new i64[n+1];
	shift[0] = 1LL;
	for(int i=1;i<=n;i++) {
		shift[i] = (shift[i-1]<<1) % MOD;
	}
	tree = new i64[4*n+1];
	lazy = new i64[4*n+1];
	for(int i=0;i<4*n+1;i++) {
		tree[i] = 0;
		lazy[i] = -1;
	}
	int i,j,k;
	while(q--) {
		cin>>i>>j>>k;
		switch(i) {
			case 0:
			case 1:
			update(0, n-1, j, k, i);
			break;
			case 2:
			cout<<query(0, n-1, j, k)<<'\n';
			break;
		}
	}
	return 0;
}