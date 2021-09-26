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
        int n,k,s;
        fastscan(n);
        fastscan(k);
        fastscan(s);
        int l = log2(k) + 1;
        int ar[n];
        i64 sum[n+1];
        sum[0] = 0;
        for(int i=0;i<n;i++) {
            fastscan(ar[i]);
            sum[i+1] = sum[i] + ar[i];
        }
        int dp[l][n+1];
        for(int i=0;i<n;i++) {
            dp[0][i] = upper_bound(sum+i+2, sum+n+1, sum[i]+s) - sum - 1;
        }
        dp[0][n] = n;
        for(int i=1;i<l;i++) {
            for(int j=0;j<=n;j++) {
                dp[i][j] = dp[i-1][dp[i-1][j]];
            }
        }
        int ans = 0, par, x, y;
        for(int i=0;i<n;i++) {
            x = k;
            par = i;
            while(x) {
                y = log2(x & -x);
                par = dp[y][par];
                x -= x & -x;
            }
            ans = max(ans, par-i);
        }
        printf("%d\n", ans);
    }
	return 0;
}