// UVA10003 https://onlinejudge.org/external/100/10003.pdf
#include <bits/stdc++.h>
using namespace std;
#define int long long

struct info {
    int l, r, w;
};
static constexpr int INF = 4000000000000000000LL;
int n, mode;
vector<int> x;
vector<info> a;
vector<vector<int>> dp;
void init_enemies(vector<info> p) {
    mode = 0;
    a = p;
    x.clear();
    for (auto z : a) {
        x.push_back(z.l);
        x.push_back(z.r);
    }
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    n = x.size();
    for (auto &z : a) {
        z.l = lower_bound(x.begin(), x.end(), z.l) - x.begin();
        z.r = lower_bound(x.begin(), x.end(), z.r) - x.begin();
    }
    dp.assign(n, vector<int>(n, -1));
}
void init_cuts(int length, vector<int> cuts) {
    mode = 1;
    x = cuts;
    sort(x.begin(), x.end());
    assert(adjacent_find(x.begin(), x.end()) == x.end());
    x.insert(x.begin(), 0);
    x.push_back(length);
    n = cuts.size();
    dp.assign(n, vector<int>(n, -1));
}
int dfs(int l, int r) {
    if (l > r)
        return 0;
    int &ans = dp[l][r];
    if (ans != -1)
        return ans;
    int L = l, R = r, cost = 0;
    if (mode == 0) {
        int pos = -1;
        for (int i = 0; i < (int)a.size(); i++)
            if (a[i].l >= l && a[i].r <= r && (pos == -1 || a[i].w > a[pos].w))
                pos = i;
        if (pos == -1)
            return ans = 0;
        L = a[pos].l;
        R = a[pos].r;
        cost = a[pos].w;
    } else
        cost = x[r + 2] - x[l];
    ans = INF;
    for (int k = L; k <= R; k++)
        ans = min(ans, dfs(l, k - 1) + dfs(k + 1, r) + cost);
    return ans;
}
int run() {
    return n ? dfs(0, n - 1) : 0;
}

void init_model() {
}

void solve() {
    int length;
    while (cin >> length && length) {
        int q;
        cin >> q;
        vector<int> cuts(q);
        for (int &x : cuts)
            cin >> x;
        ::init_model();
        ::init_cuts(length, cuts);
        cout << "The minimum cutting is " << ::run() << ".\n";
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
