#include <bits/stdc++.h>
using namespace std;
double dp[301][301][301];
int n;

double solve(int x, int y, int z) {
	if(x<0 || y<0 || z<0) {
		return 0;
	}
	if(!x && !y && !z) {
		return 0;
	}
	if(dp[x][y][z] > -0.9) {
		return dp[x][y][z];
	}
	return dp[x][y][z] = (n+x*solve(x-1,y,z)+y*solve(x+1,y-1,z)+z*solve(x,y+1,z-1))/(x+y+z);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	memset(dp, -1, sizeof dp);
	cin>>n;
	int cnt[4]={0},a;
	for(int i=0;i<n;i++) {
		cin>>a;
		cnt[a]++;
	}
	cout<<fixed<<setprecision(10)<<solve(cnt[1],cnt[2],cnt[3]);

	return 0;
}