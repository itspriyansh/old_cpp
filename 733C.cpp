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
        int n,a, total1=0, total2=0;
        fastscan(n);
        int me[n+1], iyla[n+1];
        me[0] = iyla[0] = 0;
        for(int i=1;i<=n;i++) {
            fastscan(me[i]);
        }
        for(int i=1;i<=n;i++) {
            fastscan(iyla[i]);
        }
        sort(me+1, me+n+1);
        sort(iyla+1, iyla+n+1);
        for(int i=1;i<=n;i++) {
            me[i] += me[i-1];
            iyla[i] += iyla[i-1];
        }
        int low=0, high=n, ans=0;
        while(low <= high) {
            int mid = (low+high)/2;
            if(me[n]-me[min(n, (n+mid)/4)] + mid*100 >= iyla[n] - iyla[max(0, (n+mid)/4-mid)]) {
                ans = mid;
                high = mid-1;
            } else {
                low = mid+1;
            }
        }
        printf("%d\n", ans);
    }

	return 0;
}