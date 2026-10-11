#include <bits/stdc++.h>
using namespace std;
#define int long long

// 进位支付与有符号数位：每位选择直接支付或向更高币值进位并找零；二进制base=2就是原资料最少±2^k。
// 幂倍币制O(n)个实际金额状态、map查找O(log n)；固定进制O(L)时间/O(1)空间。
struct CarryDP {
    vector<int> a;
    map<pair<int, int>, int> memo;
    int dfs(int i, int x) {
        if (i + 1 == (int)a.size())
            return x;
        auto key = make_pair(i, x);
        if (memo.count(key))
            return memo[key];
        int base = a[i + 1] / a[i], r = x % base, q = x / base;
        int ans = r + dfs(i + 1, q);
        if (r)
            ans = min(ans, base - r + dfs(i + 1, q + 1));
        return memo[key] = ans;
    }
    int qur(const vector<int> &coins, int x) {
        a = coins;
        assert(!a.empty() && a[0] == 1);
        for (int i = 1; i < (int)a.size(); i++)
            assert(a[i] > a[i - 1] && a[i] % a[i - 1] == 0);
        memo.clear();
        return dfs(0, x);
    }
    int digits(string s, int base) {
        int f = 0, g = 1;
        for (char c : s) {
            int d = c - '0';
            int nf = min(f + d, g + base - d), ng = min(f + d + 1, g + base - 1 - d);
            f = nf;
            g = ng;
        }
        return f;
    }
};

void solve() {
    int n, X;
    cin >> n >> X;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    CarryDP t;
    cout << t.qur(a, X) << '\n';
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
