#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define endl '\n'
#define rep(l, r) for (int i = l; i <= r; i++)

const int N = 2e6 + 10;

// 线段树节点只需要存结果值
struct info {
    ll sum;
};

// 两个子节点的合并逻辑
info operator+(const info &l, const info &r) {
    return {l.sum + r.sum};
}

struct node {
    info val;
} seg[N * 4];

ll a[N];

// 辅助函数：左儿子和右儿子
inline int ls(int x) { return x << 1; }
inline int rs(int x) { return x << 1 | 1; }

// 向上更新节点信息
void update(int id) { 
    seg[id].val = seg[ls(id)].val + seg[rs(id)].val; 
}

// 建树 [l, r]
void build(int id, int l, int r) {
    if (l == r) {
        seg[id].val.sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(id), l, mid);
    build(rs(id), mid + 1, r);
    update(id);
}

// 单点修改：将 a[pos] 修改为 val
void change(int id, int l, int r, int pos, ll val) {
    if (l == r) {
        seg[id].val.sum = val; // 或者使用 += val，取决于你的需求
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        change(ls(id), l, mid, pos, val);
    else
        change(rs(id), mid + 1, r, pos, val);
    update(id); // 修改后必须向上更新
}

// 区间查询：查询 [ql, qr] 的和
ll qur(int id, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return seg[id].val.sum;
    
    int mid = (l + r) >> 1;
    ll res = 0;
    if (ql <= mid) res += qur(ls(id), l, mid, ql, qr);
    if (qr > mid)  res += qur(rs(id), mid + 1, r, ql, qr);
    
    return res;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;
    rep(1, n) cin >> a[i];
    
    build(1, 1, n);
    
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) { // 单点修改
            int pos;
            ll val;
            cin >> pos >> val;
            change(1, 1, n, pos, val);
        } else { // 区间查询
            int x, y;
            cin >> x >> y;
            cout << qur(1, 1, n, x, y) << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
