// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2014 选课 DFS序版
// 原题：https://www.luogu.com.cn/problem/P2014
// 所属知识点：DFS序依赖背包；使用模板：DependencyKnapsack
// 题意：按先修条件恰好选m门课。
// 转化：先修树的合法点集在DFS序中只能“选当前”或“跳整子树”。
// 调用：真实课w=1、虚根w=0，run(0,true)。
// 复杂度：O(nm)时间/空间。
void solve() {
    int n, m;
    cin >> n >> m;
    DependencyKnapsack t(n, m);
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p >> t.a[i];
        t.w[i] = 1;
        t.add_edge(p, i);
    }
    cout << t.run(0, true) << '\n';
}
