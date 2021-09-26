#include <bits/stdc++.h>
#define i64 long long
#define MOD 1000000007LL
#define pair pair<int, int>
#define F first
#define S second
using namespace std;

int H,W,N;
pair obs[3000];
i64 perm[200001], inv[200001];

i64 inverse(i64 a) {
	i64 ans = 1LL;
	i64 p = MOD-2;
	while(p) {
		if(p&1) {
			ans = (ans * a)%MOD;
		}
		a = (a*a)%MOD;
		p >>= 1;
	}
	return ans;
}

void preprocess() {
	perm[0] = inv[0] = 1LL;
	for(i64 i=1;i<=200000;i++) {
		perm[i] = (perm[i-1] * i) % MOD;
		inv[i] = inverse(perm[i]) % MOD;
	}
}

bool comp(pair &a, pair &b) {
	return a.F+a.S < b.F+b.S;
}

i64 ncrMod(int n, int r) {
	return (perm[n] * inv[r] % MOD * inv[n-r] % MOD) %MOD;
}

i64 getWays(pair a, pair b) {
	if(b.F >= a.F && b.S >= a.S) {
		return ncrMod(b.F-a.F+b.S-a.S, b.F-a.F);
	}
	return 0;
}

i64 solve() {
	i64 ans = getWays({0,0}, {H,W});
	i64 ways[N];
	for(int i=0;i<N;i++) {
		i64 x = getWays({0,0}, obs[i]);
		for(int j=0;j<i;j++) {
			x = (MOD + x - ((ways[j] * getWays(obs[j], obs[i]))%MOD) ) % MOD;
		}
		ways[i] = x;
		i64 y = getWays(obs[i], {H,W});
		ans = (MOD + ans - ((x*y)%MOD)) % MOD;
	}
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	preprocess();
	cin>>H>>W>>N;
	H--;W--;
	for(int i=0;i<N;i++) {
		cin>>obs[i].F>>obs[i].S;
		obs[i].F--;obs[i].S--;
	}
	sort(obs, obs+N, comp);
	cout<<solve();

	return 0;
}