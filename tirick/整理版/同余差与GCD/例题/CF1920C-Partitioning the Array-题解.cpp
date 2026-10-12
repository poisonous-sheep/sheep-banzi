// CF1920C https://codeforces.com/problemset/problem/1920/C
#include <bits/stdc++.h>
using namespace std;
#define int long long

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

void init_model() {
}

void solve() {
    int T;
    cin >> T;
    ::init_model();
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x : a)
            cin >> x;
        cout << ::partitions(a) << '\n';
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
