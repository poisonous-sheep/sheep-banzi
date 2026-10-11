#include <bits/stdc++.h>
using namespace std;
#define int long long

// 权值线段树合并与分裂：同值域多棵可重集合树；破坏性合并、分裂出最大的k个。
// 插入/排名/分裂O(log V)，合并O(实际同时非空访问节点数)；空间O(累计新建节点)。
struct WeightSegForest {
    struct info {
        int cnt = 0; // 当前值域内的元素个数（包含重复）
    };

    friend info operator+(const info &l, const info &r) {
        return {l.cnt + r.cnt};
    }

    struct node {
        info val;
        int32_t lc = 0, rc = 0; // 动态开点，不能用 id<<1 找儿子
    };

    vector<node> seg = vector<node>(1); // seg[0] 是空节点，cnt = 0

    inline int ls(int id) {
        return seg[id].lc;
    }
    inline int rs(int id) {
        return seg[id].rc;
    }

    int newnode() {
        seg.push_back({});
        return (int)seg.size() - 1;
    }

    void init(int reserve_nodes = 0) { // 多测时重置；reserve_nodes 是预估节点数
        seg.clear();
        if (reserve_nodes > 0)
            seg.reserve(reserve_nodes + 1);
        seg.push_back({});
    }

    void update(int id) {
        seg[id].val = seg[ls(id)].val + seg[rs(id)].val;
    }

    // 单点增减出现次数；pos 在 [l,r]，删除前须保证数量足够
    // 返回可能新建的根，必须接收返回值
    int change(int id, int l, int r, int pos, int v = 1) {
        assert(l <= pos && pos <= r);
        assert(v != 0);
        if (!id) {
            assert(v > 0);
            id = newnode();
        }
        if (l == r) {
            assert(seg[id].val.cnt + v >= 0);
            seg[id].val.cnt += v;
            return id;
        }
        int mid = l + ((__int128)r - l) / 2;
        if (pos <= mid) {
            seg[id].lc = change(ls(id), l, mid, pos, v);
        } else {
            seg[id].rc = change(rs(id), mid + 1, r, pos, v);
        }
        update(id);
        return id;
    }

    // 按值域查询元素个数，允许重数
    int qur(int id, int l, int r, int ql, int qr) {
        if (!id || qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return seg[id].val.cnt;
        int mid = l + ((__int128)r - l) / 2;
        return qur(ls(id), l, mid, ql, qr) + qur(rs(id), mid + 1, r, ql, qr);
    }

    // 查第 k 大（1-indexed），返回值域上的数；要求 1 <= k <= cnt[root]
    int kth(int id, int l, int r, int k) {
        assert(id && 1 <= k && k <= seg[id].val.cnt);
        if (l == r)
            return l;
        int mid = l + ((__int128)r - l) / 2;
        int cnt = seg[rs(id)].val.cnt;
        if (k <= cnt)
            return kth(rs(id), mid + 1, r, k);
        return kth(ls(id), l, mid, k - cnt);
    }

    // 将 y 并入 x。合并是破坏性的，旧的 x/y 不再作为独立的树使用。
    // 必须保证两棵树表示同一值域 [l,r]。
    int merge(int x, int y, int l, int r) {
        if (!x || !y)
            return x + y;
        if (l == r) {
            seg[x].val.cnt += seg[y].val.cnt;
            return x;
        }
        int mid = l + ((__int128)r - l) / 2;
        seg[x].lc = merge(ls(x), ls(y), l, mid);
        seg[x].rc = merge(rs(x), rs(y), mid + 1, r);
        update(x);
        return x;
    }

    // 分裂出最大的 k 个元素，返回 {剩余树的根, 取出树的根}
    // 要求 0 <= k <= cnt[id]；相同值会在叶子按出现次数拆开。
    // 原根 id 在操作后不能再作为“未分裂前的树”使用。
    pair<int, int> split(int id, int l, int r, int k) {
        assert(0 <= k && k <= seg[id].val.cnt);
        if (!id || k == 0)
            return {id, 0};
        if (k == seg[id].val.cnt)
            return {0, id};

        int x = newnode(); // 分裂出来的新树在当前值域的根
        if (l == r) {
            seg[x].val.cnt = k;
            seg[id].val.cnt -= k;
            return {id, x};
        }

        int mid = l + ((__int128)r - l) / 2;
        int cnt = seg[rs(id)].val.cnt;
        if (k <= cnt) {
            // 较大的 k 个全部落在右子树
            auto [a, b] = split(rs(id), mid + 1, r, k);
            seg[id].rc = a;
            seg[x].rc = b;
        } else {
            // 整个右子树取走；剩余 k-cnt 个从左边拿
            seg[x].rc = rs(id);
            seg[id].rc = 0;
            auto [a, b] = split(ls(id), l, mid, k - cnt);
            seg[id].lc = a;
            seg[x].lc = b;
        }
        update(id);
        update(x);
        return {id, x};
    }

    int L, R;
    WeightSegForest(int l = 1, int r = 1000000000) {
        L = l;
        R = r;
        init();
    }
    int change(int root, int pos, int v) {
        return change(root, L, R, pos, v);
    }
    int qur(int root, int l, int r) {
        return l > r ? 0 : qur(root, L, R, l, r);
    }
    int size(int root) {
        return seg[root].val.cnt;
    }
    int kth(int root, int k) {
        return k <= 0 || k > size(root) ? -1 : kth(root, L, R, k);
    }
    int merge(int x, int y) {
        return merge(x, y, L, R);
    }
    pair<int, int> split(int root, int k) {
        return split(root, L, R, k);
    }
};

struct DSU {
    vector<int> fid, sz;
    DSU(int n = 0) {
        init(n);
    }
    void init(int n) {
        fid.resize(n + 1);
        iota(fid.begin(), fid.end(), 0);
        sz.assign(n + 1, 1);
    }
    int root(int x) {
        return fid[x] == x ? x : fid[x] = root(fid[x]);
    }
    bool merge(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y)
            return false;
        if (sz[x] > sz[y])
            swap(x, y);
        fid[x] = y;
        sz[y] += sz[x];
        return true;
    }
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    int size(int x) {
        return sz[root(x)];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    WeightSegForest seg(1, n);
    vector<int> root(m + 2);
    int tot = 1;
    for (int i = 1, c; i <= n; i++) {
        cin >> c;
        if (c)
            root[1] = seg.change(root[1], i, c);
    }
    while (m--) {
        int op, p;
        cin >> op >> p;
        if (op == 0) {
            int x, y;
            cin >> x >> y;
            int c = seg.qur(root[p], 1, x - 1);
            auto [low, high] = seg.split(root[p], seg.size(root[p]) - c);
            int hi = seg.qur(high, y + 1, n);
            auto [mid, upper] = seg.split(high, hi);
            root[p] = seg.merge(low, upper);
            root[++tot] = mid;
        } else if (op == 1) {
            int t;
            cin >> t;
            root[p] = seg.merge(root[p], root[t]);
            root[t] = 0;
        } else if (op == 2) {
            int x, q;
            cin >> x >> q;
            if (x)
                root[p] = seg.change(root[p], q, x);
        } else if (op == 3) {
            int x, y;
            cin >> x >> y;
            cout << seg.qur(root[p], x, y) << '\n';
        } else {
            int k;
            cin >> k;
            if (k <= 0 || k > seg.size(root[p]))
                cout << -1 << '\n';
            else
                cout << seg.kth(root[p], seg.size(root[p]) - k + 1) << '\n';
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
