#include <bits/stdc++.h>
#define i64 long long
using namespace std;
i64 sum[401] = {0};
i64 dp[400][400];

i64 solve(int x, int y) {
	if(x == y) {
		return 0;
	}
	if(dp[x][y]+1) {
		return dp[x][y];
	}
	i64 ans = INT64_MAX, add = sum[y+1]- sum[x];
	for(int i=x;i<y;i++) {
		ans = min(ans, add+solve(x,i)+solve(i+1,y));
	}
	return dp[x][y] = ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	memset(dp, -1, sizeof dp);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>sum[i];
		if(i) sum[i] += sum[i-1];
	}
	cout<<solve(0,n-1);

	return 0;
}