#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define endl '\n'
#define rep(l, r) for (int i = l; i <= r; i++)

const int N = 2e6 + 10;
const int LOG = 21;  // 要求 1 <= n < N，且 2^LOG > n。

// 静态区间最小值、最大值；数组下标从 1 开始。
// mn/mx 用 int32_t，兼容 #define int long long；a[i] 必须在 int32_t 范围内。
// 若值域需要 long long，请把 mn/mx 改为 ll，并去掉 build 中的 int32_t 转换。
struct info {
    int32_t mn;
    int32_t mx;
};

// 合并逻辑不变
info operator+(const info& l, const info& r) {
    info res;
    res.mn = min(l.mn, r.mn);
    res.mx = max(l.mx, r.mx);
    return res;
}

int a[N];
int lg[N];
// st[j][i] 表示区间 [i, i + 2^j - 1] 的信息。
info st[LOG][N];

// 建 ST 表：O(n log n)。读入 a[1..n] 后调用 build(n)。
void build(int n) {
    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i / 2] + 1;
    }

    for (int i = 1; i <= n; i++) {
        st[0][i] = {(int32_t)a[i], (int32_t)a[i]};
    }

    for (int j = 1; j <= lg[n]; j++) {
        for (int i = 1; i + (1LL << j) - 1 <= n; i++) {
            st[j][i] = st[j - 1][i] + st[j - 1][i + (1LL << (j - 1))];
        }
    }
}

// 查询闭区间 [l, r]：O(1)，要求 1 <= l <= r <= n。
// 两段可能重叠，min/max 重复合并不影响结果；不能直接用于区间求和。
// 原数组修改后，需要重新 build。
info qur(int l, int r) {
    int k = lg[r - l + 1];
    return st[k][l] + st[k][r - (1LL << k) + 1];
}

// 使用示例：输入 n、q，数组，以及 q 个查询 [l, r]；输出最小值和最大值。
// N = 2e6 + 10、LOG = 21 时，st 约占 320.4 MiB；按题目规模调整 N。
void solve() {
    int n, q;
    cin >> n >> q;
    rep(1, n) cin >> a[i];
    build(n);
    while (q--) {
        int l, r;
        cin >> l >> r;
        info res = qur(l, r);
        cout << res.mn << ' ' << res.mx << endl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
