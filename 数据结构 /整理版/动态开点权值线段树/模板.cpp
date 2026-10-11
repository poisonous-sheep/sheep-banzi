#include <bits/stdc++.h>
using namespace std;
#define int long long

// 动态开点权值线段树：值域可重集合增删、区间次数、第k小/大；支持负值域。
// 操作O(1+log V)，空间O(1+D log V)，删除不回收节点。
struct WeightSegTree {
    struct info {
        int cnt = 0; // 出现次数；所有叶子的次数必须非负
        friend info operator+(const info &l, const info &r) {
            return {l.cnt + r.cnt};
        }
    };
    struct node {
        info val;
        int32_t lc = 0, rc = 0;
    };

    vector<node> seg;
    int root = 0;
    int L, R;

    WeightSegTree(int l = 1, int r = 1000000000) {
        init(l, r);
    }

    void init(int l, int r) {
        assert(l <= r);
        L = l, R = r;
        root = 0;
        seg.clear();
        seg.push_back({}); // seg[0] 表示空节点
    }

    int ls(int id) {
        return seg[id].lc;
    }
    int rs(int id) {
        return seg[id].rc;
    }

    int newnode() {
        assert(seg.size() < (size_t)INT32_MAX);
        seg.push_back({});
        return seg.size() - 1;
    }

    void update(int id) {
        seg[id].val = seg[ls(id)].val + seg[rs(id)].val;
    }

    // 单点修改：v 是 info 增量，{1} 插入，{-1} 删除
    int change(int id, int l, int r, int pos, const info &v) {
        if (!id) {
            assert(v.cnt > 0);
            id = newnode();
        }
        if (l == r) {
            assert((__int128)seg[id].val.cnt + v.cnt >= 0);
            assert((__int128)seg[id].val.cnt + v.cnt <= LLONG_MAX);
            seg[id].val = seg[id].val + v;
            return id;
        }
        int mid = l + ((__int128)r - l) / 2;
        if (pos <= mid) {
            int t = change(ls(id), l, mid, pos, v);
            seg[id].lc = t;
        } else {
            int t = change(rs(id), mid + 1, r, pos, v);
            seg[id].rc = t;
        }
        update(id);
        return id;
    }

    void change(int pos, const info &v) {
        assert(L <= pos && pos <= R && v.cnt != 0);
        assert((__int128)size() + v.cnt >= 0);
        assert((__int128)size() + v.cnt <= LLONG_MAX);
        root = change(root, L, R, pos, v);
    }

    // 查询值域 [ql, qr]，直接返回聚合信息 info
    info qur(int id, int l, int r, int ql, int qr) {
        if (!id || ql > r || qr < l)
            return {};
        if (ql <= l && r <= qr)
            return seg[id].val;
        int mid = l + ((__int128)r - l) / 2;
        return qur(ls(id), l, mid, ql, qr) + qur(rs(id), mid + 1, r, ql, qr);
    }

    info qur(int l, int r) {
        if (l > r)
            return {};
        return qur(root, L, R, l, r);
    }

    info all() {
        return seg[root].val;
    }

    // 线段树上二分：查询第 k 小（k 从 1 开始）
    int kth(int id, int l, int r, int k) {
        if (l == r)
            return l;
        int mid = l + ((__int128)r - l) / 2;
        int cnt = seg[ls(id)].val.cnt;
        if (k <= cnt)
            return kth(ls(id), l, mid, k);
        return kth(rs(id), mid + 1, r, k - cnt);
    }

    int kth(int k) {
        if (k <= 0 || k > seg[root].val.cnt)
            return -1;
        return kth(root, L, R, k);
    }

    int kth_max(int k) {
        if (k <= 0 || k > size())
            return -1;
        return kth(size() - k + 1);
    }

    int size() {
        return seg[root].val.cnt;
    }
};

void solve() {
    int q;
    cin >> q;
    WeightSegTree seg(0, 1000000000);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            seg.change(x, {1});
        } else if (op == 2) {
            int x, c;
            cin >> x >> c;
            int del = min(c, seg.qur(x, x).cnt);
            if (del)
                seg.change(x, {-del}); // 没有该元素时不调用 change(x,{0})
        } else {
            // 原题保证此时非空；重复元素会占据多个排名。
            cout << seg.kth_max(1) - seg.kth(1) << '\n';
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
