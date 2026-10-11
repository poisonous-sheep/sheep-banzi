// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF543D Road Improvement
// 原题：https://codeforces.com/contest/543/problem/D
// 所属知识点：换根连通块计数；使用模板：RerootCount
// 题意：对每个首都，统计满足各路径最多一条未修路的道路修复方式。
// 转化：以首都为根时，若父边未修，整棵子树内所有边必须修；否则子树继续有dp种选择，所以同样是(dp[v]+1)乘积。
// 调用：输入2..n父节点，add_edge，run；输出ans。
// 复杂度：O(n)时间与空间。
void solve() {
    int n;
    cin >> n;
    RerootCount t(n);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        t.add_edge(p, i);
    }
    t.run();
    for (int i = 1; i <= n; i++)
        cout << t.ans[i] << " \n"[i == n];
}
