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

struct Triplet {
    int a,b,c;
};

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

bool compare(Triplet &x, Triplet &y) {
    return x.a < y.a || (x.a == y.a && x.b < y.b);
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
        int n;
        fastscan(n);
        Triplet ar[n];
        for(int i=0;i<n;i++) {
            fastscan(ar[i].b);
            ar[i].c = i;
        }
        for(int i=0;i<n;i++) {
            fastscan(ar[i].a);
        }
        sort(ar, ar+n, compare);
        Triplet dp[n+1];
        dp[0].a = 0;
        dp[0].b = 0;
        dp[0].c = 0;
        for(int i=0;i<n;i++) {
            dp[i+1].a = 0;
            dp[i+1].b = 0;
            dp[i+1].c = i;
            for(int j=0;j<=i;j++) {
                if(dp[j].b+ar[i].b <= ar[i].a && (dp[i+1].a <  dp[j].a+1 || ( dp[i+1].a==dp[j].a+1 && dp[i+1].b > dp[j].b+ar[i].b ))) {
                    dp[i+1].a = dp[j].a+1;
                    dp[i+1].b = dp[j].b+ar[i].b;
                    dp[i+1].c = j;
                }
            }
        }
        vector<Triplet> ans;
        int it = max_element(dp, dp+n+1, compare)-dp;
        while(it != dp[it].c) {
            Triplet tp;
            tp.a = ar[it-1].c+1;
            tp.c = dp[it].b;
            tp.b = dp[it].b - ar[it-1].b;
            it = dp[it].c;
            ans.pb(tp);
        }
        printf("%d\n", (int)ans.size());
        for(int i=ans.size()-1;i>=0;i--) {
            printf("%d %d %d\n", ans[i].a, ans[i].b, ans[i].c);
        }
    }

	return 0;
}