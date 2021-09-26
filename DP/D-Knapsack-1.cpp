#include <bits/stdc++.h>
#define i64 long long
using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n,w;
	cin>>n>>w;
	int W[n];
	i64 v[n], dp[w+1][n];
	memset(dp, 0, sizeof(dp));

	for(int i=0;i<n;i++) {
		cin>>W[i]>>v[i];
	}

	for(int i=1;i<=w;i++) {
		for(int j=0;j<n;j++) {
			if(!j) {
				if(i >= W[j]) {
					dp[i][j] = v[j];
				}
				continue;
			}
			dp[i][j] = dp[i][j-1];
			if(i >= W[j]) {
				dp[i][j] = max(dp[i][j], dp[i-W[j]][j-1]+v[j]);
			}
		}
	}
	cout<<dp[w][n-1];

	return 0;
}