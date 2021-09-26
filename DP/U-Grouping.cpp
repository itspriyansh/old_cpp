#include <bits/stdc++.h>
#define i64 long long
using namespace std;
int ar[16][16], N;
i64 dp[1<<16], sums[1<<16];
unordered_map<int, int> ln;

i64 solve(int mask) {
	if(!mask) {
		return 0;
	}
	if(dp[mask] != INT64_MIN) {
		return dp[mask];
	}

	for(int i=mask;i;i=(i-1)&mask) {
		i64 sum = solve(mask - i) + sums[i];
		dp[mask] = max(dp[mask], sum);
	}
	return dp[mask];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	for(int i=0;i<=16;i++) {
		ln[1<<i] = i;
	}
	fill(dp, dp+(1<<16), INT64_MIN);
	cin>>N;
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			cin>>ar[i][j];
		}
	}
	for(int i=0,l=(1<<N);i<l;i++) {
		sums[i] = 0;
		for(int j=0;j<N;j++) {
			if(!(i&(1<<j))) continue;
			for(int k=j+1;k<N;k++) {
				if(i&(1<<k)) {
					sums[i] += ar[j][k];
				}
			}
		}
	}
	cout<<solve((1<<N)-1);

	return 0;
}