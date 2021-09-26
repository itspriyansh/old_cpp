#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define MOD 998244353LL
#define pair pair<int, int>
#define pb push_back
#define endl '\n'
#define matrix vector<vector<int>>
#define INF INT32_MAX
#define LIM 100001
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

i64 inverse(i64 n) {
    i64 p = MOD-2, ans = 1;
    while(p) {
        if(p&1) {
            ans = (ans*n)%MOD;
        }
        n = (n*n)%MOD;
        p >>= 1;
    }
    return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

    i64 product[LIM], inv[LIM];
    product[0] = 1;
    inv[0] = inverse(1);
    for(i64 i=1;i<LIM;i++) {
        product[i] = (product[i-1]*i) % MOD;
        inv[i] = (inv[i-1]*inverse(i)) % MOD;
    }

    int t;
    scanf("%d", &t);
    char str[LIM];
    while(t--) {
        int n;
        scanf("%d", &n);
        scanf("%s", str);
        int zeroes = 0, groups = 0;
        for(int i=0;i<n;i++) {
            if(str[i] == '0') {
                zeroes++;
            } else if(i+1 < n && str[i+1] == '1') {
                groups++;
                i++;
            }
        }
        printf("%lld\n", ((product[zeroes+groups] * inv[zeroes]) % MOD * inv[groups]) % MOD);
    }

	return 0;
}