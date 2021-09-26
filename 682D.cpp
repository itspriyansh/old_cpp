#include <bits/stdc++.h>
using namespace std;
int n,m,k,dp[1001][1001][11][2];
string s,t;

int solve(int n, int m, int k, int c) {
	if(!n || !m || k==-1 || (!k && !c)) {
		return 0;
	}
	if(dp[n][m][k][c] != -1) {
		return dp[n][m][k][c];
	}
	int ans = INT_MIN;
	ans = max(ans, max(solve(n-1,m,k,0), solve(n,m-1,k,0)));
	if(s[n-1] == t[m-1]) {
		ans = max(ans, 1+solve(n-1,m-1,k-!c,1));
	}
	// cout<<"For "<<n<<", "<<m<<", "<<k<<", "<<c<<" : "<<ans<<endl;
	return dp[n][m][k][c] = ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	cin>>n>>m>>k>>s>>t;
	memset(dp, -1, sizeof(dp));
	cout<<solve(n,m,k,0);
	return 0;
}