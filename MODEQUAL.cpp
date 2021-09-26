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
        int n, least = 2000000000;
        fastscan(n);
        int ar[n];
        for(int i=0;i<n;i++) {
            fastscan(ar[i]);
            least = min(least, ar[i]);
        }
        int ans = n, cnt = 0, valid = true;
        for(int i=0;i<n;i++) {
            if(ar[i] != least && ar[i]/2 + ar[i]%2 <= least) {
                valid = false;
                break;
            }
            if(ar[i] != least) cnt++;
        }
        if(valid) {
            ans = cnt;
        }
        printf("%d\n", ans);
    }
	return 0;
}