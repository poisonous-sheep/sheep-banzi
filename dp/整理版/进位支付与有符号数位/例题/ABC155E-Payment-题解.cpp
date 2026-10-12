// ABC155E https://atcoder.jp/contests/abc155/tasks/abc155_e
#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> a;
map<pair<int, int>, int> memo;

int digits(string s, int base) {
    int f = 0, g = 1;
    for (char c : s) {
        int d = c - '0';
        int nf = min(f + d, g + base - d), ng = min(f + d + 1, g + base - 1 - d);
        f = nf;
        g = ng;
    }
    return f;
}

void init_model() {
}

void solve() {
    string N;
    cin >> N;
    ::init_model();
    cout << ::digits(N, 10) << '\n';
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
