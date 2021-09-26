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
int step;

struct node {
	int F, S, pos;
};

bool compare(node &a, node &b) {
	if(a.F/step == b.F/step) {
		return a.S <= b.S;
	}
	return a.F < b.F;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

	int n,q;
	cin>>n>>q;
	step = sqrt(q);
	int cnt[1000001] = {0}, ar[n];
	i64 sum=0, ans[q];
	node qs[q];
	for(int i=0;i<n;i++) {
		cin>>ar[i];
	}
	for(int i=0;i<q;i++) {
		cin>>qs[i].F>>qs[i].S;
		qs[i].F--;
		qs[i].S--;
		qs[i].pos = i;
	}
	sort(qs, qs+q, compare);
	for(int i=qs[0].F;i<=qs[0].S;i++) {
		sum += (2LL*cnt[ar[i]] + 1) * ar[i];
		cnt[ar[i]]++;
	}
	ans[qs[0].pos] = sum;

	for(int i=1;i<q;i++) {
		while(qs[i].S > qs[i-1].S) {
			++qs[i-1].S;
			sum += (2LL*cnt[ar[qs[i-1].S]]+1) * ar[qs[i-1].S];
			cnt[ar[qs[i-1].S]]++;
		}
		while(qs[i].F < qs[i-1].F) {
			--qs[i-1].F;
			sum += (2LL*cnt[ar[qs[i-1].F]]+1) * ar[qs[i-1].F];
			cnt[ar[qs[i-1].F]]++;
		}
		while(qs[i].S < qs[i-1].S) {
			cnt[ar[qs[i-1].S]]--;
			sum -= (2LL*cnt[ar[qs[i-1].S]]+1) * ar[qs[i-1].S];
			qs[i-1].S--;
		}
		while(qs[i].F > qs[i-1].F) {
			cnt[ar[qs[i-1].F]]--;
			sum -= (2LL*cnt[ar[qs[i-1].F]]+1) * ar[qs[i-1].F];
			qs[i-1].F++;
		}
		ans[qs[i].pos] = sum;
	}
	for(i64 a: ans) {
		cout<<a<<endl;
	}

	return 0;
}