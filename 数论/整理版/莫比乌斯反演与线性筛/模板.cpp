#include <bits/stdc++.h>
using namespace std;
#define int long long

// 莫比乌斯反演与线性筛：线性筛mu与phi；利用互质指示函数和整除分块统计数对；保留原稿模2^32反演接口。
// 筛O(N)时间/空间；coprime O(sqrt(min(a,b)))；invert32 O(N log N)。
struct Mobius {
    int n;
    vector<int> p, pr, mu, smu, phi;
    Mobius(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        p.assign(n + 1, 0);
        mu = smu = phi = p;
        pr.clear();
        if (n)
            mu[1] = phi[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!p[i])
                p[i] = i, pr.push_back(i), mu[i] = -1, phi[i] = i - 1;
            for (int x : pr) {
                if (x > n / i)
                    break;
                p[i * x] = x;
                if (i % x == 0) {
                    phi[i * x] = phi[i] * x;
                    break;
                }
                mu[i * x] = -mu[i];
                phi[i * x] = phi[i] * (x - 1);
            }
        }
        for (int i = 1; i <= n; i++)
            smu[i] = smu[i - 1] + mu[i];
    }
    int coprime(int a, int b) {
        if (a > b)
            swap(a, b);
        assert(a <= n);
        int ans = 0;
        for (int l = 1, r; l <= a; l = r + 1) {
            int x = a / l, y = b / l;
            r = min(a / x, b / y);
            ans += (smu[r] - smu[l - 1]) * x * y;
        }
        return ans;
    }
    vector<uint32_t> invert32(const vector<uint32_t> &f) {
        assert((int)f.size() == n + 1);
        vector<uint32_t> g(n + 1);
        for (int d = 1; d <= n; d++)
            for (int k = 1; k <= n / d; k++)
                g[d * k] += f[d] * (uint32_t)mu[k];
        return g;
    }
};

void solve() {
    int T;
    cin >> T;
    vector<array<int, 3>> q(T);
    int N = 0;
    for (auto &z : q) {
        cin >> z[0] >> z[1] >> z[2];
        N = max(N, min(z[0] / z[2], z[1] / z[2]));
    }
    Mobius t(N);
    for (auto z : q)
        cout << t.coprime(z[0] / z[2], z[1] / z[2]) << '\n';
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
