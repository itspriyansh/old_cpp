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
    scanf("%d", &t);
    while(t--) {
        int n,m;
        scanf("%d %d", &n, &m);
        if(m < n) {
            printf("0\n");
            continue;
        }
        int d = m-n+1, prev = -1;
        for(int i=0;d&n;i++) {
            if(!(d&(1<<i))) {
                prev = -1;
                continue;
            }
            if(prev == -1) prev = i;
            if((d&(1<<i)) && (n&(1<<i))) {
                d += 1<<prev;
                prev = -1;
            }
        }
        for(int i=0;d>>i;i++) {
            if(!(d&(1<<i))) continue;
            if(d-(1<<i) > m-n) d ^= 1<<i;
        }
        printf("%d\n", d);
    }

	return 0;
}