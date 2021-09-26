#include <bits/stdc++.h>
#define i64 long long
#define MOD 1000000007
using namespace std;
int dp[10000][100][2], D;
string K;

int solve(int n, int d, bool limited) {
	if(n == K.length()) {
		return !d;
	}
	if(dp[n][d][limited]+1) {
		return dp[n][d][limited];
	}
	i64 ans = 0;
	for(int i=0;i<=(limited ? K[n]-'0' : 9);i++) {
		ans += solve(n+1, (d-i+D)%D, (limited and '0'+i==K[n]));
		ans %= MOD;
	}
	return dp[n][d][limited] = ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	memset(dp, -1, sizeof dp);
	cin>>K>>D;

	cout<<(solve(0, 0, true)+MOD-1)%MOD;

	return 0;
}