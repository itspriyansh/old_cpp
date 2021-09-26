#include <bits/stdc++.h>
#define i64 long long
#define LIM 4000002
#define pb push_back
using namespace std;

void fastscan(int &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register int c;
  
    number = 0;
  
    // extract current character from buffer
    c = getchar();
    if (c=='-')
    {
        // number is negative
        negative = true;
  
        // extract the next character from the buffer
        c = getchar();
    }
  
    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
  
    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	
	unordered_map<int, int> dp;
	unordered_map<int, i64> pd;
	vector<int> div, div2;
	int t;
	fastscan(t);
	while(t--) {
		int n;
		fastscan(n);
		if(pd.count(n)) {
			printf("%lld\n", pd[n]);
			continue;
		}
		n *= 2;
		int k = n*2+1;
		i64 ans = n;
		//dp.clear();
		div.clear();
		div2.clear();
		div2.pb(k);
		for(i64 i=3;i*i<=k;i+=2) {
			if(k%i) continue;
			div.pb(i);
			if(k/i != i) {
				div2.pb(k/i);
			}
		}
		for(int i=div2.size()-1;i>=0;i--) {
			div.pb(div2[i]);
		}
		for(auto i=div.begin();i!=div.end();i++) {
			if(!dp.count(*i)) {
				dp[(*i)] = (*i)-1;
				for(auto j=div.begin();j!=i;j++) {
					if((*i)%(*j)) continue;
					dp[(*i)] -= dp[(*j)];
				}
			}
			// cout<<(*i)<<" -> "<<dp[(*i)]<<endl;
			ans += (i64)dp[(*i)] * (n+1+((*i)-1)/2)/(*i);
		}
		pd[n/2] = ans;
		printf("%lld\n", ans);
	}
	return 0;
}