#include <bits/stdc++.h>
using namespace std;
#define int long long

// KMP字符串匹配：前缀函数失配跳转在线性时间查找全部匹配；数字序列与字符串共用接口。
// O(n+m)时间、O(m+匹配数)空间。
struct KMP {
    vector<int> nxt, pat;
    void init(const vector<int> &a) {
        pat = a;
        int n = a.size();
        nxt.assign(n, 0);
        for (int i = 1, j = 0; i < n; i++) {
            while (j && a[i] != a[j])
                j = nxt[j - 1];
            if (a[i] == a[j])
                j++;
            nxt[i] = j;
        }
    }
    void init(const string &s) {
        init(vector<int>(s.begin(), s.end()));
    }
    vector<int> find(const vector<int> &a) {
        vector<int> ans;
        int m = pat.size();
        if (!m) {
            for (int i = 0; i <= (int)a.size(); i++)
                ans.push_back(i + 1);
            return ans;
        }
        for (int i = 0, j = 0; i < (int)a.size(); i++) {
            while (j && a[i] != pat[j])
                j = nxt[j - 1];
            if (a[i] == pat[j])
                j++;
            if (j == m)
                ans.push_back(i - m + 2), j = nxt[j - 1];
        }
        return ans;
    }
    vector<int> find(const string &s) {
        return find(vector<int>(s.begin(), s.end()));
    }
};

void solve() {
    string s, p;
    cin >> s >> p;
    KMP t;
    t.init(p);
    for (int x : t.find(s))
        cout << x << '\n';
    for (int i = 0; i < (int)p.size(); i++)
        cout << t.nxt[i] << " \n"[i + 1 == (int)p.size()];
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
