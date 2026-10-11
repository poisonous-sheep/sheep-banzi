#include <bits/stdc++.h>
using namespace std;
#define int long long

// 01Trie：非负整数的动态可重集合与最大异或查询；最高位B<=62。
// 增删/查询O(B)，空间O(D*B)，删除不回收节点。
struct Trie {
    struct node {
        int32_t t[2] = {0, 0};
        int cnt = 0;
    };
    int B;
    vector<node> seg;
    Trie(int b = 32) {
        init(b);
    }
    void init(int b = 32) {
        assert(0 <= b && b <= 62);
        B = b;
        seg.assign(1, {});
    }
    void update(int x) {
        assert(x >= 0);
        int u = 0;
        seg[u].cnt++;
        for (int i = B; i >= 0; i--) {
            int ch = x >> i & 1;
            if (!seg[u].t[ch]) {
                int id = seg.size();
                seg.push_back({});
                seg[u].t[ch] = id;
            }
            u = seg[u].t[ch];
            seg[u].cnt++;
        }
    }
    int count(int x) {
        int u = 0;
        for (int i = B; i >= 0; i--) {
            int ch = x >> i & 1;
            if (!seg[u].t[ch])
                return 0;
            u = seg[u].t[ch];
        }
        return seg[u].cnt;
    }
    bool eras(int x) {
        if (!count(x))
            return false;
        int u = 0;
        seg[u].cnt--;
        for (int i = B; i >= 0; i--) {
            u = seg[u].t[x >> i & 1];
            seg[u].cnt--;
        }
        return true;
    }
    int qur(int x) {
        assert(seg[0].cnt > 0);
        int u = 0, ans = 0;
        for (int i = B; i >= 0; i--) {
            int ch = x >> i & 1, to = ch ^ 1;
            int v = seg[u].t[to];
            if (v && seg[v].cnt) {
                ans |= 1LL << i;
                u = v;
            } else
                u = seg[u].t[ch];
        }
        return ans;
    }
};

void solve() {
    int q;
    cin >> q;
    Trie tr(30);
    tr.update(0);
    while (q--) {
        char op;
        int x;
        cin >> op >> x;
        if (op == '+')
            tr.update(x);
        else if (op == '-')
            tr.eras(x);
        else
            cout << tr.qur(x) << '\n';
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
