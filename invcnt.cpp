#include <bits/stdc++.h>
#define i64 long long
using namespace std;

int *ar, *bit;

void update(int i, int val, int n) {
	while(i<n) {
		bit[i] += val;
		i += i & -i;
	}
}

i64 query(int i) {
	i64 ans = 0;
	while(i>0) {
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
	string dummy;
	while(t--) {
		getline(cin, dummy);
		int n;
		cin>>n;
		ar = new int[n];
		unordered_map<int, int> mp;
		set<int> st;
		for(int i=0;i<n;i++) {
			cin>>ar[i];
			st.insert(ar[i]);
		}
		int val = 1;
		for(int s: st) {
			mp[s] = val++;
		}
		bit = new int[val];
		for(int i=1;i<val;i++) {
			bit[i] = 0;
		}
		i64 ans = 0;
		for(int i=n-1;i>=0;i--) {
			ar[i] = mp[ar[i]];
			ans += query(ar[i]-1);
			update(ar[i], 1, val);
		}
		cout<<ans<<endl;
	}
	return 0;
}