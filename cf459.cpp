#include <bits/stdc++.h>
#define i64 long long
using namespace std;

i64 query(int bit[], int i) {
	i64 ans = 0;
	while(i>0) {
		ans += bit[i];
		i -= i & -i;
	}
	return ans;
}

void updat(int bit[], int i, int val, int n) {
	while(i<=n) {
		bit[i] += val;
		i += i & -i;
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	// online submission
	#endif
	int n;
	cin>>n;
	int ar[n];
	for(int i=0;i<n;i++) {
		cin>>ar[i];
	}
	unordered_map<int, int> cnt;
	int rgt[n];
	for(int i=n-1;i>=0;i--) {
		cnt[ar[i]]++;
		rgt[i] = cnt[ar[i]];
	}
	i64 ans = 0;
	int bit[n+1];
	for(int i=1;i<=n;i++) {
		bit[i] = 0;
	}
	for(int i=n-1;i>=0;i--) {
		int lft = cnt[ar[i]] - rgt[i] + 1;
		ans += query(bit, lft-1);
		updat(bit, rgt[i], 1, n);
	}
	cout<<ans<<endl;
	return 0;
}