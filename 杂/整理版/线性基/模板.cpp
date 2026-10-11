#include <bits/stdc++.h>
using namespace std;
#define int long long

// 线性基：GF(2)消元维护可达异或空间，支持最大值、可表示判定、第k小及最大权线性无关集。
// insert/exist/qur O(B)，kth O(B²)，空间O(B)，B=63。
struct LinearBasis {
    static const int B = 62;
    array<int, B + 1> p{};
    bool zero = false;
    void init() {
        p.fill(0);
        zero = false;
    }
    bool insert(int x) {
        assert(x >= 0);
        for (int i = B; i >= 0; i--)
            if ((x >> i) & 1) {
                if (!p[i]) {
                    p[i] = x;
                    return true;
                }
                x ^= p[i];
            }
        zero = true;
        return false;
    }
    bool exist(int x) {
        for (int i = B; i >= 0; i--)
            if ((x >> i) & 1)
                x ^= p[i];
        return x == 0;
    }
    int qur(int x = 0) {
        for (int i = B; i >= 0; i--)
            x = max(x, x ^ p[i]);
        return x;
    }
    int rank() {
        int ans = 0;
        for (int x : p)
            ans += x != 0;
        return ans;
    }
    optional<int> kth(uint64_t k, bool nonempty = true) {
        auto b = p;
        for (int i = 0; i <= B; i++)
            if (b[i])
                for (int j = i + 1; j <= B; j++)
                    if ((b[j] >> i) & 1)
                        b[j] ^= b[i];
        vector<int> a;
        for (int x : b)
            if (x)
                a.push_back(x);
        // nonempty: k为1基；有非空零组合时，第1小为0。
        if (nonempty) {
            if (!k)
                return nullopt;
            if (zero)
                --k;
        }
        if (k >= (1ULL << a.size()))
            return nullopt;
        int ans = 0;
        for (int i = 0; i < (int)a.size(); i++)
            if ((k >> i) & 1)
                ans ^= a[i];
        return ans;
    }
};

void solve() {
    int n;
    cin >> n;
    LinearBasis t;
    while (n--) {
        int x;
        cin >> x;
        t.insert(x);
    }
    cout << t.qur() << '\n';
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
