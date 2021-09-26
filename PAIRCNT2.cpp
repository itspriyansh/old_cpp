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
int timein[100000], height[100000], counts=0, cr[100000], ch[100000], ct[100000], sparse[19][200000], path[200000];

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
				sparse[i][j] = path[j];
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
		int K;
		i64 l, r;
		int k,d,ans=0;
		while(q--) {
			// cin>>k>>d;
			fastscan(k);
			fastscan(d);
			ans = 0;
			for(int i=0;i<k;i++) {
				// cin>>cr[i];
				fastscan(cr[i]);
				cr[i]--;
				ch[i] = height[cr[i]];
				ct[i] = timein[cr[i]];
			}
			for(int i=0;i<k;i++) {
				for(int j=0;j<i;j++) {
					l = ct[i];r = ct[j];
					if(l>r) swap(l,r);
                	K = 32 - __builtin_clz(r+1-l) - 1;
					if(ch[i]+ch[j]-2*min(sparse[K][l], sparse[K][r-(1<<K)+1]) == d) {
						ans++;
					}
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}