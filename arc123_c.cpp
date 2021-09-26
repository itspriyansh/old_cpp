#include <bits/stdc++.h>
#define i64 long long
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int t, x;
    scanf("%d", &t);
    i64 n, m;
    int digits[20], remains[20], carry;
    while(t--) {
        scanf("%lld", &n);
        m = n;
        int len = 0;
        int ans = 0;
        while(n) {
            digits[len++] = n%10;
            n /= 10;
        }
        n = m;
        // cout<<"Len: "<<len<<endl;
        // for(int y=0;y<len;y++) {
        //     cout<<digits[y]<<" ";
        // }cout<<endl;
        for(int i=0;i<len;i++) {
            remains[i] = digits[i] / 3 + (digits[i]%3 ? 1 : 0);
            if(i && remains[i] > remains[i-1]) {
                for(int j=0;j<i;j++) {
                    if(remains[j] >= remains[i]) continue;
                    if(digits[j] >= remains[i]) {
                        remains[j] = remains[i];
                    } else {
                        digits[j] = digits[j] + 10;
                        remains[j] = digits[j] / 3 + (digits[j]%3 ? 1 : 0);
                        i = j-1;
                        carry = 1;
                        for(int k=j+1;carry && k<len;k++) {
                            digits[k] -= carry;
                            if(digits[k] < 0) {
                                digits[k] += 10;
                                carry = 1;
                            } else {
                                carry = 0;
                            }
                        }
                        while(!digits[len-1]) len--;
                        break;
                    }
                }
            }
        }
        // for(int y=0;y<len;y++) {
        //     cout<<digits[y]<<" ";
        // }cout<<endl;
        // for(int y=0;y<len;y++) {
        //     cout<<remains[y]<<" ";
        // }cout<<endl;
        for(int i=0;i<len;i++) {
            ans = max(ans, remains[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}