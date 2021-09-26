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
#define LIM 1000000
using namespace std;

bitset<LIM> isprime;
unordered_set<string> primes;

void fastscan(int &number) {
    bool negative = false;
    register int c;
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

string getString(char x) {
    string s(1, x);
 
    return s;  
}

void recur(int n, int pos, string &str, string &ans, string &cur, int lim) {
    if(!cur.empty() && !primes.count(cur)) {
        ans = cur;
    }
    if(pos>=n || lim<0 || (!ans.empty() && ans.size() <= cur.size())) {
        return;
    }
    recur(n, pos+1, str, ans, cur, lim);
    cur.pb(str[pos]);
    recur(n, pos+1, str, ans, cur, lim-1);
    cur.pop_back();
}

string solve(int n, string &str) {
    for(int i=0;i<n;i++) {
        if(!primes.count(getString(str[i]))) {
            return getString(str[i]);
        }
    }
    unordered_set<char> st;
    for(int i=0;i<n;i++) {
        if(st.count(str[i])) {
            return getString(str[i])+str[i];
        }
        st.insert(str[i]);
    }
    string ans, cur;
    recur(n, 0, str, ans, cur, 5);
    return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

    for(i64 i=2;i<LIM;i++) {
        if(isprime[i]) continue;
        primes.insert(to_string(i));
        for(i64 j=i*i;j<LIM;j+=i) {
            isprime[j] = 1;
        }
    }
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        string str;
        cin>>str;
        string ans = solve(n, str);
        cout<<ans.size()<<'\n'<<ans<<'\n';
    }
	return 0;
}