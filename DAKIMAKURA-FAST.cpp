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

bool isPossible(i64 n, i64 pos, i64 limit, i64 coins, i64 ar[], i64 dist[], i64 branches[], i64 slots[], i64 finishes[], i64 closest, i64 distClosest) {
    if(coins < 0) return false;
    if(pos < 0) return true;
    i64 people = ar[pos];
    if(closest != -1 && slots[closest] && distClosest < limit) {
        i64 waste = distClosest - finishes[closest];
        if(waste < 0) {
            waste = 0;
        } else {
            waste = waste * branches[closest] + slots[closest] % branches[closest];
        }
        i64 booking = min(slots[closest] - waste, people);
        if(booking == people) {
            slots[closest] -= booking + waste;
            people -= booking;
            finishes[closest] = limit - slots[closest]/branches[closest];
        }
    }
    if(!people) {
        slots[pos] = 0;
        branches[pos] = 0;
        return isPossible(n, pos-1, limit, coins, ar, dist, branches, slots, finishes, closest, distClosest + dist[pos]);
    }
    for(int branch = people / limit + (people % limit ? 1 : 0);branch <= coins;branch++) {
        i64 key = branch*n+pos;
        if(dp.count(key) && dp[key]<=limit) {
            return true;
        }
        branches[pos] = branch;
        slots[pos] = branch * limit - people;
        finishes[pos] = limit - slots[pos]/branch;
        if(isPossible(n, pos-1, limit, coins-branch, ar, dist, branches, slots, finishes, pos, dist[pos])) {
            dp[key] = limit;
            return true;
        }
    }
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
		i64 ar[n], dist[n];
		for(i64 i=0;i<n;i++) {
			fastscan(ar[i]);
			if(zExist && !ar[i]) {
				i--;n--;
				zeroes++;
			} else {
				zExist = false;
			}
		}
		if(!n) zeroes--;
		while(zeroes--) {
			fastscan(dist[0]);
		}
		for(i64 i=1;i<n;i++) {
			fastscan(dist[i]);
		}
		if(!n) {
			printf("0\n");
			continue;
		}
		while(!ar[n-1]) {
			n--;
		}
		i64 low = 1, high = 10000000000000000LL, total, steps;
		i64 ans, mid;
		bool valid;
		i64 people, slots[n], booking, branch;
		i64 finishes[n], waste, branches[n];
		while(low <= high) {
			dp.clear();
			valid = true;
			mid = low/2 + high/2 + ((low & 1) + (high & 1)) / 2;
			total = 0;
			for(i64 i=0;i<n;i++) {
				people = ar[n-i-1];
				steps = 0;
				for(i64 j=n-i;steps < mid && j < n && people;j++) {
					steps += dist[j];
					if(steps < mid && slots[j]) {
						waste = steps - finishes[j];
						if(waste < 0) {
							waste = 0;
						} else {
							waste = waste * branches[j] + slots[j] % branches[j];
						}
						booking = min(slots[j] - waste, people);
						if(booking == people) {
							slots[j] -= booking + waste;
							people -= booking;
							finishes[j] = mid - slots[j]/branches[j];
						}
					}
					if(branches[j]) break;
				}
				if(!people) {
					slots[n-i-1] = 0;
					branches[n-i-1] = 0;
					continue;
				}
				branch = people / mid;
				if(people % mid) branch++;
				total += branch;
				if(total > x) {
					valid = false;
					break;
				}
				slots[n-i-1] = branch * mid - people;
				finishes[n-i-1] = mid - slots[n-i-1]/branch;
				branches[n-i-1] = branch;
			}
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
		low = 1;high = ans;
		// while(low <= high) {
	 //        mid = low/2 + high/2 + ((low & 1) + (high & 1)) / 2;
	 //        valid = isPossible(n, n-1, mid, x, ar, dist, branches, slots, finishes, -1, 0);
	 //        if(valid) {
	 //            ans = mid;
	 //            high = mid - 1;
	 //        } else {
	 //            low = mid + 1;
	 //        }
	 //    }
		while(ans-1 && isPossible(n, n-1, ans-1, x, ar, dist, branches, slots, finishes, -1, 0)) {
			ans--;
		}
		printf("%lld\n", ans);
	}
	return 0;
}