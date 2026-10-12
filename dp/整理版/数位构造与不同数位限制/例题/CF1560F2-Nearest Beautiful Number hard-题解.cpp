// CF1560F2 https://codeforces.com/contest/1560/problem/F2
#include <bits/stdc++.h>
using namespace std;
#define int long long

string bound, ans;
int k;
array<int, 10> vis{};
bool dfs(int pos, bool larger, int cnt) {
    if (pos == (int)bound.size())
        return true;
    int low = larger ? 0 : bound[pos] - '0';
    if (!pos)
        low = max(1LL, low);
    for (int d = low; d <= 9; d++) {
        int nc = cnt + (vis[d] == 0);
        if (nc > k)
            continue;
        vis[d]++;
        ans.push_back('0' + d);
        if (dfs(pos + 1, larger || d > bound[pos] - '0', nc))
            return true;
        ans.pop_back();
        vis[d]--;
    }
    return false;
}
string at_most(string n, int k_) {
    assert(1 <= k_ && k_ <= 10);
    k = k_;
    bound = n;
    ans.clear();
    vis.fill(0);
    bool ok = dfs(0, false, 0);
    assert(ok);
    return ans;
}
string at_least(string n, int k_) {
    assert(1 <= k_ && k_ <= 10);
    k = k_;
    for (int len = n.size(); len <= max((int)n.size(), k); len++) {
        bound = len == (int)n.size() ? n : "1" + string(len - 1, '0');
        ans.clear();
        vector<vector<array<int32_t, 2>>> memo(
            len + 1, vector<array<int32_t, 2>>(1024, {-1, -1}));
        function<bool(int, int, bool)> can = [&](int pos, int mask,
                                                 bool larger) -> bool {
            if (pos == len)
                return __builtin_popcount((unsigned)mask) >= k;
            auto &res = memo[pos][mask][larger];
            if (res != -1)
                return res != 0;
            int low = larger ? 0 : bound[pos] - '0';
            if (!pos)
                low = max(1LL, low);
            for (int d = low; d <= 9; d++)
                if (can(pos + 1, mask | (1 << d), larger || d > bound[pos] - '0'))
                    return res = 1;
            return res = 0;
        };
        if (!can(0, 0, false))
            continue;
        int mask = 0;
        bool larger = false;
        for (int pos = 0; pos < len; pos++) {
            int low = larger ? 0 : bound[pos] - '0';
            if (!pos)
                low = max(1LL, low);
            for (int d = low; d <= 9; d++)
                if (can(pos + 1, mask | (1 << d), larger || d > bound[pos] - '0')) {
                    ans.push_back('0' + d);
                    mask |= 1 << d;
                    larger |= d > bound[pos] - '0';
                    break;
                }
        }
        return ans;
    }
    return "";
}

void init_model() {
}

void solve() {
    int T;
    cin >> T;
    ::init_model();
    while (T--) {
        string n;
        int k;
        cin >> n >> k;
        cout << ::at_most(n, k) << '\n';
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
