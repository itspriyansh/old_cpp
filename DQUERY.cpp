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
	int first, second, pos;
};

bool compare(node &a, node &b) {
	if(a.F/step == b.F/step) {
		return a.S <= b.S;
	}
	return a.F/step <= b.F/step;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

	int n,q;
	cin>>n>>q;
	int cnt[1000001] = {0}, count = 0;
	int ar[n];
	for(int i=0;i<n;i++) {
		cin>>ar[i];
	}
	cin>>q;
	step = sqrt(q);
	node qr[q];
	for(int i=0;i<q;i++) {
		cin>>qr[i].F>>qr[i].S;
		qr[i].F--;
		qr[i].S--;
		qr[i].pos  =i;
	}
	int ans[q];
	sort(qr, qr+q, compare);
	for(int i=qr[0].F;i<=qr[0].S;i++) {
		if(!cnt[ar[i]]) {
			count++;
		}
		cnt[ar[i]]++;
	}
	ans[qr[0].pos] = count;

	for(int i=1;i<q;i++) {
		while(qr[i].S > qr[i-1].S) {
			cnt[ar[++qr[i-1].S]]++;
			if(cnt[ar[qr[i-1].S]] == 1) {
				count++;
			}
		}
		while(qr[i].F < qr[i-1].F) {
			cnt[ar[--qr[i-1].F]]++;
			if(cnt[ar[qr[i-1].F]] == 1) {
				count++;
			}
		}
		while(qr[i].S < qr[i-1].S) {
			cnt[ar[qr[i-1].S]]--;
			if(!cnt[ar[qr[i-1].S]]) count--;
			qr[i-1].S--;
		}
		while(qr[i].F > qr[i-1].F) {
			cnt[ar[qr[i-1].F]]--;
			if(!cnt[ar[qr[i-1].F]]) count--;
			qr[i-1].F++;
		}
		ans[qr[i].pos] = count;
	}
	for(int a: ans) {
		cout<<a<<'\n';
	}
	return 0;
}