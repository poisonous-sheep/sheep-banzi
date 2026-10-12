// ABC139F https://atcoder.jp/contests/abc139/tasks/abc139_f
#include <bits/stdc++.h>
using namespace std;
#define int long long

using db = long double;
const db EPS = 1e-9L;
int sign(db x) {
    return x < -EPS ? -1 : x > EPS ? 1 : 0;
}
struct P {
    db x = 0, y = 0;
    P() {
    }
    P(db x, db y) : x(x), y(y) {
    }
    P operator+(P p) const {
        return {x + p.x, y + p.y};
    }
    P operator-(P p) const {
        return {x - p.x, y - p.y};
    }
    P operator*(db k) const {
        return {x * k, y * k};
    }
    P operator/(db k) const {
        return {x / k, y / k};
    }
    bool operator<(P p) const {
        return x != p.x ? x < p.x : y < p.y;
    }
    db dot(P p) const {
        return x * p.x + y * p.y;
    }
    db det(P p) const {
        return x * p.y - y * p.x;
    }
    db abs2() const {
        return dot(*this);
    }
    db abs() const {
        return sqrtl(abs2());
    }
    db distTo(P p) const {
        return (*this - p).abs();
    }
    db alpha() const {
        return atan2l(y, x);
    }
    P rot90() const {
        return {-y, x};
    }
    P rot(db a) const {
        return {x * cosl(a) - y * sinl(a), x * sinl(a) + y * cosl(a)};
    }
    P unit() const {
        assert(abs2() > 0);
        return *this / abs();
    }
    int quad() const {
        return y > 0 || (y == 0 && x >= 0);
    }
    void read() {
        cin >> x >> y;
    }
};
struct Geometry {
    db cross(P a, P b, P c) {
        return (b - a).det(c - a);
    }
    bool intersect(db a, db b, db c, db d) {
        if (a > b)
            swap(a, b);
        if (c > d)
            swap(c, d);
        return sign(b - c) >= 0 && sign(d - a) >= 0;
    }
    bool onSeg(P a, P b, P p) {
        return !sign(cross(a, b, p)) && sign((p - a).dot(p - b)) <= 0;
    }
    bool onSeg_strict(P a, P b, P p) {
        return !sign(cross(a, b, p)) && sign((p - a).dot(p - b)) < 0;
    }
    bool isSS(P a, P b, P c, P d) {
        return intersect(a.x, b.x, c.x, d.x) && intersect(a.y, b.y, c.y, d.y) &&
               sign(cross(a, b, c)) * sign(cross(a, b, d)) <= 0 &&
               sign(cross(c, d, a)) * sign(cross(c, d, b)) <= 0;
    }
    bool isSS_strict(P a, P b, P c, P d) {
        return sign(cross(a, b, c)) * sign(cross(a, b, d)) < 0 &&
               sign(cross(c, d, a)) * sign(cross(c, d, b)) < 0;
    }
    bool chkLL(P a, P b, P c, P d) {
        return sign((b - a).det(d - c)) != 0;
    }
    P isLL(P a, P b, P c, P d) {
        assert(chkLL(a, b, c, d));
        return a + (b - a) * ((c - a).det(d - c) / (b - a).det(d - c));
    }
    P proj(P a, P b, P p) {
        P v = b - a;
        assert(v.abs2() > 0);
        return a + v * (v.dot(p - a) / v.abs2());
    }
    P reflect(P a, P b, P p) {
        return proj(a, b, p) * 2 - p;
    }
    db nearest(P a, P b, P p) {
        if ((b - a).abs2() == 0)
            return p.distTo(a);
        P v = b - a;
        db t = clamp(v.dot(p - a) / v.abs2(), 0.0L, 1.0L);
        return p.distTo(a + v * t);
    }
    db disSS(P a, P b, P c, P d) {
        if (isSS(a, b, c, d))
            return 0;
        return min(
            {nearest(a, b, c), nearest(a, b, d), nearest(c, d, a), nearest(c, d, b)});
    }
};

static bool cmp(P a, P b) {
    if (a.quad() != b.quad())
        return a.quad() > b.quad();
    db z = a.det(b);
    if (z != 0)
        return z > 0;
    return a.abs2() < b.abs2();
}
void run(vector<P> &a) {
    sort(a.begin(), a.end(), cmp);
}

void init_model() {
}

void solve() {
    int n;
    cin >> n;
    vector<P> a;
    while (n--) {
        P p;
        p.read();
        if (p.abs2() > 0)
            a.push_back(p);
    }
    ::init_model();
    ::run(a);
    n = a.size();
    db ans = 0;
    for (int i = 0; i < n; i++) {
        P s;
        for (int k = 0; k < n; k++) {
            s = s + a[(i + k) % n];
            ans = max(ans, s.abs2());
        }
    }
    cout << fixed << setprecision(12) << sqrtl(ans) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}
