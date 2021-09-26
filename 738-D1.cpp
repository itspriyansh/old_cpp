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

int getParent(int par[], int i) {
    return par[i] == i ? i : par[i] = getParent(par, par[i]);
}

void unoin(int par[], int rnk[], int m, int n) {
    m = getParent(par, m);
    n = getParent(par, n);
    if(m == n) return;
    if(rnk[m] < rnk[n]) {
        swap(m, n);
    }
    par[n] = m;
    rnk[m] += rnk[n];
}

bool same(int par[], int a, int b) {
    return getParent(par, a) == getParent(par, b);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

    int n, m1, m2;
    fastscan(n);
    fastscan(m1);
    fastscan(m2);
    unordered_set<int> edges;
    int parents[2][n], ranks[2][n];
    for(int i=0;i<n;i++) {
        parents[0][i] = parents[1][i] = i;
        ranks[0][i] = ranks[1][i] = 1;
    }
    int a,b;
    for(int i=0;i<m1;i++) {
        fastscan(a);
        fastscan(b);
        a--;b--;
        edges.insert(a*n+b);
        unoin(parents[0], ranks[0], a, b);
    }
    for(int i=0;i<m2;i++) {
        fastscan(a);
        fastscan(b);
        a--;b--;
        if(a > b) swap(a, b);
        edges.insert(a*n+b);
        edges.insert(a*n+b);
        unoin(parents[1], ranks[1], a, b);
    }
    vector<pair> ans;
    ans.reserve(n-1);
    for(int i=0;i+1<n && m1<n-1 && m2<n-1;i++) {
        for(int j=i+1;j<n && m1<n-1 && m2<n-1;j++) {
            if(!edges.count(i*n+j) && !same(parents[0], i, j) && !same(parents[1], i, j)) {
                ans.pb({i+1, j+1});
                edges.insert(i*n+j);
                unoin(parents[0], ranks[0], i, j);
                unoin(parents[1], ranks[1], i, j);
            }
        }
    }
    printf("%d\n", (int)ans.size());
    for(pair &x: ans) {
        printf("%d %d\n", x.F, x.S);
    }
	return 0;
}