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
int timein[100000], height[100000], counts=0, cr[100000], path[200000], ans, D;
pair sparse[19][200000];

int getLog(int x) {
    return 32 - __builtin_clz(x) - 1;
}

void dfs(int u, int p, vector<int> adj[], int h=1) {
	timein[u] = counts;
	path[counts++] = h;
	height[u] = h;
	for(int i=0;i<adj[u].size();i++) {
		if(p==adj[u][i]) continue;
		dfs(adj[u][i], u, adj, h+1);
		if(i+1 == adj[u].size() || (i+2 == adj[u].size() && adj[u].back() == p)) break;
		path[counts++] = h;
	}
}

void buildSparse() {
	int n = counts, lv = getLog(n)+1;
	for(int i=0;i<lv;i++) {
		for(int j=0, k=(1<<i)-1;j<n-k;j++) {
			if(!i) {
				sparse[i][j] = {path[j], j};
				continue;
			}
			sparse[i][j] = min(sparse[i-1][j], sparse[i-1][j+(1<<(i-1))]);
		}
	}
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

pair query(int l, int r) {
	int K = 32 - __builtin_clz(r+1-l) - 1;
	return min(sparse[K][l], sparse[K][r-(1<<K)+1]);
}

bool compare(int a, int b) {
	return timein[a] <= timein[b];
}

void divideAndConqure(int l, int r) {
	if(l >= r) {
		return;
	}
	static unordered_map<int, int> right;
	right.clear();
	pair pivot = query(timein[cr[l]], timein[cr[r]]);
	int pos = pivot.S;
	int pivot2 = r;
	while(timein[cr[pivot2]] > pos) {
		right[height[cr[pivot2]]]++;
		pivot2--;
	}
	int leftLim = pivot2, d = D+2*pivot.F;
	if(timein[cr[leftLim]] == pos) {
		ans += right[d-pivot.F];
		right[pivot.F]++;
		leftLim--;
	}
	for(int i=l;i<=leftLim;i++) {
		ans += right[d-height[cr[i]]];
	}
	divideAndConqure(l, leftLim);
	divideAndConqure(pivot2+1, r);
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
		counts = 0;
		int n,a,b,q;
		// cin>>n>>q;
		fastscan(n);
		fastscan(q);
		vector<int> adj[n];
		for(int i=1;i<n;i++) {
			// cin>>a>>b;
			fastscan(a);
			fastscan(b);
			adj[a-1].pb(b-1);
			adj[b-1].pb(a-1);
		}
		dfs(0, -1, adj);
		int lv = getLog(counts)+1;
		buildSparse();
		int k;
		while(q--) {
			// cin>>k>>d;
			fastscan(k);
			fastscan(D);
			ans = 0;
			for(int i=0;i<k;i++) {
				// cin>>cr[i];
				fastscan(cr[i]);
				cr[i]--;
			}
			sort(cr, cr+k, compare);
			divideAndConqure(0, k-1);
			printf("%d\n", ans);
		}
	}
	return 0;
}