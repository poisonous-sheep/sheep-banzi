#include <bits/stdc++.h>
using namespace std;
#define int long long

// 树状数组：单点加、前缀和、区间和；非负频率时支持前缀排名二分。
// 初始化O(n)，修改/查询/select为O(log n)，空间O(n)。
template <typename T> struct BIT {
    int n;
    vector<T> a;
    BIT(int n_ = 0) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        a.assign(n + 1, T{});
    }
    void add(int x, const T &v) {
        assert(1 <= x && x <= n);
        for (int i = x; i <= n; i += i & -i)
            a[i] += v;
    }
    T sum(int x) {
        assert(0 <= x && x <= n);
        T ans{};
        for (int i = x; i; i -= i & -i)
            ans += a[i];
        return ans;
    }
    T rangeSum(int l, int r) {
        return l > r ? T{} : sum(r) - sum(l - 1);
    }
    // 非负原数组：返回满足prefix(x)<=k的最大x；k>=0，结果0..n。
    int select(const T &k) {
        assert(k >= T{});
        int x = 0, step = 1;
        T cur{};
        while (step <= n / 2)
            step <<= 1;
        for (; step; step >>= 1)
            if (x + step <= n && cur + a[x + step] <= k) {
                x += step;
                cur += a[x];
            }
        return x;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    BIT<int> bit(n);
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        bit.add(i, x);
    }
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
            bit.add(x, y);
        else
            cout << bit.rangeSum(x, y) << '\n';
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
