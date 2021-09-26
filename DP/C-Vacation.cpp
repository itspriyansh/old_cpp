#include <bits/stdc++.h>
#define i64 long long
using namespace std;
i64 dp[100001][3] = {0};
int n,*a,*b,*c;

i64 solve(int n, int k) {
	if(!n) {
		return !k ? a[n] : k==1 ? b[n] : c[n];
	}
	if(dp[n][k]) {
		return dp[n][k];
	}
	i64 ans = 0;
	int add = !k ? a[n] : k==1 ? b[n] : c[n];
	for(int i=0;i<3;i++) {
		if(k!=i) {
			ans = max(ans, solve(n-1, i) + add);
		}
	}
	return dp[n][k] = ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	memset(dp, 0, sizeof(dp));
	cin>>n;
	a = new int[n];
	b = new int[n];
	c = new int[n];
	for(int i=0;i<n;i++) {
		cin>>a[i]>>b[i]>>c[i];
	}
	cout<<max(solve(n-1, 0), max(solve(n-1, 1), solve(n-1 ,2)))<<endl;

	return 0;
}