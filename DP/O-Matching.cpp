#include <bits/stdc++.h>
#define i64 long long
#define MOD 1000000007LL
using namespace std;
int dp[1LL<<22][22];
int ar[22][22], n;

int solve(int a, i64 mask) {
	if(!mask) {
		return 1;
	}
	if(dp[mask][a]+1) {
		return dp[mask][a];
	}
	i64 ans = 0;
	i64 m = mask;
	while(m) {
		int k = m & -m, ind = log2(k);
		if(ar[a][ind]) {
			ans = (ans + solve(a-1, mask-k)) % MOD;
		}
		m -= k;
	}
	return dp[mask][a] = ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	memset(dp, -1, sizeof dp);
	cin>>n;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cin>>ar[i][j];
		}
	}
	cout<<solve(n-1, (1LL<<n)-1);

	return 0;
}