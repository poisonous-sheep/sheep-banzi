#include <bits/stdc++.h>
using namespace std;
#define int long long

// 数位背包：体积拆成奇数*2^b，高位到低位下放剩余容量，用奇数部分总和截断状态。
// O((63+n)*LIM)时间、O(n+LIM)空间；LIM=min(W,Σ奇数部分)。
struct DigitKnapsack {
    static constexpr int INF = 4000000000000000000LL;
    vector<pair<int, int>> a;
    void init() {
        a.clear();
    }
    void add(int w, int v) {
        assert(w > 0);
        a.push_back({w, v});
    }
    int qur(int W) {
        assert(W >= 0);
        vector<vector<pair<int, int>>> item(63);
        int lim = 0;
        for (auto [w, v] : a) {
            int b = __builtin_ctzll((unsigned long long)w);
            int odd = w >> b;
            item[b].push_back({odd, v});
            lim += odd;
        }
        lim = min(lim, W);
        vector<int> f(lim + 1, -INF), g(lim + 1, -INF);
        f[0] = 0;
        for (int b = 62; b >= 0; b--) {
            fill(g.begin(), g.end(), -INF);
            int bit = (W >> b) & 1;
            for (int j = 0; j <= lim; j++)
                if (f[j] > -INF)
                    g[min(lim, 2 * j + bit)] = max(g[min(lim, 2 * j + bit)], f[j]);
            for (auto [w, v] : item[b])
                for (int j = 0; j + w <= lim; j++)
                    if (g[j + w] > -INF)
                        g[j] = max(g[j], g[j + w] + v);
            f.swap(g);
        }
        return *max_element(f.begin(), f.end());
    }
};

void solve() {
    int n, W;
    while (cin >> n >> W && n != -1) {
        DigitKnapsack t;
        while (n--) {
            int w, v;
            cin >> w >> v;
            t.add(w, v);
        }
        cout << t.qur(W) << '\n';
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
