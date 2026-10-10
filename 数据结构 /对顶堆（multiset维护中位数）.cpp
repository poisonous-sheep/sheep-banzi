#include <bits/stdc++.h>
using namespace std;

#define int long long

// multiset 模拟对顶堆：支持动态插入、删除任意一个值、查询中位数与绝对值距离和。
// L 存较小的一半，R 存较大的一半（允许重复元素）。
// 维护：max(L) <= min(R)，且 |L| = |R| 或 |L| = |R| + 1。
// 因此 L 的最大值就是“下中位数”（偶数长度取靠左的中位数）。
// 所有操作 O(log n)，查询中位数 / cost 为 O(1)。
struct Mid {
    multiset<int> L, R;
    int sumL = 0, sumR = 0;

    void init() {
        L.clear();
        R.clear();
        sumL = sumR = 0;
    }

    int size() const { return L.size() + R.size(); }
    bool empty() const { return L.empty() && R.empty(); }

    // 调整两个集合大小。插入时按 L 的最大值分类，保证大小调整后顺序仍正确。
    void balance() {
        while (L.size() > R.size() + 1) {
            auto it = prev(L.end());
            int x = *it;
            L.erase(it);
            sumL -= x;
            R.insert(x);
            sumR += x;
        }
        while (L.size() < R.size()) {
            auto it = R.begin();
            int x = *it;
            R.erase(it);
            sumR -= x;
            L.insert(x);
            sumL += x;
        }
    }

    // 插入一个 x，可有重复元素。
    void add(int x) {
        if (L.empty() || x <= *L.rbegin()) {
            L.insert(x);
            sumL += x;
        } else {
            R.insert(x);
            sumR += x;
        }
        balance();
    }

    // 删除一个值为 x 的元素（只删一次）；要求 x 已存在。
    void del(int x) {
        auto it = L.find(x);
        if (it != L.end()) {
            L.erase(it);
            sumL -= x;
        } else {
            it = R.find(x);
            assert(it != R.end());
            R.erase(it);
            sumR -= x;
        }
        balance();
    }

    // 当前下中位数；要求非空。
    int mid() const {
        assert(!L.empty());
        return *L.rbegin();
    }

    // min_x sum |a_i - x|，最优 x 可以取中位数。空集返回 0。
    int cost() const {
        if (empty()) return 0;
        int x = mid();
        return x * (int)L.size() - sumL + sumR - x * (int)R.size();
    }
};

// 用法示例：2023 ICPC 济南区域赛 K - Rainbow Subarray。
// 将 a[i] -= i，等差为 1 的区间变成相等区间；
// 双指针维护“区间元素全部变成中位数的最少操作次数 <= k”。
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] -= i;
    }

    Mid st;
    int l = 1, ans = 0;
    for (int r = 1; r <= n; r++) {
        st.add(a[r]);
        while (st.cost() > k) {
            st.del(a[l]);
            l++;
        }
        ans = max(ans, r - l + 1);
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
