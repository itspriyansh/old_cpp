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

    int n;
    fastscan(n);
    pair a[n];
    for(int i=0;i<n;i++) {
        fastscan(a[i].F);
        fastscan(a[i].S);
    }
    i64 ans = 0;
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            for(int k=j+1;k<n;k++) {
                int area = abs(a[i].F*(a[j].S-a[k].S) + a[j].F*(a[k].S-a[i].S) + a[k].F*(a[i].S-a[j].S))/2;
                int line = __gcd(abs(a[i].F-a[j].F), abs(a[i].S-a[j].S)) + __gcd(abs(a[j].F-a[k].F), abs(a[j].S-a[k].S)) + __gcd(abs(a[i].F-a[k].F), abs(a[i].S-a[k].S));
                int inner = (2*area - line + 2) / 2;
                if(inner&1) {
                    ans++;
                }
            }
        }
    }
    printf("%lld\n", ans);
	return 0;
}