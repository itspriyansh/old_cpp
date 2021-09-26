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
    int n, a, b, c, prev;
    fastscan(n);
    i64 ans = 0;
    bool invert = false;

    for(int i=0;i<n;i++) {
        fastscan(a);
        if(!i) {
            b = 0;
            c = a;
            if(a<0) {
                invert = true;
                c = -c;
            }
        }
        if(invert) a = -a;
        if(i) {
            if(a > prev) {
                b += a-prev;
            } else {
                c -= prev-a;
            }
        }
        // cout<<b<<" -> "<<c<<endl;
        prev = a;
        ans = ans + abs(b) + abs(c);
    }
    printf("%lld", ans);

	return 0;
}