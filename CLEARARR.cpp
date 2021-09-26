#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define MOD 1000000007
#define pair pair<int, int>
#define pb push_back
#define endl '\n'
#define matrix vector<vector<int>>
#define INF INT32_MAX
using namespace std;

int ar[5000];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

    int t;
    cin>>t;
    while(t--) {
        int n,k,x;
        cin>>n>>k>>x;
        i64 ans = 0;
        for(int i=0;i<n;i++) {
            cin>>ar[i];
            ans += ar[i];
        }
        sort(ar, ar+n);
        for(int i=0, j=n-1;i<k;i++,j-=2) {
            if(ar[j]+ar[j-1] > x) {
                ans += x - (ar[j]+ar[j-1]);
            } else break;
        }
        cout<<ans<<endl;
    }
	return 0;
}