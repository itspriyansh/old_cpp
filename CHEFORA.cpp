#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define MOD 1000000007
#define pair pair<int, int>
#define pb push_back
#define endl '\n'
#define LIM 100001
using namespace std;

i64 chefora(i64 n) {
	int k=n/10;
	while(k) {
		n = n*10+k%10;
		k /= 10;
	}
	return n;
}

int exponent(i64 a, int n) {
	i64 ans = 1;
	while(n) {
		if(n&1) {
			ans = (ans*a)%MOD;
		}
		a = (a*a)%MOD;
		n >>= 1;
	}
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

	i64 sum[LIM], num[LIM];
	sum[0] = num[0] = 0;
	for(int i=1;i<LIM;i++) {
		sum[i] = (sum[i-1] + (num[i] = chefora(i))) % (MOD-1);
	}

	int q;
	cin>>q;
	while(q--) {
		int l,r;
		cin>>l>>r;
		cout<<exponent(num[l], (sum[r]+MOD-1-sum[l]) % (MOD-1))<<endl;
	}
	return 0;
}