#include <bits/stdc++.h>
#define i64 long long
using namespace std;

i64 *bit;

void update(int i, int val, int n) {
	while(i<=n) {
		bit[i] += val;
		i += i & -i;
	}
}

i64 query(int i) {
	i64 ans = 0;
	while(i > 0) {
		ans += bit[i];
		i -= i & -i;
	}
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	// online submission
	#endif
	int t;
	cin>>t;
	while(t--) {
		int n,u,q;
		cin>>n>>u;
		bit = new i64[n+1];
		for(int i=1;i<=n;i++) {
			bit[i] = 0;
		}
		int l, r, val;
		while(u--) {
			cin>>l>>r>>val;
			update(l+1, val, n);
			update(r+2, -val, n);
		}
		cin>>q;
		while(q--) {
			cin>>l;
			cout<<query(l+1)<<endl;
		}
	}
	return 0;
}