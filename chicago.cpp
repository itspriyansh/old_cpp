#include<bits/stdc++.h>
#define pb push_back
#define pair pair<double, int>
#define F first
#define S second
using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	int n,m;
	cout<<fixed<<setprecision(6);
	while(1) {
		cin>>n;
		if(!n) break;
		cin>>m;
		vector<pair> adj[n];
		int x,y;
		double z;
		while(m--) {
			cin>>x>>y>>z;
			adj[x-1].pb({z/100.0, y-1});
			adj[y-1].pb({z/100.0, x-1});
		}
		double prob[n];
		fill(prob, prob+n, 0.0);
		prob[0] = 1.0;
		set<pair> q;
		q.insert({1.0, 0});
		unordered_set<int> vis;
		while(!q.empty()) {
			int u = q.rbegin()->S;
			q.erase({prob[u], u});
			vis.insert(u);
			for(auto &v: adj[u]) {
				if(!vis.count(v.S) && prob[v.S] < prob[u]*v.F) {
					q.erase({prob[v.S], v.S});
					prob[v.S] = prob[u]*v.F;
					q.insert({prob[v.S], v.S});
				}
			}
		}
		cout<<prob[n-1]*100.0<<endl;
	}
	return 0;
}