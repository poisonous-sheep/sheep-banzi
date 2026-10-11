// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2731 Riding the Fences
// 原题：https://www.luogu.com.cn/problem/P2731
// 所属知识点：无向欧拉路径；使用模板：Euler
// 题意：按字典序输出经过每条栅栏一次的路线。
// 转化：栅栏是无向多重边，选择最小奇度点或最小有边点出发。
// 调用：init(500)、addedge、run，按点逐行输出。
// 复杂度：O(m log m+500)时间、O(m+500)空间。
void solve() {
    int m;
    cin >> m;
    Euler g;
    g.init(500);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.addedge(u, v);
    }
    g.run();
    for (int u : g.path)
        cout << u << '\n';
}
