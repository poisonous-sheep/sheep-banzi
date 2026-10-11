// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC436E Minimum Swap
// 原题：https://atcoder.jp/contests/abc436/tasks/abc436_e
// 所属知识点：置换环分解；使用模板：Permutation
// 题意：计数能作为最少交换排序方案第一步的交换。
// 转化：最优步骤必须令环数加1，因此两点必须在同一个原置换环内；任意同环两点都能拆成两个环。
// 调用：init、build，对每个cycle长度L累加L(L-1)/2。
// 复杂度：O(n)时间/O(n)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    Permutation t;
    t.init(a);
    t.build();
    int ans = 0;
    for (auto &c : t.cycle) {
        int L = c.size();
        ans += L * (L - 1) / 2;
    }
    cout << ans << '\n';
}
