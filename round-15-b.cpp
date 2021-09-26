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

bool compare(vector<int> &a, vector<int> &b) {
    int x=0, y=0;
    for(int i=0;i<5;i++) {
        if(a[i] < b[i]) x++;
        else y++;
    }
    return x > y;
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
        vector<int> ar[n];
        for(int i=0;i<n;i++) {
            ar[i].resize(5);
            for(int j=0;j<5;j++) {
                fastscan(ar[i][j]);
            }
        }
        int ans = min_element(ar, ar+n, compare) - ar;
        for(int i=0;i<n;i++) {
            if(ans != i && !compare(ar[ans], ar[i])) {
                ans = -2;
                break;
            }
        }
        printf("%d\n", ans+1);
    }

	return 0;
}