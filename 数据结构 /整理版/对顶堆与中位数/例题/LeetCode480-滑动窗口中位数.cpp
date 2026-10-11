// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// LeetCode480 滑动窗口中位数
// 原题：https://leetcode.cn/problems/sliding-window-median/description/
// 所属知识点：对顶堆与中位数；使用模板：Mid
// 题意：返回每个长度k窗口的中位数；偶数窗口取中间两数平均。
// 转化：滑窗加入新值、删除旧值，multiset可删任意一个重复值，无需额外惰性删除；偶数窗口组合L最大与R最小。
// 调用：原平台提交Solution::medianSlidingWindow，签名使用int32_t避免宏改变平台int类型；solve是本地n,k和数组适配器。
// 复杂度：O(n log k)时间/O(k)维护空间，输出另需O(n)。
struct Solution {
    vector<double> medianSlidingWindow(vector<int32_t> &nums, int32_t k) {
        Mid t;
        vector<double> ans;
        for (int i = 0; i < (int)nums.size(); i++) {
            t.add(nums[i]);
            if (i >= k)
                t.del(nums[i - k]);
            if (i + 1 >= k) {
                double z = t.mid();
                if (k % 2 == 0)
                    z = (z + (double)*t.R.begin()) / 2;
                ans.push_back(z);
            }
        }
        return ans;
    }
};
void solve() {
    int n;
    int32_t k;
    cin >> n >> k;
    vector<int32_t> a(n);
    for (auto &x : a)
        cin >> x;
    Solution s;
    auto ans = s.medianSlidingWindow(a, k);
    for (double x : ans)
        cout << setprecision(10) << x << ' ';
    cout << '\n';
}
