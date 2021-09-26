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

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    fastio

    int t;
    fastscan(t);
    while(t--) {
        int n,m;
        fastscan(n);
        fastscan(m);
        i64 ans = 0;
        pair ar[m];
        i64 all = 1;
        for(int i=0;i<m;i++) {
            fastscan(ar[i].F);
            fastscan(ar[i].S);
        }
        sort(ar, ar+m, greater<pair>());
        i64 hcf;
        for(int i=0;i<m && n;i++) {
            hcf = __gcd(all, (i64)ar[i].S);
            ar[i].S /= hcf;
            ans += (i64)ar[i].F * (n-(n/ar[i].S));
            n /= ar[i].S;
            all *= ar[i].S;
        }
        printf("%lld\n", ans);
    }
    return 0;
}