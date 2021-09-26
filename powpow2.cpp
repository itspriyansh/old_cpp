#include <bits/stdc++.h>
#define i64 long long
using namespace std;
const int as = 1681, bs = 148721;
i64 A[200001],B[bs],A41[200001];

i64 modInverse(i64 a, int n) {
	for(i64 i=1;;i++) {
		if((a*i)%n == 1) {
			return i;
		}
	}
}

i64 modExponent(i64 a, i64 n, i64 p) {
	i64 ans = 1;
	i64 k = a;
	while(n) {
		if(n&1) {
			ans = (ans * k) % p;
		}
		k = (k*k)%p;
		n >>= 1;
	}
	return ans;
}

i64 modInverse2(i64 a, int n) {
	return modExponent(a, n-2, n);
}

i64 modCombination(i64 n, int m) {
	if(m == 2) {
		return !n;
	}
	else if(m == 1681) {
		i64 inv = modInverse(A[n], m);
		inv = (inv* inv) %m;
		return (((A[2*n] * modExponent(41, A41[2*n]-2*A41[n], 1681)) % as ) * inv) % as;
	} else {
		if(2*n >= m) return 0;
		i64 inv = modInverse2(B[n], m);
		inv = (inv*inv)%m;
		return (B[2*n] * inv) % bs;
	}
}

i64 crt(i64 rem[]) {
	i64 product = 500000002LL;
	i64 inv[] = {1, 637, 18004};
	i64 ans = 0;
	i64 num[] = {2, 1681, 148721};
	for(int i=0;i<3;i++) {
		i64 rr = product/num[i];
		ans = (ans + (((rem[i] * rr) % product) * inv[i] % product) ) % product;
	}
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	// online submission
	#endif
	A[0] = B[0] = 1;
	A41[0] = 0;
	for(int i=1;i<200001;i++) {
		A41[i] = A41[i-1];
		int k = i;
		while(k%41 == 0) {
			A41[i]++;
			k /= 41;
		}
		A[i] = (A[i-1] * k) % as;
		if(i < bs) {
			B[i] = (B[i-1] * i) % bs;
		}
	}
	i64 p = 1000000007LL, m = 500000003LL;
	int t;
	cin>>t;
	while(t--) {
		i64 a,b,n;
		cin>>a>>b>>n;
		if(!b) {
			cout<<1<<'\n';
			continue;
		}
		i64 rem[] = {modCombination(n, 2), modCombination(n, 1681), modCombination(n, 148721)};
		i64 ex = crt(rem);
		i64 w = modExponent(b, ex, b%2 ? p-1 : m), y=0;
		if(b%2) {
			y = w;
		} else {
			y = (w* (m+1)) % (p-1);
		}
		i64 x = modExponent(a, y, p);
		cout<<x<<'\n';
	}
	return 0;
}