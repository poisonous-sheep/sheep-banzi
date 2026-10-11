// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1324F Maximum White Subtree
// 原题：https://codeforces.com/contest/1324/problem/F
// 所属知识点：树上最大连通块权和；使用模板：TreeMaxSum
// 题意：对每点求包含它的连通块中白数减黑数的最大值。
// 转化：白点权+1，黑点权-1；换根把子树答案扩展为整树答案。
// 调用：把输入颜色转为2*a-1，run后输出ans。
// 复杂度：O(n)时间/空间。
void solve() {
    int n;
    cin >> n;
    TreeMaxSum t(n);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        t.a[i] = 2 * x - 1;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    t.run();
    for (int i = 1; i <= n; i++)
        cout << t.ans[i] << " \n"[i == n];
}
