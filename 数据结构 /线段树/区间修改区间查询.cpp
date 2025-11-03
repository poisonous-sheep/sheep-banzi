#include <bits/stdc++.h>
#include <vector>

#define ld long double
#define ll long long
#define lowbit(x) x & -x

using namespace std;

const int N = 2e6 + 10;
const ll mod = 1e9 + 7;
const ll INF = 1e18;

#define endl '\n'
#define rep(l, r) for (int i = l; i <= r; i++)
#define lep(r, l) for (int i = r; i >= l; i--)

using pii = pair<int, int>;
using pll = pair<ll, ll>;
using i64 = int64_t;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

inline ll qpow(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

#define ok cout << "YES\n"
#define no cout << "NO\n"

ll ls(ll x) { return x << 1; }
ll rs(ll x) { return x << 1 | 1; }

struct info {
  ll sum;
  ll len;
}; // 线段树里面要存什么

struct tag {
  ll add;
}; // 区间修改什么

info operator+(const info &l, const info &r) {
  info a;
  a.sum = l.sum + r.sum;
  a.len = l.len + r.len;
  return a;
};

info operator+(const info &v, const tag &t) {
  info a;
  a.len = v.len;
  a.sum = v.sum + t.add * v.len;
  return a;
};

tag operator+(const tag &t1, const tag &t2) { return {t1.add + t2.add}; };

struct node {
  tag t;
  info val;
} seg[N * 4];

ll a[N];

void update(int id) { seg[id].val = seg[rs(id)].val + seg[ls(id)].val; }

void settag(int id, tag t) {
  seg[id].val = seg[id].val + t;
  seg[id].t = seg[id].t + t;
}

void pushdown(int id) {
  if (seg[id].t.add != 0) { // 标记非空
    settag(ls(id), seg[id].t);
    settag(rs(id), seg[id].t);
    seg[id].t.add = 0;
  }
}

//[l,r]
void build(int id, int l, int r) {
  seg[id].t.add = 0;
  if (l == r) {
    seg[id].val.sum = a[l];
    seg[id].val.len = 1;
  } else {
    int mid = (l + r) >> 1;
    build(ls(id), l, mid);
    build(rs(id), mid + 1, r);
    update(id);
  }
}



// 节点编号为id，区间为[l,r] a[pos]->val
void change(int id, int l, int r, int pos, int val) {
  if (l == r) {
    seg[id].val.sum = val;
  } else {
    int mid = (l + r) >> 1;
    pushdown(id);
    if (pos <= mid)
      change(ls(id), l, mid, pos, val);
    else
      change(rs(id), mid + 1, r, pos, val);
    // very important
    update(id);
  }
}

void modify(int id, int l, int r, int ql, int qr, tag t) {
  if (l == ql && r == qr) {
    settag(id, t);
    return;
  }
  int mid = (l + r) >> 1;
  // ！！！重要
  pushdown(id);
  if (qr <= mid)
    modify(ls(id), l, mid, ql, qr, t);
  else if (ql > mid)
    modify(rs(id), mid + 1, r, ql, qr, t);
  else {
    modify(ls(id), l, mid, ql, mid, t);
    modify(rs(id), mid + 1, r, mid + 1, qr, t);
  }
  update(id);
}
//[ql,qr] 查询区间
ll qur(int id, int l, int r, int ql, int qr) {
  if (l == ql && r == qr)
    return seg[id].val.sum;
  int mid = (l + r) >> 1;
  // ！！！重要
  pushdown(id);
  if (qr <= mid)
    return qur(ls(id), l, mid, ql, qr);
  else if (ql > mid)
    return qur(rs(id), mid + 1, r, ql, qr);
  else
    return qur(ls(id), l, mid, ql, mid) + qur(rs(id), mid + 1, r, mid + 1, qr);
}

void solve() {
  int n, m;
  cin >> n >> m;
  rep(1, n) cin >> a[i];
  build(1, 1, n);
  while (m--) {
    int op;
    cin >> op;
    if (op == 1) {
      ll x, y, k;
      cin >> x >> y >> k;
      tag t = {k};
      modify(1, 1, n, x, y, t);
    } else {
      ll x, y;
      cin >> x >> y;
      cout << qur(1, 1, n, x, y) << endl;
    }
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  // cin >> t;
  while (t--)
    solve();
  return 0;
}
