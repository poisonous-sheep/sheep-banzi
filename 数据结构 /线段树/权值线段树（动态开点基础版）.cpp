#include <bits/stdc++.h>
using namespace std;
#define int long long

// 动态开点权值线段树：单点加减 / 值域计数 / 第 k 小与第 k 大
// 支持重复元素。插入、删除及区间查询都使用 info；第 k 小/大返回权值。
struct info {
    int cnt = 0;  // 出现次数，插入 +1，删除 -1
};

info operator+(const info& l, const info& r) {
    info res;
    res.cnt = l.cnt + r.cnt;
    return res;
}

struct WeightSegTree {
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
        seg.push_back({});  // seg[0] 表示空节点
    }

    int ls(int id) { return seg[id].lc; }
    int rs(int id) { return seg[id].rc; }

    int newnode() {
        seg.push_back({});
        return seg.size() - 1;
    }

    void update(int id) {
        seg[id].val = seg[ls(id)].val + seg[rs(id)].val;
    }

    // 单点修改：v 是 info 增量，{1} 插入，{-1} 删除
    int change(int id, int l, int r, int pos, const info& v) {
        if (!id) {
            assert(v.cnt > 0);
            id = newnode();
        }
        if (l == r) {
            assert(seg[id].val.cnt + v.cnt >= 0);
            seg[id].val = seg[id].val + v;
            return id;
        }
        int mid = (l + r) >> 1;
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

    void change(int pos, const info& v) {
        assert(L <= pos && pos <= R && v.cnt != 0);
        root = change(root, L, R, pos, v);
    }

    // 查询值域 [ql, qr]，直接返回聚合信息 info
    info qur(int id, int l, int r, int ql, int qr) {
        if (!id || ql > r || qr < l) return {};
        if (ql <= l && r <= qr) return seg[id].val;
        int mid = (l + r) >> 1;
        return qur(ls(id), l, mid, ql, qr)
             + qur(rs(id), mid + 1, r, ql, qr);
    }

    info qur(int l, int r) {
        if (l > r) return {};
        return qur(root, L, R, l, r);
    }

    info all() {
        return seg[root].val;
    }

    // 线段树上二分：查询第 k 小（k 从 1 开始）
    int kth(int id, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int cnt = seg[ls(id)].val.cnt;
        if (k <= cnt) return kth(ls(id), l, mid, k);
        return kth(rs(id), mid + 1, r, k - cnt);
    }

    int kth(int k) {
        if (k <= 0 || k > seg[root].val.cnt) return -1;
        return kth(root, L, R, k);
    }

    int kth_max(int k) {
        return kth(seg[root].val.cnt - k + 1);
    }

    int size() {
        return seg[root].val.cnt;
    }
};

void solve() {
    // 使用示例：值域 [1, 1e9]
    // WeightSegTree seg(1, 1000000000);
    // seg.change(3, {1});    // 插入 3
    // seg.change(5, {1});    // 插入 5
    // seg.change(5, {1});    // 允许重复
    // seg.change(8, {1});    // 插入 8
    // seg.qur(3, 5).cnt;     // 3（查询返回 info）
    // seg.kth(2);           // 5（第 2 小）
    // seg.kth_max(1);       // 8（第 1 大）
    // seg.change(5, {-1});  // 删除一个 5
    // seg.all().cnt;        // 3（整棵树的信息）
    // seg.size();           // 3（集合大小）
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
