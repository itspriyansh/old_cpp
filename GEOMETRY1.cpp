#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define i64 long long
#define F first
#define S second
#define MOD 1000000007
// #define pair pair<int, int>
#define pb push_back
#define endl '\n'
#define matrix vector<vector<int>>
#define INF INT32_MAX
#define double long double
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

struct Point {
    double x,y;

    Point() {}

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

struct Fraction {
    double a,b;

    Fraction() {}

    Fraction(double a, double b) {
        this->a = a;
        this->b = b;
    }

    void add(Fraction x) {
        a = a*x.b + x.a*b;
        b = b*x.b;
    }
};

struct Equation {
    double a, b, c;

    Equation () {}

    Equation(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    Equation(Point &a, Point &b) {
        this->a = b.y-a.y;
        this->b = a.x-b.x;
        if(this->a <= 0 && this->b <= 0) {
            this->a = -this->a;
            this->b = -this->b;
        }
        if(this->a == 0) {
            this->b = 1;
        }
        this->c = 0.0;
    }

    Fraction cot(Equation &eq) {
        Fraction m1(this->a, this->b), m2(eq.a, eq.b);
        Fraction f(m1.b*m2.b+m1.a*m2.a, m1.a*m2.b - m2.a*m1.b);
        return f;
    }

    Fraction cot2(Equation &eq) {
        Fraction m1(this->a, this->b), m2(eq.a, eq.b);
        Fraction f(m1.a*m2.b - m1.b*m2.a, m1.b*m2.b + m1.a*m1.b);
        Fraction cosSq(f.b*f.b, f.a*f.a+f.b*f.b);
        Fraction ans;
        ans.a = cosSq.b - cosSq.a;
        ans.b = sqrt(cosSq.b) - sqrt(cosSq.a);
        return ans;
    }
};

double getArea(Point ar[]) {
    double ans = 0.0;
    for(int i=0;i<3;i++) {
        int j = (i+1) % 3, k = (j+1) % 3;
        ans += ar[i].x * (ar[j].y - ar[k].y);
    }
    return fabs(ans) / 2.0;
}

double getDist(Point &a, Point &b) {
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	fastio

    int t;
    scanf("%d", &t);
    while(t--) {
        int n, q;
        scanf("%d %d", &n, &q);
        Point polygon[n];
        for(int i=0;i<n;i++) {
            scanf("%Lf %Lf", &polygon[i].x, &polygon[i].y);
        }
        double area = 0.0;
        Point ar[3];
        ar[0] = polygon[0];
        for(int i=1;i+1<n;i++) {
            ar[1] = polygon[i];
            ar[2] = polygon[i+1];
            area += getArea(ar);
        }
        double baseSq = getDist(polygon[1], polygon[2]);
        double base = sqrt(baseSq);
        Equation eqs[3];
        for(int i=0,j;i<3;i++) {
            j = (i+1)%n;
            Equation eq(polygon[i], polygon[j]);
            eqs[i] = eq;
        }
        Fraction addon = eqs[0].cot2(eqs[1]);
        addon.add(eqs[1].cot2(eqs[2]));

        double dist;
        int v,time;

        while(q--) {
            scanf("%d %d", &v, &time);
            dist = (double)v * time;
            
            double ans = (area * (base * addon.b + dist * addon.a) * (base * addon.b + dist * addon.a)) / (baseSq * addon.b * addon.b);
            printf("%Lf\n", ans);
        }
    }
	return 0;
}