#include <bits/stdc++.h>
using namespace std;
#define int long long

// 区间加线段树：闭区间加、区间和、单点赋值；1-based。
// 建树O(n)，修改/查询O(log n)，空间O(n)。
struct SegTree {
    struct info {
        int sum = 0, len = 0;

        friend info operator+(const info &l, const info &r) {
            return {l.sum + r.sum, l.len + r.len};
        }
    };

    struct tag {
        int add = 0;
    };

    struct node {
        info val;
        tag t;
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

    void settag(int id, tag t) {
        seg[id].val.sum += t.add * seg[id].val.len;
        seg[id].t.add += t.add;
    }

    void pushdown(int id) {
        if (seg[id].t.add) {
            settag(ls(id), seg[id].t);
            settag(rs(id), seg[id].t);
            seg[id].t.add = 0;
        }
    }

    void build(int id, int l, int r, const vector<int> &a) {
        if (l == r) {
            seg[id].val = {a[l], 1};
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(id), l, mid, a);
        build(rs(id), mid + 1, r, a);
        update(id);
    }

    void modify(int id, int l, int r, int ql, int qr, tag t) {
        if (ql <= l && r <= qr) {
            settag(id, t);
            return;
        }
        pushdown(id);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            modify(ls(id), l, mid, ql, qr, t);
        if (qr > mid)
            modify(rs(id), mid + 1, r, ql, qr, t);
        update(id);
    }

    // 区间查询：返回 info
    info qur(int id, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return seg[id].val;

        pushdown(id);
        int mid = (l + r) >> 1;
        info ans = {};

        if (ql <= mid)
            ans = ans + qur(ls(id), l, mid, ql, qr);
        if (qr > mid)
            ans = ans + qur(rs(id), mid + 1, r, ql, qr);

        return ans;
    }

    void change(int id, int l, int r, int pos, int val) {
        if (l == r) {
            seg[id].val.sum = val;
            seg[id].t = {};
            return;
        }
        pushdown(id);
        int mid = (l + r) >> 1;
        if (pos <= mid)
            change(ls(id), l, mid, pos, val);
        else
            change(rs(id), mid + 1, r, pos, val);
        update(id);
    }

    void build(const vector<int> &a) {
        init(a.size() - 1);
        assert(n > 0);
        build(1, 1, n, a);
    }

    void modify(int l, int r, tag t) {
        assert(1 <= l && l <= r && r <= n);
        modify(1, 1, n, l, r, t);
    }

    void change(int pos, int val) {
        assert(1 <= pos && pos <= n);
        change(1, 1, n, pos, val);
    }

    // 对外查询接口也返回 info
    info qur(int l, int r) {
        if (l > r)
            return {};
        assert(1 <= l && r <= n);
        return qur(1, 1, n, l, r);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    SegTree seg;
    seg.build(a);

    while (m--) {
        int op, l, r, k;
        cin >> op >> l >> r;

        if (op == 1) {
            cin >> k;
            seg.modify(l, r, {k});
        } else {
            cout << seg.qur(l, r).sum << '\n';
        }
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
