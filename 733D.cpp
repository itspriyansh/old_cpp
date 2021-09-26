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
	fastio

    int t;
    fastscan(t);
    while(t--) {
        int n;
        fastscan(n);
        int ar[n];
        unordered_set<int> indegree[n];
        stack<int> popular, introvert;
        for(int i=0;i<n;i++) {
            fastscan(ar[i]);
            ar[i]--;
            indegree[ar[i]].insert(i);
            if(indegree[ar[i]].size() == 2) {
                popular.push(ar[i]);
            }
        }
        for(int i=0;i<n;i++) {
            if(indegree[i].empty()) {
                introvert.push(i);
            }
        }
        int fulfilled = n-introvert.size();
        while(!popular.empty()) {
            int p = popular.top(), z;popular.pop();
            int m = indegree[p].size()-1;
            auto it = indegree[p].begin();
            while(m) {
                int r = introvert.top();introvert.pop();
                if(*it == r) {
                    it++;
                    if(it == indegree[p].end()) it = indegree[p].begin();
                }
                z = *it;
                ar[z] = r;
                it++;
                indegree[p].erase(z);
                if(it == indegree[p].end()) it = indegree[p].begin();
                m--;
            }
        }
        printf("%d\n", fulfilled);
        for(int a: ar) {
            printf("%d ", a+1);
        }
        printf("\n");
    }

	return 0;
}