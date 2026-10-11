#include <bits/stdc++.h>
using namespace std;
#define int long long

// 动态开点权值线段树：单点加减 / 值域计数 / 第 k 小与第 k 大
// 支持重复元素。维护的是数值出现次数，而不是数组下标。
struct WeightSegTree {
    struct info {
        int cnt = 0;
    };

    friend info operator+(const info& l, const info& r) {
        return {l.cnt + r.cnt};
    }

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

    // 单点修改：v=1 插入，v=-1 删除；删除前需确保元素存在
    int change(int id, int l, int r, int pos, int v) {
        if (!id) {
            assert(v > 0);
            id = newnode();
        }
        if (l == r) {
            assert(seg[id].val.cnt + v >= 0);
            seg[id].val.cnt += v;
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

    void change(int pos, int v = 1) {
        assert(L <= pos && pos <= R && v != 0);
        root = change(root, L, R, pos, v);
    }

    // 查询值域 [ql, qr] 中元素的个数（包括重复）
    int qur(int id, int l, int r, int ql, int qr) {
        if (!id || ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return seg[id].val.cnt;
        int mid = (l + r) >> 1;
        return qur(ls(id), l, mid, ql, qr)
             + qur(rs(id), mid + 1, r, ql, qr);
    }

    int qur(int l, int r) {
        if (l > r) return 0;
        return qur(root, L, R, l, r);
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
    // seg.change(3);       // 插入 3
    // seg.change(5);       // 插入 5
    // seg.change(5);       // 允许重复
    // seg.change(8);       // 插入 8
    // seg.qur(3, 5);       // 3（值域内的元素个数）
    // seg.kth(2);          // 5（第 2 小）
    // seg.kth_max(1);      // 8（第 1 大）
    // seg.change(5, -1);   // 删除一个 5
    // seg.size();          // 3（集合大小）
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
