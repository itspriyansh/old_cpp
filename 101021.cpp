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
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	#endif

	int low = 1, high = 1000000;
	string res;
	int ans = high;
	while(low <= high) {
		int mid = (low+high)/2;
		cout<<mid<<endl<<flush;
		cin>>res;
		if(res[0] == '<') {
			low = mid+1;
		} else {
			ans = mid;
			high = mid-1;
		}
	}
	cout<<"! "<<ans<<endl<<flush;

	return 0;
}