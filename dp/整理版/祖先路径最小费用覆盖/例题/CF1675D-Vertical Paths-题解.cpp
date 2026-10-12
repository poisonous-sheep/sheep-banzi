// CF1675D https://codeforces.com/problemset/problem/1675/D
#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> fa(n + 1), has_child(n + 1), used(n + 1);
        for (int u = 1; u <= n; u++) {
            cin >> fa[u];
            if (fa[u] != u)
                has_child[fa[u]] = 1;
        }
        vector<vector<int>> paths;
        for (int u = 1; u <= n; u++)
            if (!has_child[u]) {
                vector<int> p;
                int v = u;
                while (!used[v]) {
                    p.push_back(v);
                    used[v] = 1;
                    if (fa[v] == v)
                        break;
                    v = fa[v];
                }
                reverse(p.begin(), p.end());
                paths.push_back(p);
            }
        cout << paths.size() << '\n';
        for (auto &p : paths) {
            cout << p.size() << '\n';
            for (int x : p)
                cout << x << ' ';
            cout << '\n';
        }
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
