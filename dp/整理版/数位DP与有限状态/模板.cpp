#include <bits/stdc++.h>
using namespace std;
#define int long long

// 数位DP与有限状态：把前缀必要信息编码为自动机状态，统一处理tight、前导零和区间前缀差；包含原数数三转移。
// O(L*S*10)时间、O(S)滚动空间；L是位数，S是状态数。
struct DigitDP {
    int S, initial, mod;
    vector<array<int, 10>> go;
    vector<int> accept;
    DigitDP(int S = 1, int mod = 1000000007) {
        init(S, mod);
    }
    void init(int s, int m) {
        S = s;
        mod = m;
        initial = 0;
        go.assign(S, {});
        for (auto &a : go)
            a.fill(-1);
        accept.assign(S, 0);
    }
    int plus(int a, int b) {
        return mod ? (a + b) % mod : a + b;
    }
    int qur(const string &bound) {
        vector<array<int, 2>> dp(S), tmp(S);
        dp[initial][1] = 1;
        for (char c : bound) {
            for (auto &z : tmp)
                z = {0, 0};
            for (int s = 0; s < S; s++)
                for (int tight = 0; tight < 2; tight++)
                    if (dp[s][tight]) {
                        int hi = tight ? c - '0' : 9;
                        for (int d = 0; d <= hi; d++) {
                            int v = go[s][d];
                            if (v < 0)
                                continue;
                            int nt = tight && d == hi;
                            tmp[v][nt] = plus(tmp[v][nt], dp[s][tight]);
                        }
                    }
            dp.swap(tmp);
        }
        int ans = 0;
        for (int s = 0; s < S; s++)
            if (accept[s])
                ans = plus(ans, plus(dp[s][0], dp[s][1]));
        return ans;
    }
    int qur(int x) {
        return x < 0 ? 0 : qur(to_string(x));
    }
    void windy() {
        init(11, 0);
        for (int d = 0; d < 10; d++)
            go[0][d] = d ? d + 1 : 0;
        for (int last = 0; last < 10; last++)
            for (int d = 0; d < 10; d++)
                if (abs(last - d) >= 2)
                    go[last + 1][d] = d + 1;
        for (int s = 1; s <= 10; s++)
            accept[s] = 1;
    }
    void digit_sum(int D, int p) {
        init(D, p);
        for (int s = 0; s < D; s++)
            for (int d = 0; d < 10; d++)
                go[s][d] = (s + d) % D;
        accept[0] = 1;
    }
    // 状态0是尚无有效数位；其余编码(exist,last,inc)，inc=1..3。
    void increasing_three() {
        init(1 + 2 * 10 * 3, 0);
        auto id = [](int e, int last, int inc) {
            return 1 + e * 30 + last * 3 + inc - 1;
        };
        go[0][0] = 0;
        for (int d = 1; d < 10; d++)
            go[0][d] = id(0, d, 1);
        for (int e = 0; e < 2; e++)
            for (int last = 0; last < 10; last++)
                for (int inc = 1; inc <= 3; inc++) {
                    int s = id(e, last, inc);
                    accept[s] = e;
                    for (int d = 0; d < 10; d++) {
                        int k = d > last ? min(3LL, inc + 1) : 1;
                        go[s][d] = id(e || k == 3, d, k);
                    }
                }
    }
};

void solve() {
    int L, R;
    cin >> L >> R;
    DigitDP t;
    t.windy();
    cout << t.qur(R) - t.qur(L - 1) << '\n';
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
