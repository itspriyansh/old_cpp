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

	int t;
	cin>>t;
	while(t--) {
		int n;
		cin>>n;
		int ar[n];
		for(int i=0;i<n;i++) {
			cin>>ar[i];
		}
		if(n==1) {
			cout<<0<<endl;
		} else if(n==2) {
			cout<<(ar[0] != ar[1] ? 0 : -1)<<endl;
		} else if(n==3) {
			if(ar[0] == ar[2]) {
				cout<<1<<endl;
			} else if(ar[0] == (ar[0]^ar[1])) {
				cout<<2<<endl<<1<<' '<<2<<' '<<3<<endl;
			} else if(ar[2] == (ar[1]^ar[2])) {
				cout<<2<<endl<<2<<' '<<3<<' '<<1<<endl;
			} else {
				cout<<-1<<endl;
				continue;
			}
			cout<<1<<' '<<3<<' '<<2<<endl;
		} else {
			int base=-1;
			vector<int> eq, un;
			for(int i=0;i<n;i+=2) {
				if(!ar[i]) continue;
				if(base ==-1) {
					base = ar[i];
					eq.pb(i);
					un.pb(i);
				} else {
					if(base == ar[i]) {
						eq.pb(i);
					} else {
						un.pb(i);
					}
					break;
				}
			}
			if(base == -1) {
				int frnd = -1;
				for(int i=1;i<n;i+=2) {
					if(ar[i]) {
						frnd = ar[i];
						cout<<(n/2)-1<<endl;
						for(int j=1;j<n;j+=2) {
							if(i==j) continue;
							cout<<1<<' '<<i+1<<' '<<j+1<<endl;
						}
						break;
					}
				}
				if(frnd==-1) {
					cout<<-1<<endl;
				}
			} else if(eq.size()>1) {
				cout<<n-1<<endl;
				for(int j=1;j<n;j+=2) {
					cout<<eq[0]+1<<' '<<eq[1]+1<<' '<<j+1<<endl;
				}
				for(int j=0;j<n;j+=2) {
					if(j==eq[0]) continue;
					cout<<eq[0]+1<<' '<<2<<' '<<j+1<<endl;
				}
			} else if(un.size()==1) {
				for(int i=0;i<n;i+=2) {
					if(un[0] != i) {
						un.pb(i);
						break;
					}
				}
			} else if(un.size() < 2) {
				cout<<-1<<endl;
			}
			if(un.size()>1) {
				cout<<n<<endl;
				for(int i=1;i<n;i+=2) {
					cout<<un[0]+1<<' '<<un[1]+1<<' '<<i+1<<endl;
				}
				for(int i=0;i<n;i+=2) {
					cout<<2<<' '<<4<<' '<<i+1<<endl;
				}
			}
		}
	}
	return 0;
}