#include <bits/stdc++.h>
using namespace std;

void build(int ar[][2][2], int tree[][2][2], int l, int r, int R, int ind=0) {
	if(l == r) {
		for(int j=0;j<2;j++) {
			for(int k=0;k<2;k++) {
				tree[ind][j][k] = ar[l][j][k];
			}
		}
		return;
	}
	int m = (l+r)/2;
	build(ar, tree, l, m, R, 2*ind+1);
	build(ar, tree, m+1, r, R, 2*ind+2);
	for(int j=0;j<2;j++) {
		for(int k=0;k<2;k++) {
			tree[ind][j][k] = 0;
			for(int m=0;m<2;m++) {
				tree[ind][j][k] = (tree[ind][j][k] + ( tree[2*ind+1][j][m] * tree[2*ind+2][m][k] ) %R ) %R;
			}
		}
	}
}

int one[][2] = {{1,0}, {0,1}};
int pack[2][2];

int (*query(int ar[][2][2], int tree[][2][2], int l, int r, int a, int b, int R, int ind=0))[2] {
	if(l>b || r<a) {
		return one;
	}
	if(l>=a && r<=b) {
		return tree[ind];
	}
	int m = (l+r)/2;
	int (*ll)[2] = query(ar, tree, l, m, a, b, R, 2*ind+1);
	int LL[2][2];
	for(int j=0;j<2;j++) {
		for(int k=0;k<2;k++) {
			LL[j][k] = ll[j][k];
		}
	}
	int (*RR)[2] = query(ar, tree, m+1, r, a, b, R, 2*ind+2);
	int ans[2][2] = {0};
	for(int j=0;j<2;j++) {
		for(int k=0;k<2;k++) {
			ans[j][k] = 0;
			for(int m=0;m<2;m++) {
				ans[j][k] = (ans[j][k] + ( LL[j][m] * RR[m][k] ) %R ) %R;
			}
		}
	}
	for(int j=0;j<2;j++) {
		for(int k=0;k<2;k++) {
			pack[j][k] = ans[j][k];
		}
	}
	return pack;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	// online submission
	#endif

	int r, n, q;
	cin>>r>>n>>q;
	string garbage;
	int ar[n][2][2], tree[4*n+1][2][2];
	for(int i=0;i<n;i++) {
		for(int j=0;j<2;j++) {
			for(int k=0;k<2;k++) {
				cin>>ar[i][j][k];
			}
		}
		getline(cin, garbage);
	}
	build(ar, tree, 0, n-1, r);

	int i, j;
	while(q--) {
		cin>>i>>j;
		int (*ans)[2] = query(ar, tree, 0, n-1, i-1, j-1, r);
		cout<<ans[0][0]<<" "<<ans[0][1]<<'\n'<<ans[1][0]<<" "<<ans[1][1]<<'\n';
		cout<<'\n';
	}
	return 0;
}