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
		int parents[n], heights[n];
		heights[0] = 0;
		for(int i=1;i<n;i++) {
			fastscan(parents[i]);
			parents[i]--;
		}
		i64 ans = 0;
		printf("0 ");
		for(int i=1;i<n;i++) {
			heights[i] = 0;
			for(int j=i;j;j = parents[j]) {
				if(heights[parents[j]] < heights[j]+1) {
					ans += heights[parents[j]] ? 2 : 1;
					heights[parents[j]] = heights[j]+1;
				} else break;
			}
			printf("%lld ", ans);
		}
		printf("\n");
	}
	return 0;
}

// Input:
// 3
// 8
// 1 2 3 4 5 6 7
// 6
// 1 2 1 4 3
// 12
// 1 2 1 4 4 6 2 8 5 6 11
// Output:
// 0 1 4 9 16 25 36 49 
// 0 1 4 4 5 10 
// 0 1 4 4 5 5 10 10 13 14 14 21 
// 0 1 1 4 4 5 5 10 10 11 11 14 15 15 