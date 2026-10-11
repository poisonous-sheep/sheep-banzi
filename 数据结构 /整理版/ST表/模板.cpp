#include <bits/stdc++.h>
using namespace std;
#define int long long

// ST表：静态区间最小值与最大值；重叠两段要求合并幂等。
// 建表O(n log n)，查询O(1)，空间O(n log n)。
struct ST {
    struct info {
        int mn, mx;
        friend info operator+(const info &l, const info &r) {
            return {min(l.mn, r.mn), max(l.mx, r.mx)};
        }
    };
    int n = 0;
    vector<int> lg;
    vector<vector<info>> st;
    void build(const vector<int> &a) {
        n = a.size() - 1;
        assert(n > 0);
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        st.assign(lg[n] + 1, vector<info>(n + 1));
        for (int i = 1; i <= n; i++)
            st[0][i] = {a[i], a[i]};
        for (int j = 1; j <= lg[n]; j++)
            for (int i = 1; i + (1LL << j) - 1 <= n; i++)
                st[j][i] = st[j - 1][i] + st[j - 1][i + (1LL << (j - 1))];
    }
    info qur(int l, int r) {
        assert(1 <= l && l <= r && r <= n);
        int k = lg[r - l + 1];
        return st[k][l] + st[k][r - (1LL << k) + 1];
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    ST st;
    st.build(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.qur(l, r).mx << '\n';
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
