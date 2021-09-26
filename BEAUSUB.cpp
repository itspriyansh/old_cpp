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
    int dp[1000][1001], getmax[1001], last[1001], l;
    while(t--) {
        int n,k;
        fastscan(n);
        fastscan(k);
        int ar[n], ans = 0;
        l=0;
        for(int i=0;i<n;i++) {
            fastscan(ar[i]);
            l = max(l, ar[i]+1);
        }
        fill(last, last+l, -1);
        fill(getmax, getmax+k+1, 0);
        for(int i=0;i<n;i++) {
            for(int j=k;j>=0;j--) {
                dp[i][j] = 1;
                if(j) dp[i][j] = max(dp[i][j], getmax[j-1]+1);
                if(last[ar[i]] != -1) dp[i][j] = max(dp[i][j], dp[last[ar[i]]][j]+1);
                getmax[j] = max(getmax[j], dp[i][j]);
                if(j) getmax[j] = max(getmax[j], getmax[j-1]);
                ans = max(ans, dp[i][j]);
            }
            last[ar[i]] = i;
        }
        printf("%d\n", ans);
    }
	return 0;
}