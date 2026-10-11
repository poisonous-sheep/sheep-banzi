// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC350C Sort
// 原题：https://atcoder.jp/contests/abc350/tasks/abc350_c
// 所属知识点：置换环分解；使用模板：Permutation
// 题意：将排列用最多n-1次任意交换排好，并输出交换。
// 转化：每次把位置i正确值换入，拆分置换环，总次数正好n-环数。
// 调用：init，sort_swaps，输出操作列表。
// 复杂度：O(n)时间/O(n)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    Permutation t;
    t.init(a);
    auto ans = t.sort_swaps();
    cout << ans.size() << '\n';
    for (auto [u, v] : ans)
        cout << u << ' ' << v << '\n';
}
