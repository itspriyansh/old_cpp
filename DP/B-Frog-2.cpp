#include <bits/stdc++.h>
using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n,k;
	cin>>n>>k;
	int h[n];
	long long dp[n] = {0};

	for(int i=0;i<n;i++) {
		cin>>h[i];
		if(i) dp[i] = INT_MAX;
		for(int j=i-1;j>=0 && j>=i-k;j--) {
			dp[i] = min(dp[i], dp[j] + abs(h[i]-h[j]));
		}
	}
	cout<<dp[n-1];
	return 0;
}