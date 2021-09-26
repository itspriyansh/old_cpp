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

struct node {
	int count,val;
	int ch[2];

	node() {
		count = ch[0] = ch[1] = 0;
		val = 0;
	}
};

node data[10000000];
int len = 1, len2 = 0;
int tries[500001];

void add(int n) {
	int l = tries[len2-1], r=len++;
	tries[len2++] = r;
	data[r] = data[l];
	data[r].count++;
	for(int i=20;i>=0;i--) {
		int k = (n>>i)&1;
		data[r].ch[k] = len++;
		l = data[l].ch[k];
		r = data[r].ch[k];
		data[r] = data[l];
		data[r].count++;
	}
	data[r].val = n;
}

int find(int l, int r, int n) {
	for(int i=20;i>=0;i--) {
		int k = (n>>i)&1;
		if(data[data[r].ch[1-k]].count-data[data[l].ch[1-k]].count > 0) {
			l = data[l].ch[1-k];
			r = data[r].ch[1-k];
		} else {
			l = data[l].ch[k];
			r = data[r].ch[k];
		}
	}
	return data[r].val;
}

int countt(int l, int r, int n) {
	int ans = 0;
	for(int i=20;i>=0;i--) {
		int k = (n>>i)&1;
		if(k) {
			ans += data[data[r].ch[0]].count-data[data[l].ch[0]].count;
			l = data[l].ch[1];
			r = data[r].ch[1];
		} else {
			l = data[l].ch[0];
			r = data[r].ch[0];
		}
	}
	ans += data[r].count - data[l].count;
	return ans;
}

int findThat(int l, int r, int k) {
	for(int i=20;i>=0;i--) {
		if(data[data[r].ch[0]].count-data[data[l].ch[0]].count >= k) {
			l = data[l].ch[0];
			r = data[r].ch[0];
		} else {
			k -= data[data[r].ch[0]].count-data[data[l].ch[0]].count;
			l = data[l].ch[1];
			r = data[r].ch[1];
		}
	}
	return data[r].val;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio
	int m,c,l,r,x;
	cin>>m;
	tries[len2++] = 0;
	while(m--) {
		cin>>c;
		switch(c) {
			case 0: {
				cin>>x;
				add(x);
				break;
			}
			case 1: {
				cin>>l>>r>>x;
				cout<<find(tries[l-1], tries[r], x)<<'\n';
				break;
			}
			case 2: {
				cin>>x;
				// len = tries[len2-x-1];
				len2 = len2-x;
				break;
			}
			case 3: {
				cin>>l>>r>>x;
				cout<<countt(tries[l-1], tries[r], x)<<'\n';
				break;
			}
			case 4: {
				cin>>l>>r>>x;
				cout<<findThat(tries[l-1], tries[r], x)<<'\n';
				break;
			}
		}
	}

	return 0;
}