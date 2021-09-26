#include <bits/stdc++.h>
#define i64 long long
using namespace std;
int ar[3000];
i64 dp[3000][3000];

i64 solve(int l, int r) {
	if(l>r) {
		return 0;
	}
	if(l==r) {
		return ar[l];
	}
	if(dp[l][r]+1) {
		return dp[l][r];
	}
	i64 ans = max( min(solve(l+2,r),solve(l+1,r-1))+ar[l], min(solve(l+1,r-1),solve(l,r-2))+ar[r] );
	return dp[l][r] = ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	memset(dp, -1, sizeof dp);
	int n;
	cin>>n;
	i64 total = 0;
	for(int i=0;i<n;i++) {
		cin>>ar[i];
		total += ar[i];
	}
	i64 points = solve(0, n-1);
	cout<<2*points-total;

	return 0;
}