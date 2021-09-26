#include <bits/stdc++.h>
#define i64 long long
#define F first
#define S second
#define MOD 1000000007
#define pair pair<int, int>
#define pb push_back
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
	int n;
    cin>>n;
    int adj[n][n] = {0};
    for(int i=0;i<n;i++) {
        fill(adj[i], adj[i]+n, 0);
    }
    char prev[n], color;
    int parity[n] = {0}, part;
    fill(parity, parity+n, 0);
    for(int i=1;i<n;i++) {
        // cout<<"Stage: "<<i+1<<endl;
        cout<<"? "<<i<<endl;
        cin>>prev[i-1];
        cout<<"? "<<i+1<<endl;
        cin>>prev[i];
        for(int j=1;j<=i;j++) { 
            cout<<"? "<<j<<endl;
            cin>>color;
            part = (color != prev[j-1]);
            // cout<<"Case: "<<j<<" ->  "<<part<<" old "<<parity[j-1]<<endl;
            if(part != parity[j-1]) {
                adj[j-1][i] = 1;
                parity[i] = 1-parity[i];
            }
            parity[j-1] = part;
            prev[j-1] = color;
        }
    }
    cout<<"!\n";
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cout<<adj[min(i,j)][max(i,j)];
        }cout<<endl;
    }
	return 0;
}