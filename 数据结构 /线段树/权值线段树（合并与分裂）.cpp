#include <bits/stdc++.h>
using namespace std;

#define int long long

// 权值线段树（动态开点 + 线段树合并 + 按排名分裂）
// 每棵树维护值域 [L, R] 内的一个可重集合，支持重复元素。
// 节点 0 表示空树；每棵树用一个 root 保存根编号。
// 用法：root = change(root, L, R, pos, +/-1);
//       root = merge(root, other, L, R); other = 0;
//       auto [remain, taken] = split(root, L, R, k); // 取最大的 k 个
//       x = kth(root, L, R, k);                    // 第 k 大
//       c = qur(root, L, R, ql, qr);              // 值域计数

struct info {
    int cnt = 0; // 当前值域内的元素个数（包含重复）
};

info operator+(const info& l, const info& r) {
    return {l.cnt + r.cnt};
}

struct node {
    info val;
    int32_t lc = 0, rc = 0; // 动态开点，不能用 id<<1 找儿子
};

vector<node> seg(1); // seg[0] 是空节点，cnt = 0

inline int ls(int id) { return seg[id].lc; }
inline int rs(int id) { return seg[id].rc; }

int newnode() {
    seg.push_back({});
    return (int)seg.size() - 1;
}

void init(int reserve_nodes = 0) { // 多测时重置；reserve_nodes 是预估节点数
    seg.clear();
    if (reserve_nodes > 0) seg.reserve(reserve_nodes + 1);
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
    int mid = (l + r) >> 1;
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
    if (!id || qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return seg[id].val.cnt;
    int mid = (l + r) >> 1;
    return qur(ls(id), l, mid, ql, qr) +
           qur(rs(id), mid + 1, r, ql, qr);
}

// 查第 k 大（1-indexed），返回值域上的数；要求 1 <= k <= cnt[root]
int kth(int id, int l, int r, int k) {
    assert(id && 1 <= k && k <= seg[id].val.cnt);
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int cnt = seg[rs(id)].val.cnt;
    if (k <= cnt) return kth(rs(id), mid + 1, r, k);
    return kth(ls(id), l, mid, k - cnt);
}

// 将 y 并入 x。合并是破坏性的，旧的 x/y 不再作为独立的树使用。
// 必须保证两棵树表示同一值域 [l,r]。
int merge(int x, int y, int l, int r) {
    if (!x || !y) return x + y;
    if (l == r) {
        seg[x].val.cnt += seg[y].val.cnt;
        return x;
    }
    int mid = (l + r) >> 1;
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
    if (!id || k == 0) return {id, 0};
    if (k == seg[id].val.cnt) return {0, id};

    int x = newnode(); // 分裂出来的新树在当前值域的根
    if (l == r) {
        seg[x].val.cnt = k;
        seg[id].val.cnt -= k;
        return {id, x};
    }

    int mid = (l + r) >> 1;
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

void solve() {
    // 示例（值域 [0,4]）：
    // int root1 = 0, root2 = 0;
    // root1 = change(root1, 0, 4, 4); // [4]
    // root1 = change(root1, 0, 4, 2); // [4,2]
    // root2 = change(root2, 0, 4, 2); // [2]
    // root1 = merge(root1, root2, 0, 4);
    // root2 = 0;                      // [4,2,2]
    // auto [a, b] = split(root1, 0, 4, 2);
    // root1 = a;                      // [2]
    // int take = b;                   // [4,2]
    // cout << kth(take, 0, 4, 1) << '\n'; // 4
    // cout << qur(take, 0, 4, 2, 4) << '\n'; // 2
    // 在 Phony 中：值域是离散化后的余数下标，
    // 每个商对应一个 root，取出的树再 merge 到较低商的 root 中。
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
