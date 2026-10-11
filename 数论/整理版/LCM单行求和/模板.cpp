#include <bits/stdc++.h>
using namespace std;
#define int long long

// LCM单行求和：求Σ(1<=i<=n)lcm(i,n)=n*(1+Σ(d|n)d*phi(d))/2。保留课堂按约数累加思路。
// 批量init O(N log N)、O(N)空间；单点calc试除O(sqrt n)、O(log n)空间。
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

struct LCMSumRow {
    vector<int> f;
    void init(int n) {
        Mobius t(n);
        f.assign(n + 1, 0);
        for (int d = 1; d <= n; d++)
            for (int j = d; j <= n; j += d)
                f[j] += d * t.phi[d];
    }
    __int128 qur(int n) {
        assert(1 <= n && n < (int)f.size());
        return (__int128)n * (f[n] + 1) / 2;
    }
    __int128 calc(int n) {
        vector<pair<int, int>> fac;
        int x = n;
        for (int p = 2; p <= x / p; p++)
            if (x % p == 0) {
                int e = 0;
                while (x % p == 0)
                    x /= p, e++;
                fac.push_back({p, e});
            }
        if (x > 1)
            fac.push_back({x, 1});
        __int128 s = 1;
        for (auto [p, e] : fac) {
            __int128 z = 1, pow = 1;
            for (int k = 1; k <= e; k++) {
                pow *= p;
                z += pow * (pow - pow / p);
            }
            s *= z;
        }
        return (__int128)n * (s + 1) / 2;
    }
};
void print128(__int128 x) {
    if (!x) {
        cout << 0;
        return;
    }
    string s;
    while (x)
        s.push_back('0' + x % 10), x /= 10;
    reverse(s.begin(), s.end());
    cout << s;
}

void solve() {
    int T;
    cin >> T;
    vector<int> a(T);
    for (int &x : a)
        cin >> x;
    LCMSumRow t;
    t.init(*max_element(a.begin(), a.end()));
    for (int x : a) {
        print128(t.qur(x));
        cout << '\n';
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
