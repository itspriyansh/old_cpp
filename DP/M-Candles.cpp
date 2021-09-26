#include <bits/stdc++.h>
#define i64 long long
#define MOD 1000000007
using namespace std;
int dp[101][100001], ar[100], n, k;

int solve(int n, int k) {
	if(!k) {
		return 1;
	}
	if(!n) {
		return k ? 0 : 1;
	}
	if(dp[n][k]+1) {
		return dp[n][k];
	}
	i64 ans = ((i64)solve(n,k-1) + solve(n-1,k) - (k>ar[n-1] ? solve(n-1,k-ar[n-1]-1) : 0)+MOD) % MOD;
	return dp[n][k] = ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	memset(dp, -1, sizeof dp);
	cin>>n>>k;
	for(int i=0;i<n;i++) {
		cin>>ar[i];
	}
	cout<<solve(n,k);

	return 0;
}