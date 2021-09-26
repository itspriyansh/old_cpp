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

    void print() {
        printf("%Lf %Lf\n", x, y);
    }
};

struct Fraction {
    double a,b;

    Fraction() {}

    Fraction(double a, double b) {
        this->a = a;
        this->b = b;
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

    void print() {
        printf("%Lfx + %Lfy = %Lf\n", a, b, c);
    }
};

double getArea(Point a, Point b, Point c) {
    return fabs(a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y)) / 2.0;
}

Fraction getArea(Point &a, Point &b, pair<Fraction, Fraction> &c) {
    return *(new Fraction(fabs(a.x*(b.y*c.S.b-c.S.a)*c.F.b + b.x*(c.S.a-a.y*c.S.b)*c.F.b + c.F.a*(a.y-b.y)*c.S.b), (2.0 * c.F.b * c.S.b)));
}

double getDist(Point &a, Point &b) {
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

double getHeight(pair<Fraction, Fraction> &cnt, Point &a, Point &b) {
    Equation eq(b.y-a.y, a.x-b.x, 0);
    eq.c = a.x*eq.a + a.y*eq.b;
    // eq.print();
    Fraction h;
    h.a = sqrt(eq.a*eq.a + eq.b*eq.b)*cnt.F.b*cnt.S.b;
    h.b = fabs(eq.a*cnt.F.a*cnt.S.b + eq.b*cnt.S.a*cnt.F.b - eq.c*cnt.F.b*cnt.S.b);
    // printf("Returning: %Lf\n", h.a/h.b);
    return h.a / h.b;
}

double getHeight2(pair<Fraction, Fraction> &cnt, Point &a, Point &b) {
    Point p(cnt.F.a/cnt.F.b, cnt.S.a/cnt.S.b);
    // printf("Returning 2: %Lf\n", getDist(a, b) / (2.0 * getArea(a, b, cnt)));
    Fraction area = getArea(a, b, cnt);
    return (getDist(a, b) * area.b) / (2.0 * area.a);
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
        pair<Fraction, Fraction> centroid;
        double area = 0, sumX = 0, sumY = 0, lc;
        for(int i=0;i<n;i++) {
            scanf("%Lf %Lf", &polygon[i].x, &polygon[i].y);
            if(i>=2) {
                lc = getArea(polygon[0], polygon[i-1], polygon[i]);
                area += lc;
                sumX += lc * (polygon[0].x + polygon[i-1].x + polygon[i].x);
                sumY += lc * (polygon[0].y + polygon[i-1].y + polygon[i].y);
            }
        }

        centroid.F.a = sumX;
        centroid.F.b = (3.0*area);
        centroid.S.a = sumY;
        centroid.S.b = (3.0*area);
        // printf("Area: %Lf\n", area);
        // printf("centroid: (%Lf/%Lf, %Lf/%Lf)\n", centroid.F.a,centroid.F.b, centroid.S.a,centroid.S.b);
        double heights = 0.0, perimeter = 0.0;

        for(int i=0;i<n;i++) {
            perimeter += sqrt(getDist(polygon[i], polygon[(i+1)%n]));
            heights += getHeight2(centroid, polygon[i], polygon[(i+1)%n]);
        }
        // printf("Height Sum: %Lf\n", heights);
        // printf("Perimeter: %Lf\n", perimeter);

        double dist;
        int v,time;
        while(q--) {
            scanf("%d %d", &v, &time);
            dist = (double)v * time;
            
            double ans = area + dist * perimeter + (dist*dist*heights) / 2.0;
            printf("%Lf\n", ans);
        }
    }

	return 0;
}