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

vector<int> *adj;
int path[2000000], sparse[30][2000000], total = 0, timein[800000];

int getLog(int x) {
    return 32 - __builtin_clz(x) - 1;
}

void dfs(int u, int h=0) {
	timein[u] = total;
	path[total++] = h;
	for(int v: adj[u]) {
		dfs(v, h+1);
		path[total++] = h;
	}
}

void buildSparse() {
	int n = total, lv = getLog(n)+1;
	for(int i=0;i<lv;i++) {
		for(int j=0, k=(1<<i)-1;j<n-k;j++) {
			if(!i) {
				sparse[i][j] = path[j];
				continue;
			}
			sparse[i][j] = min(sparse[i-1][j], sparse[i-1][j+(1<<(i-1))]);
		}
	}
}

int query(int l, int r) {
	int K = 32 - __builtin_clz(r+1-l) - 1;
	return min(sparse[K][l], sparse[K][r-(1<<K)+1]);
}

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
		total = 0;
		adj = new vector<int>[n];
		int parents[n], heights[n], counts[n];
		set<int> qq[n];
		for(int i=0;i<n;i++) {
			heights[i] = counts[i] = 0;
		}
		for(int i=1;i<n;i++){
			fastscan(parents[i]);
			parents[i]--;
			adj[parents[i]].pb(i);
		}
		dfs(0);
		buildSparse();
		i64 ans = 0;
		printf("0 ");
		for(int i=1;i<n;i++){
			heights[i] = heights[parents[i]]+1;
			if(!counts[parents[i]]) {
				if(qq[heights[i]].empty()) {
					ans = ans + 2*heights[i]-1;
				} else {
					auto it = qq[heights[i]].lower_bound(timein[i]);
					int dist;
					if(it == qq[heights[i]].begin()) dist = query(timein[i], *it);
					else if(it == qq[heights[i]].end()) dist = query(*prev(it), timein[i]);
					else dist = max(query(*prev(it), timein[i]), query(timein[i], *it));
					dist = heights[i] - dist;
					ans += 2*dist - 3;
				}
				qq[heights[i]].insert(timein[i]);
				counts[parents[i]]++;
			}
			printf("%lld ", ans);
		}
		printf("\n");
	}

	return 0;
}