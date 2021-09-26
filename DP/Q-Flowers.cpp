#include <bits/stdc++.h>
#define i64 long long
using namespace std;

struct flower {
	int h;
	int b;
};

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int n;
	cin>>n;
	flower ar[n];

	for(int i=0;i<n;i++) {
		cin>>ar[i].h;
	}
	i64 ans = 0;
	map<int, i64> track;

	for(int i=0;i<n;i++) {
		cin>>ar[i].b;
		i64 sum = ar[i].b;
		auto it = track.upper_bound(ar[i].h);
		if(it != track.begin()) {
			it--;
			sum += it->second;
			it++;
		}
		while(it != track.end() && it->second <= sum) {
			auto temp = it;
			it++;
			track.erase(temp);
		}
		track[ar[i].h] = sum;
		ans = max(ans, sum);
	}
	cout<<ans;

	return 0;
}