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

void fastscan(i64 &number) {
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

void build(i64 tree[], i64 ar[], int l, int r, int i=0) {
    if(l == r) {
        tree[i] = ar[l];
        return;
    }
    int m = (l+r)/2;
    build(tree, ar, l, m, 2*i+1);
    build(tree, ar, m+1, r, 2*i+2);
    tree[i] = __gcd(tree[2*i+1], tree[2*i+2]);
}

i64 query(i64 tree[], i64 ar[], int l, int r, int a, int b, int i=0) {
    if(l>b || r<a) {
        return 0;
    }
    if(l>=a && r<=b) {
        return tree[i];
    }
    int m = (l+r)/2;
    i64 x = query(tree, ar, l, m, a, b, 2*i+1);
    i64 y = query(tree, ar, m+1, r, a, b, 2*i+2);
    return __gcd(x, y);
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
        int n;
        scanf("%d", &n);
        n--;
        i64 prev;
        scanf("%lld", &prev);
        if(!n) {
            printf("1\n");
            continue;
        }
        i64 ar[n];
        for(int i=0;i<n;i++) {
            scanf("%lld", &ar[i]);
            swap(ar[i], prev);
            ar[i] = llabs(ar[i]-prev);
        }
        int ans = 1;
        i64 tree[4*n];
        build(tree, ar, 0, n-1);
        i64 gcd = 0;
        for(int i=0,j=0;j<n;j++) {
            gcd = __gcd(gcd, ar[j]);
            while(gcd <= 1 && i<j) {
                i++;
                gcd = query(tree, ar, 0, n-1, i, j);
            }
            if(gcd > 1) {
                ans = max(ans, j-i+2);
            }
        }
        printf("%d\n", ans);
    }
	return 0;
}