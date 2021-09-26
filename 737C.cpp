#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define MOD 1000000007
#define pair pair<int, int>
#define pb push_back
#define endl '\n'
#define matrix vector<vector<int>>
#define INF INT32_MAX
#define LIM 200001
using namespace std;

void fastscan(int &number) {
    bool negative = false;
    register int c;
    number = 0;
    c = getchar();
    if (c=='-') {
        negative = true;
        c = getchar();
    }
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
    if (negative)
        number *= -1;
}

int modExpo(int a, int b) {
    i64 x = a, y = 1;
    while(b) {
        if(b&1) {
            y *= x;
            y %= MOD;
        }
        x *= x;
        x %= MOD;
        b >>= 1;
    }
    return y;
}

int fact(int a) {
    i64 ans = 1;
    for(int i=2;i<=a;i++) {
        ans *= i;
        ans %= MOD;
    }
    return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

    int t;
    fastscan(t);
    i64 inv[LIM];
    inv[0] = 1;
    for(int i=1;i<LIM;i++) {
        inv[i] = (inv[i-1] * modExpo(i, MOD-2))%MOD;
    }
    while(t--) {
        int n, k;
        fastscan(n);
        fastscan(k);
        i64 f = fact(n), k2 = modExpo(2, n);
        i64 single = 0;

        for(int i=0;i<n;i+=2) {
            single += (((f*inv[i])%MOD)*inv[n-i])%MOD;
            single %= MOD;
        }
        if(n&1) {
            single = (single+1) % MOD;
        }

        i64 soFar = 1;
        i64 dp[k+1];
        dp[0] = 1;

        for(int i=1;i<=k;i++) {
            dp[i] = 0;
            if(n%2 == 0) {
                dp[i] += soFar;
                dp[i] %= MOD;
            }
            dp[i] += (single * dp[i-1]) % MOD;
            dp[i] %= MOD;
            soFar = (soFar * k2) % MOD;
        }
        printf("%lld\n", dp[k]);
    }

	return 0;
}