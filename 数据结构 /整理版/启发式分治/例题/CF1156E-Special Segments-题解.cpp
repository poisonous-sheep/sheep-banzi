// CF1156E https://codeforces.com/contest/1156/problem/E
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
vector<int> a, pre, nxt;
void init(const vector<int> &v) {
    a = v;
    n = a.size() - 1;
    pre.assign(n + 1, 0);
    nxt.assign(n + 1, n + 1);
    map<int, int> last;
    for (int i = 1; i <= n; i++) {
        pre[i] = last[a[i]];
        if (pre[i])
            nxt[pre[i]] = i;
        last[a[i]] = i;
    }
}
bool dfs(int l, int r) {
    if (l > r)
        return true;
    for (int x = l, y = r; x <= y; x++, y--) {
        if (pre[x] < l && nxt[x] > r)
            return dfs(l, x - 1) && dfs(x + 1, r);
        if (pre[y] < l && nxt[y] > r)
            return dfs(l, y - 1) && dfs(y + 1, r);
    }
    return false;
}
bool non_boring() {
    return dfs(1, n);
}
int maximum_pairs() {
    vector<int> pos(n + 1), lg(n + 1);
    for (int i = 1; i <= n; i++) {
        assert(1 <= a[i] && a[i] <= n && !pos[a[i]]);
        pos[a[i]] = i;
    }
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;
    vector<vector<int32_t>> st(lg[n] + 1, vector<int32_t>(n + 1));
    for (int i = 1; i <= n; i++)
        st[0][i] = i;
    auto better = [&](int i, int j) { return a[i] > a[j] ? i : j; };
    for (int k = 1; k < (int)st.size(); k++)
        for (int i = 1; i + (1 << k) - 1 <= n; i++)
            st[k][i] = better(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    auto argmax = [&](int l, int r) {
        int k = lg[r - l + 1];
        return better(st[k][l], st[k][r - (1 << k) + 1]);
    };
    function<int(int, int)> work = [&](int l, int r) {
        if (l >= r)
            return 0LL;
        int m = argmax(l, r), ans = work(l, m - 1) + work(m + 1, r);
        if (m - l < r - m) {
            for (int i = l; i < m; i++) {
                int x = a[m] - a[i];
                if (x > 0 && pos[x] > m && pos[x] <= r)
                    ans++;
            }
        } else
            for (int j = m + 1; j <= r; j++) {
                int x = a[m] - a[j];
                if (x > 0 && pos[x] >= l && pos[x] < m)
                    ans++;
            }
        return ans;
    };
    return work(1, n);
}

void init_model() {
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    ::init_model();
    ::init(a);
    cout << ::maximum_pairs() << '\n';
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
