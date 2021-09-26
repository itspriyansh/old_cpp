#include <bits/stdc++.h>
#define i64 long long
using namespace std;

struct node{
	i64 pf, sf, ts, ms;

	node() {
		pf = sf = ts = ms = INT32_MIN;
	}
};

i64 *ar;
node *tree;
node null;

void calculate(node &a, node &b, node &c) {
	c.pf = max(a.pf, a.ts+b.pf);
	c.sf = max(b.sf, a.sf+b.ts);
	c.ts = a.ts+b.ts;
	c.ms = max(max(a.ms, b.ms), a.sf+b.pf);
}

void build(int l, int r, int i=0) {
	if(l==r) {
		tree[i].pf = tree[i].sf = tree[i].ts = tree[i].ms = ar[l];
		return;
	}
	int m = (l+r)/2, x=2*i+1, y=2*i+2;
	build(l, m, x);
	build(m+1, r, y);
	calculate(tree[x], tree[y], tree[i]);
}

node query(int l, int r, int a, int b, int i=0) {
	if(l>b || r<a) {
		return null;
	}
	if(l>=a && r<=b) {
		return tree[i];
	}
	int m = (l+r)/2, x=2*i+1, y=2*i+2;
	node L = query(l, m, a, b, x);
	node R = query(m+1, r, a, b, y);
	node temp;
	calculate(L, R, temp);
	return temp;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	// online submission
	#endif
	int n;
	cin>>n;
	ar = new i64[n];
	tree = new node[4*n+1];
	for(int i=0;i<n;i++) {
		cin>>ar[i];
	}
	build(0, n-1);

	int q, i, j;
	cin>>q;
	while(q--) {
		cin>>i>>j;
		node ans = query(0, n-1, i-1, j-1);
		cout<<ans.ms<<'\n';
	}
	return 0;
}