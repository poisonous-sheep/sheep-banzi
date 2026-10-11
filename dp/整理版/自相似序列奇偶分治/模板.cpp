#include <bits/stdc++.h>
using namespace std;
#define int long long

// 自相似序列奇偶分治：利用f(2x)、f(2x+1)与f(x)的关系缩小下标；包含Thue-Morse模式计数与三字符替换查询变体。
// calc的上界与模式不断折半，记忆化状态约O(log² L)，每状态O(m)；transform O(min(t,log k))时间/栈空间。
struct SelfSimilar {
    map<pair<int, string>, int> memo;
    void init() {
        memo.clear();
    }
    int calc(int L, const string &s) {
        if (L < 0)
            return 0;
        if (s.empty())
            return L + 1;
        if (L == 0) {
            for (int i = 0; i < (int)s.size(); i++)
                if ((__builtin_popcountll((unsigned long long)i) & 1) != s[i] - '0')
                    return 0;
            return 1;
        }
        if (s.size() == 1) {
            int len = L + 1, half = len / 2;
            return half + (len % 2 && (__builtin_popcountll((unsigned long long)L) &
                                       1) == s[0] - '0');
        }
        auto key = make_pair(L, s);
        if (memo.count(key))
            return memo[key];
        int n = s.size(), res = 0;
        bool ok = true;
        for (int i = 0; i + 1 < n; i += 2)
            if (s[i] == s[i + 1])
                ok = false;
        if (ok) {
            string t;
            for (int i = 0; i < n; i += 2)
                t.push_back(s[i]);
            res += calc(L / 2, t);
        }
        ok = true;
        for (int i = 1; i + 1 < n; i += 2)
            if (s[i] == s[i + 1])
                ok = false;
        if (ok && L >= 1) {
            string t;
            t.push_back(s[0] == '0' ? '1' : '0');
            for (int i = 1; i < n; i += 2)
                t.push_back(s[i]);
            res += calc((L - 1) / 2, t);
        }
        return memo[key] = res;
    }
    int transform(const string &s, int t, int k) {
        if (t == 0)
            return s[k] - 'A';
        if (k == 0)
            return (s[0] - 'A' + t % 3) % 3;
        return (transform(s, t - 1, k / 2) + 1 + k % 2) % 3;
    }
};

void solve() {
    int T;
    cin >> T;
    SelfSimilar t;
    while (T--) {
        int m, L;
        cin >> m >> L;
        string s;
        while (m--) {
            int x;
            cin >> x;
            s.push_back('0' + x);
        }
        t.init();
        cout << t.calc(L, s) << '\n';
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
