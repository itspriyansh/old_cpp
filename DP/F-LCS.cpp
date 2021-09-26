#include <bits/stdc++.h>
using namespace std;
string s,t;
int dp[3001][3001], dir[3001][3001]={0};

int solve(int m, int n) {
	if(!m || !n) {
		return 0;
	}
	if(dp[m][n]+1) {
		return dp[m][n];
	}
	int ans = max(solve(m-1,n), solve(m,n-1));
	if(ans == solve(m-1,n)) {
		dir[m][n] = 1;
	}
	if(s[m-1]==t[n-1]) {
		ans = max(ans, 1+solve(m-1,n-1));
		if(ans == 1+solve(m-1,n-1)) {
			dir[m][n] = 2;
		}
	}
	return dp[m][n] = ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	memset(dp, -1, sizeof(dp));
	cin>>s>>t;
	string ans;
	int m=s.length(),n=t.length();
	solve(m, n);

	while(m && n) {
		switch(dir[m][n]) {
			case 0: {
				n--;
				break;
			}
			case 1: {
				m--;
				break;
			}
			case 2: {
				m--;
				n--;
				ans = s[m]+ans;
			}
		}
	}
	cout<<ans;
	return 0;
}