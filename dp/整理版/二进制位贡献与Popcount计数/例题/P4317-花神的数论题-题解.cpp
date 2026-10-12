// P4317 https://www.luogu.com.cn/problem/P4317
#include <bits/stdc++.h>
using namespace std;
#define int long long

int mod;

vector<int> distribution(int n) {
    string s;
    do {
        s.push_back('0' + (n & 1));
        n >>= 1;
    } while (n);
    reverse(s.begin(), s.end());
    int L = s.size();
    vector<vector<int>> C(L + 1, vector<int>(L + 1));
    C[0][0] = 1;
    for (int i = 1; i <= L; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    vector<int> ans(L + 1);
    int ones = 0;
    for (int i = 0; i < L; i++)
        if (s[i] == '1') {
            for (int k = 0; k <= L - i - 1; k++)
                ans[ones + k] += C[L - i - 1][k];
            ones++;
        }
    ans[ones]++;
    return ans;
}
int powmod(int a, int b) {
    int r = 1;
    while (b) {
        if (b & 1)
            r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return r;
}

void init_model(int mod_ = 1000000007) {
    mod = mod_;
}

void solve() {
    int N;
    cin >> N;
    ::init_model(10000007);
    auto cnt = ::distribution(N);
    int ans = 1;
    for (int k = 1; k < (int)cnt.size(); k++)
        ans = (__int128)ans * ::powmod(k, cnt[k]) % ::mod;
    cout << ans << '\n';
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
