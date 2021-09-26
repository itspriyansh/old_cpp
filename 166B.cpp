#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define pair pair<i64, i64>
#define MOD 1000000007
#define pb push_back
using namespace std;

int direction(pair &a, pair &b, pair &c) {
	i64 val = a.F*c.S-c.F*a.S+b.F*(a.S-c.S)+b.S*(c.F-a.F);
	return val < 0 ? -1 : val > 0 ? 1 : 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n,m;
	set<pair> inner;
	vector<pair> pts;
	cin>>n;
	for(int i=0;i<n;i++) {
		pts.pb({0,0});
		cin>>pts.back().F>>pts.back().S;
	}
	cin>>m;
	for(int i=0;i<m;i++) {
		pts.pb({0,0});
		cin>>pts.back().F>>pts.back().S;
		inner.insert(pts.back());
	}
	sort(pts.begin(), pts.end());
	pair &st=pts[0], &en=pts.back();
	vector<int> up, down;
	up.pb(0);
	down.pb(0);
	for(int i=1;i<pts.size();i++) {
		if(direction(st, pts[i], en) >= 0) {
			while(up.size()>1 && direction(pts[up[up.size()-2]], pts[up.back()], pts[i]) == -1) {
				up.pop_back();
			}
			up.pb(i);
		} 
		if(direction(st, pts[i], en) <= 0) {
			while(down.size()>1 && direction(pts[down[down.size()-2]], pts[down.back()], pts[i]) == 1) {
				down.pop_back();
			}
			down.pb(i);
		}
	}
	for(int u: up) {
		// cout<<pts[u].F<<", "<<pts[u].S<<endl;
		if(inner.count(pts[u])) {
			cout<<"NO";
			return 0;
		}
	}
	for(int u: down) {
		// cout<<pts[u].F<<", "<<pts[u].S<<endl;
		if(inner.count(pts[u])) {
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}