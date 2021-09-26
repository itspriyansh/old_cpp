#include <bits/stdc++.h>
#define i64 long long
#define MOD 1000000007
using namespace std;
int N, dp[3000][3000];
string s;

int solve(int ind, int gr) {
	if(ind == N-1) {
		return 1;
	}
	if(dp[ind][gr]+1) {
		return dp[ind][gr];
	}
	i64 ans = 0;
	if(s[ind] == '>' && gr) {
		ans = ((ans+solve(ind+1, gr-1))%MOD + solve(ind, gr-1))%MOD;
	} else if(s[ind] == '<' && N-ind-1-gr) {
		ans = ((ans + solve(ind+1, gr)) % MOD + solve(ind, gr+1)) % MOD;
	}
	return dp[ind][gr] = ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin>>N>>s;
	memset(dp, -1, sizeof dp);
	i64 ans = 0;
	for(int i=1;i<=N;i++) {
		ans += solve(0, N-i);
		ans %= MOD;
	}
	cout<<ans;

	return 0;
}