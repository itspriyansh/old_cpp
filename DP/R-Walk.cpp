#include <bits/stdc++.h>
#define i64 long long
#define MOD 1000000007
using namespace std;
int adj[50][50];

void multiply(int a[][50], int b[][50], int n) {
	int c[n][n];
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			c[i][j] = 0;
			for(int k=0;k<n;k++) {
				c[i][j] = ((i64)a[i][k] * b[k][j] + c[i][j]) % MOD;
			}
		}
	}
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			a[i][j] = c[i][j];
		}
	}
}

i64 power(int n, i64 k) {
	int res[n][50] = {0};
	for(int i=0;i<n;i++) {
		res[i][i] = 1;
	}
	while(k) {
		if(k&1) {
			multiply(res, adj, n);
		}
		k >>= 1;
		multiply(adj, adj, n);
	}
	i64 ans = 0;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			ans += res[i][j];
			ans %= MOD;
		}
	}
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n;
	i64 k;
	cin>>n>>k;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cin>>adj[i][j];
		}
	}
	cout<<power(n,k);

	return 0;
}