#include <bits/stdc++.h>
using namespace std;
#define int long long

// 互质集合与GCD分类计数：统计非空下标子集的gcd；按倍数统计与反演恢复恰好gcd=d的子集权重。
// O(V log V+n)时间、O(V+n)空间，V=max(a)。
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

struct CoprimeSet {
    int n, mod;
    vector<int> cnt, pw, exact;
    Mobius sieve;
    CoprimeSet(const vector<int> &a, int mod_ = 1000000007) {
        init(a, mod_);
    }
    void init(const vector<int> &a, int mod_ = 1000000007) {
        mod = mod_;
        n = a.empty() ? 0 : *max_element(a.begin(), a.end());
        sieve.init(n);
        vector<int> freq(n + 1);
        for (int x : a) {
            assert(x > 0);
            freq[x]++;
        }
        cnt.assign(n + 1, 0);
        for (int d = 1; d <= n; d++)
            for (int j = d; j <= n; j += d)
                cnt[d] += freq[j];
        pw.assign(a.size() + 1, 1);
        for (int i = 1; i < (int)pw.size(); i++)
            pw[i] = pw[i - 1] * 2 % mod;
    }
    int qur() {
        int ans = 0;
        for (int d = 1; d <= n; d++)
            ans = (ans + sieve.mu[d] * (pw[cnt[d]] - 1)) % mod;
        return (ans + mod) % mod;
    }
    int weighted() {
        exact.assign(n + 1, 0);
        int ans = 0;
        for (int d = n; d >= 1; d--) {
            int c = cnt[d];
            exact[d] = c ? c * pw[c - 1] % mod : 0;
            for (int j = d + d; j <= n; j += d)
                exact[d] = (exact[d] - exact[j] + mod) % mod;
            if (d > 1)
                ans = (ans + d * exact[d]) % mod;
        }
        return ans;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    CoprimeSet t(a);
    cout << t.qur() << '\n';
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
