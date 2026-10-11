// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3275 糖果
// 原题：https://www.luogu.com.cn/problem/P3275
// 所属知识点：差分约束；使用模板：Difference
// 题意：每人至少1颗糖，满足五类大小关系，最少糖果总数。
// 转化：取x=-糖果数后全部边权0或-1；同SCC负边意味着矛盾，缩点最长路求最小糖果。
// 调用：映射五类约束后minimum_positive；输出-sum(x)。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    Difference g;
    g.init(n);
    while (m--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) {
            g.add_constraint(a, b, 0);
            g.add_constraint(b, a, 0);
        } else if (op == 2)
            g.add_constraint(a, b, -1);
        else if (op == 3)
            g.add_constraint(b, a, 0);
        else if (op == 4)
            g.add_constraint(b, a, -1);
        else
            g.add_constraint(a, b, 0);
    }
    if (!g.minimum_positive()) {
        cout << -1 << '\n';
        return;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans -= g.x[i];
    cout << ans << '\n';
}
