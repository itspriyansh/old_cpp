#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define MOD 1000000007
#define pair pair<i64, i64>
#define pb push_back
#define endl '\n'
#define matrix vector<vector<i64>>
#define INF i6432_MAX
using namespace std;
unordered_map<i64, i64> dp;
i64 prec[100][100];

void fastscan(i64 &number) {
    bool negative = false;
    register i64 c;
    number = 0;
    c = getchar();
    if (c=='-') {
        negative = true;
        c = getchar();
    }
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
    if (negative)
        number *= -1;
}

i64 findBranch(i64 ar[], i64 dist[], i64 n, i64 pos, i64 range, i64 limit) {
	i64 steps = 0;
	for(int i=pos-1;i>=pos-range;i--) {
		steps += dist[i+1];
	}
	if(steps >= limit) return INT64_MAX;
	i64 sum = 0, branch = ar[pos]/limit + (ar[pos]%limit ? 1 : 0);
	for(int i=pos-range;i<=pos;i++) {
		sum += ar[i];
		branch = max(branch, sum/(limit-steps)+(sum%(limit-steps) ? 1 : 0));
		if(steps) steps -= dist[i+1];
	}
	return branch;
}

bool isPossible(i64 n, i64 pos, i64 limit, i64 coins, i64 ar[], i64 dist[], i64 branches[], i64 slots[], i64 finishes[], i64 closest, i64 distClosest) {
	if(coins < 0) return false;
	if(pos < 0) return true;
	if(dp.count(pos) && dp[pos] >= coins) return false;
	i64 people = ar[pos];
	if(!people) {
		slots[pos] = 0;
		branches[pos] = 0;
		finishes[pos] = 0;
		return isPossible(n, pos-1, limit, coins, ar, dist, branches, slots, finishes, closest, distClosest + dist[pos]);
	}
	for(i64 i=0;i<=pos;i++) {
		// i64 branch = findBranch(ar, dist, n, pos, i, limit);
		i64 branch = prec[pos-i][pos];
		if(branch > coins) {
			break;
		}
		branches[pos] = branch;
		i64 key = branch*n+pos;
		if(dp.count(key) && dp[key]<=limit) {
			return true;
		}
		finishes[pos] = i;
		slots[pos] = branch * limit - people;
		if(isPossible(n, pos-i-1, limit, coins-branch, ar, dist, branches, slots, finishes, pos, dist[pos])) {
			dp[key] = limit;
			return true;
		}
	}
	dp[pos] = max(dp[pos], coins);
	return false;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

	i64 t;
	fastscan(t);
	while(t--) {
		// dp.clear();
		i64 n, x, zeroes=0;
		bool zExist = true;
		fastscan(n);
		fastscan(x);
		i64 ar[n], dist[n], arc[n], distr[n];
		for(i64 i=0;i<n;i++) {
			fastscan(ar[i]);
			if(zExist && !ar[i]) {
				i--;n--;
				zeroes++;
			} else {
				zExist = false;
				arc[i] = ar[i] + (i ? arc[i-1] : 0);
			}
		}
		if(!n) zeroes--;
		while(zeroes--) {
			fastscan(dist[0]);
		}
		for(i64 i=1;i<n;i++) {
			fastscan(dist[i]);
			distr[i] = dist[i] + (i-1 ? distr[i-1] : 0);
		}
		if(!n) {
			printf("0\n");
			continue;
		}
		distr[0] = 0;
		while(!ar[n-1]) {
			n--;
		}
		i64 low = 1, high = 1000000000000LL, total, steps;
		i64 ans, mid;
		bool valid;
		i64 people, slots[n], booking, branch, sum;
		i64 finishes[n], waste, branches[n];

		while(low <= high) {
			dp.clear();
			mid = low/2 + high/2 + ((low & 1) + (high & 1)) / 2;
			for(int i=0;i<n;i++) {
	        	for(int j=i;j<n;j++) {
	        		steps = distr[j] - distr[i];
	        		if(steps >= mid) {
	        			prec[i][j] = INT64_MAX;
	        			continue;
	        		}
	        		prec[i][j] = ar[j]/mid + (ar[j]%mid ? 1 : 0);
	        		for(int k=i;k<=j;k++) {
	        			steps = distr[j] - distr[k];
	        			people = arc[k] - (i ? arc[i-1] : 0);
	        			prec[i][j] = max(prec[i][j], people/(mid-steps)+(people%(mid-steps) ? 1 : 0));
	        		}
	        	}
	        }
			valid = isPossible(n, n-1, mid, x, ar, dist, branches, slots, finishes, -1, 0);
			// steps = 0;
			// total = 0;
			// for(int i=n-1;i>=0;i--) {
			// 	int range = i;
			// 	for(int j=i-1;j>=0 && steps + dist[j+1] < mid;j--) {
			// 		steps += dist[j+1];
			// 		range = j;
			// 	}
			// 	branch = ar[i]/mid + (ar[i]%mid ? 1 : 0);
			// 	sum = 0;
			// 	for(int j=range;j<=i;j++) {
			// 		sum += ar[j];
			// 		branch = max(branch, sum/(mid-steps) + (sum%(mid-steps) ? 1 : 0));
			// 		if(branch+total > x) {
			// 			range = j+1;
			// 			branch = ar[i]/mid + (ar[i]%mid ? 1 : 0);
			// 			sum = 0;
			// 		} else {
			// 			branches[j] = 0;
			// 		}
			// 		if(steps) steps -= dist[j+1];
			// 	}
			// 	// cout<<"From "<<i<<" to "<<range<<" -> "<<branch<<" with lim "<<mid<<endl;
			// 	branches[i] = branch;
			// 	total += branch;
			// 	i = min(range, i);
			// 	if(total > x) {
			// 		valid = false;
			// 		break;
			// 	}
			// }
			if(valid) {
				ans = mid;
				high = mid - 1;
				// cout<<"ANS: "<<ans<<endl;
				// for(i64 b: branches) {
				// 	cout<<b<<" ";
				// }cout<<endl;
			} else {
				low = mid + 1;
			}
		}
		printf("%lld\n", ans);
	}

	return 0;
}