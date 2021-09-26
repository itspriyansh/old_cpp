#include <bits/stdc++.h>
using namespace std;

int get(int a, int parent[]) {
	return a==parent[a] ? a : parent[a]=get(parent[a], parent);
}

void unite(int a, int b, int parent[]) {
	int s1=get(a, parent), s2=get(b, parent);
	if(s1 != s2) {
		parent[s1] = parent[s2] = max(s1, s2);
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#else
	// online submission
	#endif

	int n,q;
	cin>>n>>q;
	int ar[n]={0}, par[n+1];
	iota(par, par+n+1, 0);
	int query[q][3];
	for(int i=0;i<q;i++) {
		for(int j=0;j<3;j++) {
			cin>>query[i][j];
		}
	}

	for(int i=q-1;i>=0;i--) {
		for(int j=get(query[i][0]-1, par);j<=query[i][1]-1;j=get(j, par)) {
			ar[j] = query[i][2];
			unite(j, j+1, par);
		}
	}

	for(int i=0;i<n;i++) {
		cout<<ar[i]<<endl;
	}

	return 0;
}