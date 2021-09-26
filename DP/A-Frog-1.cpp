#include <bits/stdc++.h>
using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n;
	cin>>n;
	int h[n];
	long long dp[n] = {0};
	for(int i=0;i<n;i++) {
		cin>>h[i];
		dp[i] = 0;
		if(i) {
			dp[i] = dp[i-1] + abs(h[i]-h[i-1]);
		}
		if(i-1) {
			dp[i] = min(dp[i], dp[i-2] + abs(h[i]-h[i-2]));
		}
	}
	cout<<dp[n-1];
	return 0;
}