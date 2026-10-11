#include <bits/stdc++.h>
using namespace std;
#define int long long

// 曼哈顿距离坐标旋转：用u=x+y,v=x-y把平面曼哈顿距离变为旋转坐标的切比雪夫距离；最大距离只需两维极值。
// add/qur/diameter O(1)；建n点O(n)时间/O(1)额外空间。
struct Manhattan {
    int mn1 = LLONG_MAX, mx1 = LLONG_MIN, mn2 = LLONG_MAX, mx2 = LLONG_MIN;
    void init() {
        mn1 = mn2 = LLONG_MAX;
        mx1 = mx2 = LLONG_MIN;
    }
    void add(int x, int y) {
        int u = x + y, v = x - y;
        mn1 = min(mn1, u);
        mx1 = max(mx1, u);
        mn2 = min(mn2, v);
        mx2 = max(mx2, v);
    }
    int diameter() {
        assert(mn1 != LLONG_MAX);
        return max(mx1 - mn1, mx2 - mn2);
    }
    int qur(int x, int y) {
        assert(mn1 != LLONG_MAX);
        int u = x + y, v = x - y;
        return max({llabs(u - mn1), llabs(u - mx1), llabs(v - mn2), llabs(v - mx2)});
    }
};

struct ManhattanSeg {
    int n;
    vector<Manhattan> seg;
    ManhattanSeg(int n = 0) : n(n), seg(4 * n + 4) {}
    Manhattan merge(Manhattan a, Manhattan b) {
        a.mn1 = min(a.mn1, b.mn1);
        a.mx1 = max(a.mx1, b.mx1);
        a.mn2 = min(a.mn2, b.mn2);
        a.mx2 = max(a.mx2, b.mx2);
        return a;
    }
    void change(int u, int l, int r, int p, int x, int y) {
        if (l == r) {
            seg[u].init();
            seg[u].add(x, y);
            return;
        }
        int m = (l + r) >> 1;
        if (p <= m)
            change(u << 1, l, m, p, x, y);
        else
            change(u << 1 | 1, m + 1, r, p, x, y);
        seg[u] = merge(seg[u << 1], seg[u << 1 | 1]);
    }
    Manhattan qur(int u, int l, int r, int L, int R) {
        if (L <= l && r <= R)
            return seg[u];
        int m = (l + r) >> 1;
        Manhattan ans;
        if (L <= m)
            ans = merge(ans, qur(u << 1, l, m, L, R));
        if (R > m)
            ans = merge(ans, qur(u << 1 | 1, m + 1, r, L, R));
        return ans;
    }
    void change(int p, int x, int y) {
        change(1, 1, n, p, x, y);
    }
    Manhattan qur(int l, int r) {
        return qur(1, 1, n, l, r);
    }
};

void solve() {
    int n;
    cin >> n;
    Manhattan t;
    while (n--) {
        int x, y;
        cin >> x >> y;
        t.add(x, y);
    }
    cout << t.diameter() << '\n';
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
