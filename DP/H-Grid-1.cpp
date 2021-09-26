#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n,m;
	cin>>n>>m;
	string str;
	int dp[n][m];

	for(int i=0;i<n;i++) {
		cin>>str;
		for(int j=0;j<m;j++) {
			if(str[j] == '#') {
				dp[i][j] = 0;
			} else {
				dp[i][j] = !i && !j ? 1 : !i ? dp[i][j-1] : !j ? dp[i-1][j] : (dp[i-1][j]+dp[i][j-1]) % MOD;
			}
		}
	}
	cout<<dp[n-1][m-1];

	return 0;
}