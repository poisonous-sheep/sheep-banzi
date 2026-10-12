// QOJ12409 https://qoj.ac/problem/12409
#include <bits/stdc++.h>
using namespace std;
#define int long long

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
        return half + (len % 2 &&
                       (__builtin_popcountll((unsigned long long)L) & 1) == s[0] - '0');
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

void init_model() {
}

void solve() {
    int T;
    cin >> T;
    ::init_model();
    while (T--) {
        int m, L;
        cin >> m >> L;
        string s;
        while (m--) {
            int x;
            cin >> x;
            s.push_back('0' + x);
        }
        ::init();
        cout << ::calc(L, s) << '\n';
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
