#include <bits/stdc++.h>
using namespace std;
#define int long long

// 珂朵莉树：用 set 保存分段常数区间；区间赋值使区间数减少，支持逐段操作。
// 每次 O(log n+s)，s 为访问区间数；第k小另需 O(s log s)。最坏 O(nq)，空间 O(n)。
struct ODT {
    struct node {
        int l, r;
        mutable int v;
        bool operator<(const node &o) const {
            return l < o.l;
        }
    };
    int n;
    set<node> odt;
    ODT(int n = 0, int v = 0) {
        init(n, v);
    }
    void init(int n_, int v = 0) {
        n = n_;
        odt.clear();
        if (n)
            odt.insert({1, n, v});
    }
    auto split(int x) {
        if (x == n + 1)
            return odt.end();
        assert(1 <= x && x <= n);
        auto it = odt.lower_bound({x, 0, 0});
        if (it != odt.end() && it->l == x)
            return it;
        --it;
        int l = it->l, r = it->r, v = it->v;
        odt.erase(it);
        odt.insert({l, x - 1, v});
        return odt.insert({x, r, v}).first;
    }
    void assign(int l, int r, int v) {
        auto itr = split(r + 1), itl = split(l);
        odt.erase(itl, itr);
        odt.insert({l, r, v});
    }
    void add(int l, int r, int v) {
        auto itr = split(r + 1), itl = split(l);
        for (; itl != itr; ++itl)
            itl->v += v;
    }
    int kth(int l, int r, int k) {
        auto itr = split(r + 1), itl = split(l);
        vector<pair<int, int>> a;
        for (; itl != itr; ++itl)
            a.push_back({itl->v, itl->r - itl->l + 1});
        sort(a.begin(), a.end());
        for (auto [v, c] : a) {
            if (k <= c)
                return v;
            k -= c;
        }
        assert(false);
        return 0;
    }
    int powmod(int a, int b, int p) {
        int r = 1 % p;
        a %= p;
        while (b) {
            if (b & 1)
                r = (__int128)r * a % p;
            a = (__int128)a * a % p;
            b >>= 1;
        }
        return r;
    }
    int qur(int l, int r, int k, int p) {
        auto itr = split(r + 1), itl = split(l);
        int ans = 0;
        for (; itl != itr; ++itl)
            ans = (ans + (__int128)(itl->r - itl->l + 1) * powmod(itl->v, k, p)) % p;
        return ans;
    }
};

void solve() {
    int n, m, seed, vmax;
    cin >> n >> m >> seed >> vmax;
    auto rnd = [&]() {
        int ret = seed;
        seed = (seed * 7 + 13) % 1000000007;
        return ret;
    };
    ODT t(n);
    for (int i = 1; i <= n; i++)
        t.assign(i, i, rnd() % vmax + 1);
    for (int i = 0; i < m; i++) {
        int op = rnd() % 4 + 1, l = rnd() % n + 1, r = rnd() % n + 1;
        if (l > r)
            swap(l, r);
        int x = op == 3 ? rnd() % (r - l + 1) + 1 : rnd() % vmax + 1;
        if (op == 1)
            t.add(l, r, x);
        if (op == 2)
            t.assign(l, r, x);
        if (op == 3)
            cout << t.kth(l, r, x) << '\n';
        if (op == 4) {
            int y = rnd() % vmax + 1;
            cout << t.qur(l, r, x, y) << '\n';
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
