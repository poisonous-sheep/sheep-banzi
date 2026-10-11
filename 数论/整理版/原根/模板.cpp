#include <bits/stdc++.h>
using namespace std;
#define int long long

// 原根：寻找最小原根并列举全部原根；从原素数版扩展至2、4、p^k、2p^k。
// 试除O(sqrt m)，找根O(G*omega(phi)*log m)，枚举O(phi(m)log phi(m))及排序，空间O(phi(m))。
struct PrimitiveRoot {
    int phi(int n) {
        int ans = n;
        for (int p = 2; p <= n / p; p++)
            if (n % p == 0) {
                ans = ans / p * (p - 1);
                while (n % p == 0)
                    n /= p;
            }
        if (n > 1)
            ans = ans / n * (n - 1);
        return ans;
    }
    int powmod(int a, int b, int m) {
        int ans = 1 % m;
        for (a %= m; b; b >>= 1, a = (__int128)a * a % m)
            if (b & 1)
                ans = (__int128)ans * a % m;
        return ans;
    }
    bool exists(int m) {
        if (m == 2 || m == 4)
            return true;
        if (m < 2)
            return false;
        if (m % 2 == 0)
            m /= 2;
        if (m % 2 == 0)
            return false;
        int p = 0;
        for (int i = 3; i <= m / i; i += 2)
            if (m % i == 0) {
                p = i;
                break;
            }
        if (!p)
            p = m;
        while (m % p == 0)
            m /= p;
        return m == 1;
    }
    int find(int m) {
        if (!exists(m))
            return -1;
        int ph = phi(m), q = ph;
        vector<int> pf;
        for (int p = 2; p <= q / p; p++)
            if (q % p == 0) {
                pf.push_back(p);
                while (q % p == 0)
                    q /= p;
            }
        if (q > 1)
            pf.push_back(q);
        for (int g = 1; g < m; g++) {
            if (gcd(g, m) != 1)
                continue;
            bool ok = true;
            for (int p : pf)
                if (powmod(g, ph / p, m) == 1) {
                    ok = false;
                    break;
                }
            if (ok)
                return g;
        }
        return -1;
    }
    vector<int> all(int m) {
        int g = find(m);
        if (g == -1)
            return {};
        int ph = phi(m), x = 1;
        vector<int> ans;
        for (int k = 1; k <= ph; k++) {
            x = (__int128)x * g % m;
            if (gcd(k, ph) == 1)
                ans.push_back(x);
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

void solve() {
    int T;
    cin >> T;
    PrimitiveRoot p;
    while (T--) {
        int n, d;
        cin >> n >> d;
        auto a = p.all(n);
        cout << a.size() << '\n';
        for (int i = d - 1; i < (int)a.size(); i += d)
            cout << a[i] << ' ';
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
