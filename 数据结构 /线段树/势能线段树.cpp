#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define endl '\n'
#define rep(l, r) for (int i = l; i <= r; i++)

const int N = 1e5 + 10;  // 根据题目范围 1 <= n <= 10^5 调整大小

// 线段树节点存区间和与区间最大值
struct info {
    ll sum;
    ll mx;
};

// 两个子节点的合并逻辑：和相加，最大值取最大
info operator+(const info& l, const info& r) {
    info res;
    res.sum = l.sum + r.sum;
    res.mx = max(l.mx, r.mx);
    return res;
}

struct node {
    info val;
} seg[N * 4];

ll a[N];

inline int ls(int x) { return x << 1; }
inline int rs(int x) { return x << 1 | 1; }

void update(int id) { seg[id].val = seg[ls(id)].val + seg[rs(id)].val; }

void build(int id, int l, int r) {
    if (l == r) {
        seg[id].val.sum = a[l];
        seg[id].val.mx = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(id), l, mid);
    build(rs(id), mid + 1, r);
    update(id);
}

// 核心：区间开方操作
// 利用势能分析，只有当区间最大值 > 1 时，才需要继续递归开方
void update_sqrt(int id, int l, int r, int ql, int qr) {
    if (l == r) {
        ll sq = sqrt(seg[id].val.mx);
        seg[id].val.sum = sq;
        seg[id].val.mx = sq;
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid && seg[ls(id)].val.mx > 1) {
        update_sqrt(ls(id), l, mid, ql, qr);
    }
    if (qr > mid && seg[rs(id)].val.mx > 1) {
        update_sqrt(rs(id), mid + 1, r, ql, qr);
    }
    update(id);
}

info qur(int id, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg[id].val;
    int mid = (l + r) >> 1;
    if (qr <= mid) {
        return qur(ls(id), l, mid, ql, qr);
    }
    if (ql > mid) {
        return qur(rs(id), mid + 1, r, ql, qr);
    }
    return qur(ls(id), l, mid, ql, qr) + qur(rs(id), mid + 1, r, ql, qr);
}

void solve() {
    int n;
    cin >> n;
    rep(1, n) cin >> a[i];
    build(1, 1, n);
    int m;
    cin >> m;
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (x > y) swap(x, y); 
        if (op == 0) {
            update_sqrt(1, 1, n, x, y);
        } else {
            cout << qur(1, 1, n, x, y).sum << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
