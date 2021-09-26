#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define MOD 1000000007
#define pair pair<int, int>
#define pb push_back
#define endl '\n'
using namespace std;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

	int n, q;
	cin>>n>>q;
	int ar[n];
	for(int i=0;i<n;i++) {
		cin>>ar[i];
	}
	sort(ar, ar+n);
	int a, pos;
	while(q--) {
		cin>>a;
		pos = lower_bound(ar, ar+n, a) - ar;
		if(ar[pos] == a) {
			cout<<"0\n";
			continue;
		}
		cout<<((n-pos)&1 ? "NEGATIVE\n" : "POSITIVE\n");
	}
	return 0;
}