#include <bits/stdc++.h>
#define i64 long long
using namespace std;

struct Block {
	int w;
	int s;
	i64 v;
};

Block *ar;
i64 dp[1000][10001];
int N;

i64 solve(int n, int w) {
	if(w>10000) {
		return 0;
	}
	if(!n) {
		return ar[n].s >= w ? ar[n].v : 0;
	}
	if(dp[n][w]+1) {
		return dp[n][w];
	}
	i64 val1 = solve(n-1, w);
	i64 val2 = ar[n].s >= w ? ar[n].v+solve(n-1, w+ar[n].w) : 0;
	return dp[n][w] = max(val1, val2); 
}

bool comp(Block &a, Block &b) {
	return a.w+a.s > b.w+b.s;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin>>N;
	ar = new Block[N];
	for(int i=0;i<N;i++) {
		cin>>ar[i].w>>ar[i].s>>ar[i].v;
	}
	memset(dp, -1LL, sizeof dp);
	sort(ar, ar+N, comp);

	cout<<solve(N-1, 0);

	return 0;
}