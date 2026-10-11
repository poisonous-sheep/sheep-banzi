// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4570 元素
// 原题：https://www.luogu.com.cn/problem/P4570
// 所属知识点：线性基；使用模板：LinearBasis
// 题意：选择异或线性无关的矿石，使魔力总和最大。
// 转化：向量独立集构成拟阵；按魔力降序贪心，insert返回是否保持独立。
// 调用：按Magic排序，只有insert成功才累加Magic。
// 复杂度：O(n log n+nB)时间、O(n+B)空间。
void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (auto &[v, x] : a)
        cin >> x >> v;
    sort(a.rbegin(), a.rend());
    LinearBasis t;
    int ans = 0;
    for (auto [v, x] : a)
        if (t.insert(x))
            ans += v;
    cout << ans << '\n';
}
