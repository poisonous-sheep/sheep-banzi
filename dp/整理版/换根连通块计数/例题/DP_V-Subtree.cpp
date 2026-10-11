// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// DP_V Subtree
// 原题：https://atcoder.jp/contests/dp/tasks/dp_v
// 所属知识点：换根连通块计数；使用模板：RerootCount
// 题意：给每点求该点为黑且全部黑点连通的染色数。
// 转化：黑点集合就是包含指定点的连通点集，每个孩子选或不选。
// 调用：读mod和树，run，逐行输出ans。
// 复杂度：O(n)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    RerootCount t(n, m);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    t.run();
    for (int i = 1; i <= n; i++)
        cout << t.ans[i] << '\n';
}
