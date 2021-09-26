#include <bits/stdc++.h>
#define i64 unsigned long long
using namespace std;
int n,k,*ar,dp[100001];

int mex(i64 mask1, i64 mask2) {
	if(!mask1) {
		return 64+log2(mask2 & -mask2);
	}
	return log2(mask1 & -mask1);
}

int solve(int a) {
	if(!a) {
		return 0;
	}
	if(dp[a]+1) {
		return dp[a];
	}
	i64 mask1 = 0, mask2 = 0;
	for(int i=0;i<n && ar[i]<=a;i++) {
		int shift = solve(a-ar[i]);
		if(shift<64) {
			mask1 |= 1LL<<shift;
		} else {
			mask2 |= 1ll<<(shift-64);
		}
	}
	return dp[a] = mex(~mask1, ~mask2);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	memset(dp, -1, sizeof dp);
	cin>>n>>k;
	ar = new int[n];
	for(int i=0;i<n;i++) {
		cin>>ar[i];
	}
	sort(ar, ar+n);
	cout<<(solve(k) ? "First" : "Second");

	return 0;
}