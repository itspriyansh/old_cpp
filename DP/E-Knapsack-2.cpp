#include <bits/stdc++.h>
#define i64 long long
using namespace std;
int N,W,v[100];
i64 w[100],dp[100001][100];

i64 solve(int val, int n) {
	if(!val) {
		return 0;
	}
	if(!n) {
		return val==v[n] ? w[n] : INT_MAX;
	}
	if(dp[val][n]+1) {
		return dp[val][n];
	}
	i64 ans = solve(val, n-1);
	if(val >= v[n]) {
		ans =  min(ans, w[n]+solve(val-v[n],n-1));
	}
	return dp[val][n] = ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	memset(dp, -1, sizeof(dp));
	cin>>N>>W;	
	for(int i=0;i<N;i++) {
		cin>>w[i]>>v[i];
	}
	int ans = 0;
	for(int val=0;val<=100000;val++) {
		if(solve(val, N-1)<=W) {
			ans = val;
		}
	}
	cout<<ans;

	return 0;
}