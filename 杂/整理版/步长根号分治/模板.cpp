#include <bits/stdc++.h>
using namespace std;
#define int long long

// 步长根号分治：小步长预维护/预处理，大步长暴力跳跃；收录动态模下标和与静态跳跃两个模型。
// 动态修改O(B)、查询O(1)或O(n/B)，空间O(n+B²)；跳跃预处理O(nB)、空间O(nB)，B约sqrt(n)。
struct SqrtDivide {
    int n, B;
    vector<int> a;
    vector<vector<int>> tag;
    vector<vector<int32_t>> jump;
    SqrtDivide(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        B = sqrt(max(1LL, n)) + 1;
        a.assign(n + 1, 0);
        tag.assign(B, {});
        for (int i = 1; i < B; i++)
            tag[i].assign(i, 0);
        jump.clear();
    }
    void change(int x, int v) {
        assert(1 <= x && x <= n);
        a[x] += v;
        for (int k = 1; k < B; k++)
            tag[k][x % k] += v;
    }
    int qur(int k, int r) {
        assert(k > 0 && 0 <= r && r < k);
        if (k < B)
            return tag[k][r];
        int ans = 0;
        for (int i = r ? r : k; i <= n; i += k)
            ans += a[i];
        return ans;
    }
    void build_jump(const vector<int> &v) {
        a = v;
        jump.assign(B, vector<int32_t>(n + 2));
        for (int k = 1; k < B; k++)
            for (int i = n; i >= 1; i--) {
                int j = i + a[i] + k;
                jump[k][i] = 1 + (j <= n ? jump[k][j] : 0);
            }
    }
    int jump_count(int p, int k) {
        if (k < B)
            return jump[k][p];
        int ans = 0;
        while (p <= n)
            ans++, p += a[p] + k;
        return ans;
    }
};

void solve() {
    int q;
    cin >> q;
    SqrtDivide t(500000);
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
            t.change(x, y);
        else
            cout << t.qur(x, y) << '\n';
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
