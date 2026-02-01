#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define endl '\n'
#define rep(l, r) for (int i = l; i <= r; i++)

const int N = 2e6 + 10;

// 线段树节点只需要存结果值
struct info {
    ll mn;
};

// 两个子节点的合并逻辑
info operator+(const info& l, const info& r) {
    info res;
    res.mn = min(l.mn, r.mn);
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
        seg[id].val.mn = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(id), l, mid);
    build(rs(id), mid + 1, r);
    update(id);
}

void change(int id, int l, int r, int pos, ll val) {
    if (l == r) {
        seg[id].val.mn = val;  
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
    int n, m;
    cin >> n >> m;
    rep(1, n) cin >> a[i];
    build(1, 1, n);
    while (m--) {
        int x, y;
        cin >> x >> y;
        x++;            
        if (x > y) swap(x, y); 
        cout << qur(1, 1, n, x, y).mn << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
