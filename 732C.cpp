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
        int n;
        fastscan(n);
        pair ar[n];
        for(int i=0;i<n;i++) {
            fastscan(ar[i].F);
            ar[i].S = i;
        }
        sort(ar, ar+n);
        bool valid = true;
        unordered_map<int, int> dp[2];
        for(int i=0;i<n;i++) {
            if((ar[i].S-i)&1) {
                int parity = 1 - (i&1);
                if(dp[parity].count(ar[i].F)) {
                    dp[parity][ar[i].F]--;
                    if(!dp[parity][ar[i].F]) {
                        dp[parity].erase(ar[i].F);
                    }
                } else {
                    dp[1-parity][ar[i].F]++;
                }
            }
        }
        valid = dp[0].empty() && dp[1].empty();
        printf(valid ? "YES\n" : "NO\n");
    }

	return 0;
}