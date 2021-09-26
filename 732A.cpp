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
        int a[n], b[n], sum=0, half=0;
        for(int i=0;i<n;i++) {
            fastscan(a[i]);
            sum += a[i];
        }
        queue<int> less, more;
        for(int i=0;i<n;i++) {
            fastscan(b[i]);
            sum -= b[i];
            if(a[i] < b[i]) {
                less.push(i);
            } else if(a[i] > b[i]) {
                more.push(i);
                half += a[i]-b[i];
            }
        }
        if(sum) {
            printf("-1\n");
            continue;
        }
        printf("%d\n", half);
        while(!more.empty()) {
            int i = more.front(), j = less.front();
            a[i]--;
            a[j]++;
            printf("%d %d\n", i+1, j+1);
            if(a[i] == b[i]) more.pop();
            if(a[j] == b[j]) less.pop();
        }
    }

	return 0;
}