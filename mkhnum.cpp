#include<bits/stdc++.h>
using namespace std;
int *weights, *forw, L, R;
unordered_map<int, int> rev;

struct segment {
	int w;
	segment *left, *right;

	segment(int w): w(w) {
		this->left = this->right = this;
	}

	segment(int w, segment *left, segment *right): w(w), left(left), right(right) {}

	segment *update(int l, int r, int pos);
};

segment *dummy = new segment(0);
segment **tree;

segment *segment::update(int l, int r, int pos) {
	if(pos<l || pos>r) {
		return this;
	}
	if(l==r) {
		return new segment(this->w+1, dummy, dummy);
	}
	int m = (l+r)/2;
	return new segment(this->w+1, this->left->update(l, m, pos), this->right->update(m+1, r, pos));
}

int query(segment *u, segment *v, int l, int r, int ind, int k) {
	if(l==r) {
		return l;
	}
	int m = (l+r)/2;
	int sum = u->left->w - v->left->w;
	if(sum >= k) {
		return query(u->left, v->left, l, m, 2*ind+1, k);
	}
	return query(u->right, v->right, m+1, r, 2*ind+2, k-sum);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	// online submission
	#endif

	int n,m;
	cin>>n>>m;
	int ar[n];
	weights = new int[n];
	forw = new int[n];
	tree = new segment*[n];
	for(int i=0;i<n;i++) {
		cin>>ar[i];
		weights[i] = ar[i];
	}
	sort(ar, ar+n);
	L = 0, R=-1;
	for(int i=0;i<n;i++) {
		if(!i || ar[i]!=ar[i-1]) {
			rev[ar[i]] = ++R;
			forw[R] = ar[i];
		}
	}
	tree[0] = dummy->update(L, R, rev[weights[0]]);
	for(int i=1;i<n;i++) {
		tree[i] = tree[i-1]->update(L, R, rev[weights[i]]);
	}

	int u, v, w;
	while(m--) {
		cin>>u>>v>>w;
		u--;v--;
		int ans = query(tree[v], (u ? tree[u-1] : dummy), L, R, 0, w);
		cout<<forw[ans]<<'\n';
	}
	return 0;
}