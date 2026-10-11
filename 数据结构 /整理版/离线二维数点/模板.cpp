#include <bits/stdc++.h>
using namespace std;
#define int long long

// 离线二维数点：按x扫描，树状数组维护y；四次前缀容斥回答闭矩形计数，允许重复点。
// O((n+q)log(n+q))时间、O(n+q)空间。
struct RectangleCounter {
    struct point {
        int x, y;
    };
    struct query {
        int l, b, r, t;
    };
    vector<point> a;
    vector<query> q;
    void init() {
        a.clear();
        q.clear();
    }
    void add(int x, int y) {
        a.push_back({x, y});
    }
    void ask(int l, int b, int r, int t) {
        assert(l <= r && b <= t);
        q.push_back({l, b, r, t});
    }
    vector<int> run() {
        struct event {
            int x, y, id, sgn;
            bool strictx, stricty;
        };
        vector<event> e;
        vector<int> ys, ans(q.size());
        for (auto p : a)
            ys.push_back(p.y);
        for (int i = 0; i < (int)q.size(); i++) {
            auto z = q[i];
            e.push_back({z.r, z.t, i, 1, false, false});
            e.push_back({z.l, z.t, i, -1, true, false});
            e.push_back({z.r, z.b, i, -1, false, true});
            e.push_back({z.l, z.b, i, 1, true, true});
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        sort(a.begin(), a.end(), [](point p, point q) { return p.x < q.x; });
        sort(e.begin(), e.end(), [](event p, event q) {
            if (p.x != q.x)
                return p.x < q.x;
            return p.strictx > q.strictx;
        });
        vector<int> c(ys.size() + 1);
        int j = 0;
        for (auto z : e) {
            while (j < (int)a.size() &&
                   (a[j].x < z.x || (!z.strictx && a[j].x == z.x))) {
                int k = lower_bound(ys.begin(), ys.end(), a[j].y) - ys.begin() + 1;
                for (; k < (int)c.size(); k += k & -k)
                    c[k]++;
                j++;
            }
            int k = (z.stricty ? lower_bound(ys.begin(), ys.end(), z.y)
                               : upper_bound(ys.begin(), ys.end(), z.y)) -
                    ys.begin(),
                s = 0;
            for (; k; k -= k & -k)
                s += c[k];
            ans[z.id] += z.sgn * s;
        }
        return ans;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    RectangleCounter t;
    while (n--) {
        int x, y;
        cin >> x >> y;
        t.add(x, y);
    }
    while (m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        t.ask(a, b, c, d);
    }
    for (int x : t.run())
        cout << x << '\n';
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
