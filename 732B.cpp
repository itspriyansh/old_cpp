#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define MOD 1000000007
#define pair pair<int, int>
#define pb push_back
// #define endl '\n'
#define matrix vector<vector<int>>
#define INF INT32_MAX
using namespace std;

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

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	// fastio

    int t;
    cin>>t;
    while(t--) {
        int n, m;
        cin>>n>>m;
        string str;
        unordered_map<char, int> dp[m];
        for(int i=0;i<n;i++) {
            cin>>str;
            for(int j=0;j<m;j++) {
                dp[j][str[j]]++;
            }
        }
        for(int i=1;i<n;i++) {
            cin>>str;
            for(int j=0;j<m;j++) {
                dp[j][str[j]]--;
                if(!dp[j][str[j]]) {
                    dp[j].erase(str[j]);
                }
            }
        }
        for(int i=0;i<m;i++) {
            printf("%c", dp[i].begin()->first);
        }
        printf("\n");
        fflush(stdout);
    }

	return 0;
}