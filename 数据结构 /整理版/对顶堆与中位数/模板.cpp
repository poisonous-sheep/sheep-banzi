#include <bits/stdc++.h>
using namespace std;
#define int long long

// 对顶堆与中位数：动态插入删除，查询下中位数与到中位数的绝对值和；允许重复。
// 增删O(log n)，mid/cost为O(1)，空间O(n)。
struct Mid {
    multiset<int> L, R;
    int sumL = 0, sumR = 0;

    void init() {
        L.clear();
        R.clear();
        sumL = sumR = 0;
    }

    int size() const {
        return L.size() + R.size();
    }
    bool empty() const {
        return L.empty() && R.empty();
    }

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
        if (empty())
            return 0;
        int x = mid();
        return x * (int)L.size() - sumL + sumR - x * (int)R.size();
    }
};

void solve() {
    int q;
    cin >> q;
    Mid st;
    int bsum = 0;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int a, b;
            cin >> a >> b;
            st.add(a);
            bsum += b;
        } else
            cout << st.mid() << ' ' << st.cost() + bsum << '\n';
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
