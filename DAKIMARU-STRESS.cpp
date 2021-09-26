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

void fastscan(i64 &number, int base, int phi=0) {
    number = rand() % base + phi;
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

i64 findBranch(i64 ar[], i64 dist[], i64 n, i64 coins, i64 pos, i64 range, i64 limit) {
	i64 low = ar[pos]/limit + (ar[pos]%limit ? 1 : 0);
	i64 high = coins;
	i64 branch = coins+1, slot, finish, steps, waste, booking;
	bool valid;
	while(low <= high) {
		i64 mid = low/2 + high/2 + ((low&1) + (high&1))/2;
		slot = mid * limit - ar[pos];
		finish = limit - slot/mid;
		steps = 0;
		valid = true;
		for(int i=pos-1;i>=pos-range;i--) {
			steps += dist[i];
			if(steps >= limit) {
				valid = false;
				break;
			}
			waste = steps - finish;
			if(waste < 0) {
				waste = 0;
			} else {
				waste = waste * mid + slot % mid;
			}
			booking = min(slot - waste, ar[i]);
			if(booking == ar[i]) {
				slot -= booking + waste;
				finish = limit - slot/mid;
			} else {
				valid = false;
				break;
			}
		}
		if(valid) {
			branch = mid;
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return branch;
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

bool isPossible2(i64 n, i64 pos, i64 limit, i64 coins, i64 ar[], i64 dist[], i64 branches[], i64 slots[], i64 finishes[], i64 closest, i64 distClosest) {
	if(coins < 0) return false;
	if(pos < 0) return true;
	if(dp.count(pos) && dp[pos] >= coins) return false;
	i64 people = ar[pos];
	/*if(closest != -1 && slots[closest] && distClosest < limit) {
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
	}*/
	if(!people) {
		slots[pos] = 0;
		branches[pos] = 0;
		finishes[pos] = 0;
		return isPossible2(n, pos-1, limit, coins, ar, dist, branches, slots, finishes, closest, distClosest + dist[pos]);
	}
	for(i64 i=0;i<=pos;i++) {
		// i64 branch = findBranch(ar, dist, n, pos, i, limit);
		i64 branch = prec[pos-i][pos];
		// cout<<pos<<" & "<<branch<<" for range "<<i<<" and limit "<<limit<<" coins "<<coins<<endl;
		if(branch > coins) {
			break;
		}
	// for(i64 branch = people / limit + (people % limit ? 1 : 0);branch <= coins;branch++) {
		i64 key = branch*n+pos;
		// if(dp.count(key) && dp[key]<=limit) {
		// 	return true;
		// }
		branches[pos] = branch;
		finishes[pos] = i;
		for(int j=pos-1;j>=pos-i;j--) {
			branches[j] = 0;
			finishes[j] = i-pos+j;
		}
		slots[pos] = branch * limit - people;
		// finishes[pos] = limit - slots[pos]/branch;
		if(isPossible2(n, pos-i-1, limit, coins-branch, ar, dist, branches, slots, finishes, pos, dist[pos])) {
			// dp[key] = limit;
			return true;
		}
	}
	dp[pos] = max(dp[pos], coins);
	return false;
}

int solveFast(const i64 N, const i64 X, const i64 AR[], const i64 DIST[]) {
	i64 n, x, zeroes=0, KK=0;
	bool zExist = true;
	n = N;
	x = X;
	i64 ar[n], dist[n];
	for(i64 i=0,j=0;i<n;i++) {
		ar[i] = AR[j++];
		if(zExist && !ar[i]) {
			i--;n--;
			zeroes++;
		} else {
			zExist = false;
		}
	}
	if(!n) zeroes--;
	while(zeroes--) {
		dist[0] = DIST[KK++];
	}
	for(i64 i=1;i<n;i++) {
		dist[i] = DIST[KK++];
	}
	if(!n) {
		return 0;
	}
	while(!ar[n-1]) {
		n--;
	}
	// for(int i=0;i<n;i++) {
	// 	cout<<ar[i];
	// 	if(i) cout<<"("<<dist[i]<<")";
	// 	cout<<" ";
	// }cout<<endl;
	i64 low = 1, high = 10000000000000000LL, total, steps;
	i64 ans, mid;
	bool valid;
	i64 people, slots[n], booking, branch;
	i64 finishes[n], waste, branches[n];
	while(low <= high) {
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
	return ans;
}

int solveNaive(const i64 N, const i64 X, const i64 AR[], const i64 DIST[]) {
	dp.clear();
	i64 n, x, zeroes=0, KK=0;
	bool zExist = true;
	n = N;
	x = X;
	i64 ar[n], dist[n];
	for(i64 i=0,j=0;i<n;i++) {
		ar[i] = AR[j++];
		if(zExist && !ar[i]) {
			i--;n--;
			zeroes++;
		} else {
			zExist = false;
		}
	}
	if(!n) zeroes--;
	while(zeroes--) {
		dist[0] = DIST[KK++];
	}
	for(i64 i=1;i<n;i++) {
		dist[i] = DIST[KK++];
	}
	if(!n) {
		return 0;
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
        mid = low/2 + high/2 + ((low & 1) + (high & 1)) / 2;
        valid = isPossible(n, n-1, mid, x, ar, dist, branches, slots, finishes, -1, 0);         
        if(valid) {
            ans = mid;
            high = mid - 1;
            // cout<<"ANS: "<<ans<<endl;
            // for(i64 b: branches) {
            //  cout<<b<<" ";
            // }cout<<endl;
            // for(i64 b: finishes) {
            //  cout<<b<<" ";
            // }cout<<endl;
        } else {
            low = mid + 1;
        }
    }
	return ans;
}

int solveNaive2(const i64 N, const i64 X, const i64 AR[], const i64 DIST[]) {
	// dp.clear();
	i64 n, x, zeroes=0, KK=0;
	bool zExist = true;
	n = N;
	x = X;
	i64 ar[n], dist[n], arc[n], distr[n];
	for(i64 i=0,j=0;i<n;i++) {
		ar[i] = AR[j++];
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
		dist[0] = DIST[KK++];
	}
	distr[0] = 0;
	for(i64 i=1;i<n;i++) {
		dist[i] = DIST[KK++];
		distr[i] = dist[i] + (i-1 ? distr[i-1] : 0);
	}
	if(!n) {
		return 0;
	}
	while(!ar[n-1]) {
		n--;
	}
	// for(int i=0;i<n;i++) {
	// 	cout<<ar[i];
	// 	if(i) cout<<"("<<dist[i]<<")";
	// 	cout<<" ";
	// }cout<<endl;
	i64 low = 1, high = 10000000000000000LL, total, steps;
    i64 ans, mid;
    bool valid;
    i64 people, slots[n], booking, branch;
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
        // cout<<"Limit is: "<<mid<<endl;
        // for(int i=0;i<n;i++) {
        // 	for(int j=i;j<n;j++) {
        // 		if(prec[i][j] == INT64_MAX) cout<<"INF";
        // 		else cout<<prec[i][j];
        // 		i64 expected = findBranch(ar, dist, n, j, j-i, mid);
        // 		cout<<"(";
        // 		if(expected == INT64_MAX) cout<<"INF";
        // 		else cout<<expected;
        // 		cout<<") ";
        // 	}cout<<endl;
        // }cout<<"--------------\n";
        valid = isPossible2(n, n-1, mid, x, ar, dist, branches, slots, finishes, -1, 0);         
        if(valid) {
            ans = mid;
            high = mid - 1;
            // cout<<"ANS: "<<ans<<endl<<" => ";
            // for(i64 b: branches) {
            //  cout<<b<<" ";
            // }cout<<endl<<" -> ";
            // for(i64 b: finishes) {
            //  cout<<b<<" ";
            // }cout<<endl;
        } else {
            low = mid + 1;
        }
    }

	return ans;
}

int main() {
	// #ifndef ONLINE_JUDGE
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	// #endif
	// fastio

	cout<<"Processing....\n";
	i64 t=1000000000LL;
	// srand(time(0));
	// fastscan(t);
	while(t--) {
		i64 n, x;
		fastscan(n,7,2);
		fastscan(x, 16, 1);
		i64 ar[n], dist[n];
		for(i64 i=0;i<n;i++) {
			fastscan(ar[i], 8);
		}
		for(i64 i=0;i+1<n;i++) {
			fastscan(dist[i], 8, 1);
		}
		i64 b = solveNaive2(n, x, ar, dist), a = solveNaive(n, x, ar, dist);
		if(a != b) {
			cout<<"Failed! Test No "<<1000000000LL-t<<"\n";
			cout<<n<<" "<<x<<endl;
			for(int i=0;i<n;i++) {
				if(i) cout<<' ';
				cout<<ar[i];
			}cout<<endl;
			for(int i=0;i+1<n;i++) {
				if(i) cout<<' ';
				cout<<dist[i];
			}cout<<endl;
			cout<<"Expected: "<<a<<" Result: "<<b<<endl;
			break;
		}
	}
	cout<<"Finished!\n";
	return 0;
}