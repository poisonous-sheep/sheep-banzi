// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1122 最大子树和
// 原题：https://www.luogu.com.cn/problem/P1122
// 所属知识点：树上最大连通块权和；使用模板：TreeMaxSum
// 题意：修剪树后保留非空连通子树使权和最大。
// 转化：任何连通块在固定根下有唯一最高点；取所有f的最大值。
// 调用：写入a、add_edge、run，然后max f[1..n]。
// 复杂度：O(n)时间/空间。
void solve() {
    int n;
    cin >> n;
    TreeMaxSum t(n);
    for (int i = 1; i <= n; i++)
        cin >> t.a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    t.run();
    cout << *max_element(t.f.begin() + 1, t.f.end()) << '\n';
}
