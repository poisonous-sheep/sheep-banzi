#include <bits/stdc++.h>
using namespace std;
#define int long long

// 前缀关系计数：把满足条件的区间转为两个前缀的相同键值，按顺序统计此前相同前缀数。
// n次add期望O(n)时间/O(n)空间；unordered_map最坏可O(n²)。
struct PrefixPairs {
    unordered_map<int, int> cnt;
    int ans = 0;
    void init(int reserve_n = 0) {
        cnt.clear();
        cnt.reserve(reserve_n * 2 + 1);
        ans = 0;
    }
    int add(int key) {
        int old = cnt[key];
        ans += old;
        cnt[key]++;
        return old;
    }
};

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        PrefixPairs t;
        t.init(n + 1);
        t.add(0);
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += s[i - 1] - '0';
            t.add(sum - i);
        }
        cout << t.ans << '\n';
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
