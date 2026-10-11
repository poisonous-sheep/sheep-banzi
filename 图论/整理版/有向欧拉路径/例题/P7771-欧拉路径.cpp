// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P7771 欧拉路径
// 原题：https://www.luogu.com.cn/problem/P7771
// 所属知识点：有向欧拉路径；使用模板：Euler
// 题意：输出字典序最小有向欧拉路，没有则No。
// 转化：度数唯一决定非回路起点；降序邻接pop_back优先小点。
// 调用：run(true)后输出path。
// 复杂度：O(m log m+n)时间、O(n+m)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    Euler g;
    g.init(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
    }
    if (!g.run()) {
        cout << "No\n";
        return;
    }
    for (int u : g.path)
        cout << u << ' ';
    cout << '\n';
}
