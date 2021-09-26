#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n;
        scanf("%d", &n);
        long long a = -1, b, ans = 0;
        while(n--) {
            scanf("%dll", &b);
            if(a != -1) {
                ans = max(ans, a*b);
            }
            a = b;
        }
        printf("%lld\n", ans);
    }
    return 0;
}