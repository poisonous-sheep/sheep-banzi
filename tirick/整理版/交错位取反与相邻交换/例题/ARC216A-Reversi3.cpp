#include <bits/stdc++.h>
using namespace std;
#define int long long

// ARC216 A - Reversi 3
// 异或差分 d[i] = a[i] ^ a[i+1]，合法操作等价于 00 <-> 11。
// 把 d 的偶数位置(1-based)取反后，等价于 01 <-> 10 相邻交换。
// 检查首位不变量、1 的数量不变量，按顺序匹配每个 1 的位置。
// 时间 O(n)，空间 O(n)。

void solve() {
    int n;
    string a, b;
    cin >> n >> a >> b;

    if (a[0] != b[0]) {
        cout << -1 << '\n';
        return;
    }

    vector<int> p, q;
    for (int i = 0; i + 1 < n; i++) {
        // i 从 0 开始，i 为奇数对应差分的偶数位置。
        int x = (a[i] != a[i + 1]) ^ (i & 1);
        int y = (b[i] != b[i + 1]) ^ (i & 1);
        if (x) p.push_back(i);
        if (y) q.push_back(i);
    }

    if (p.size() != q.size()) {
        cout << -1 << '\n';
        return;
    }

    int ans = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        ans += abs(p[i] - q[i]);
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
