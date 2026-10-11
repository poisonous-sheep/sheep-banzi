#include <bits/stdc++.h>
using namespace std;
#define int long long

// 同余差与GCD：所有数同余模m当且仅当m整除全部差；最大可行模或步长来自差值GCD。
// stride/from O(n log A)时间/O(1)额外空间；partitions O(n*tau(n)*log A)时间。
struct GcdDifference {
    int stride(const vector<int> &a, int k) {
        int g = 0;
        for (int i = k; i < (int)a.size(); i++)
            g = std::gcd(g, llabs(a[i] - a[i - k]));
        return g;
    }
    int partitions(const vector<int> &a) {
        int n = a.size(), ans = 0;
        for (int k = 1; k <= n; k++)
            if (n % k == 0 && stride(a, k) != 1)
                ans++;
        return ans;
    }
    int from(const vector<int> &a, int x) {
        int g = 0;
        for (int y : a)
            g = std::gcd(g, llabs(y - x));
        return g;
    }
};

void solve() {
    int T;
    cin >> T;
    GcdDifference t;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x : a)
            cin >> x;
        cout << t.partitions(a) << '\n';
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
