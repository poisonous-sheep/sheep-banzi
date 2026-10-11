#include <bits/stdc++.h>
using namespace std;
#define int long long

// 普通线段树：单点赋值、区间最小值；数组1-based，查询为闭区间。
// 建树O(n)，修改/查询O(log n)，空间O(n)。
struct SegTree {
    struct info {
        int mn;
        friend info operator+(const info &l, const info &r) {
            return {min(l.mn, r.mn)};
        }
    };
    struct node {
        info val;
    };
    int n = 0;
    vector<node> seg;
    SegTree(int n_ = 0) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        seg.assign(4 * n + 4, {});
    }
    int ls(int id) {
        return id << 1;
    }
    int rs(int id) {
        return id << 1 | 1;
    }
    void update(int id) {
        seg[id].val = seg[ls(id)].val + seg[rs(id)].val;
    }
    void build(int id, int l, int r, const vector<int> &a) {
        if (l == r) {
            seg[id].val = {a[l]};
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(id), l, mid, a);
        build(rs(id), mid + 1, r, a);
        update(id);
    }
    void change(int id, int l, int r, int pos, int val) {
        if (l == r) {
            seg[id].val = {val};
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            change(ls(id), l, mid, pos, val);
        else
            change(rs(id), mid + 1, r, pos, val);
        update(id);
    }
    info qur(int id, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[id].val;
        int mid = (l + r) >> 1;
        if (qr <= mid)
            return qur(ls(id), l, mid, ql, qr);
        if (ql > mid)
            return qur(rs(id), mid + 1, r, ql, qr);
        return qur(ls(id), l, mid, ql, qr) + qur(rs(id), mid + 1, r, ql, qr);
    }
    void build(const vector<int> &a) {
        init(a.size() - 1);
        assert(n > 0);
        build(1, 1, n, a);
    }
    void change(int pos, int val) {
        assert(1 <= pos && pos <= n);
        change(1, 1, n, pos, val);
    }
    info qur(int l, int r) {
        assert(1 <= l && l <= r && r <= n);
        return qur(1, 1, n, l, r);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    SegTree seg;
    seg.build(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << seg.qur(l, r).mn << (q ? ' ' : '\n');
    }
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
