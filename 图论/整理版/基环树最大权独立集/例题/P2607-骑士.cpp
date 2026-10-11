// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2607 骑士
// 原题：https://www.luogu.com.cn/problem/P2607
// 所属知识点：基环树最大权独立集；使用模板：Knight
// 题意：每位骑士有收益和一个不能同时选的对象，最大总收益。
// 转化：每点恰好一条指向冲突对象的边，弱分量是基环树。
// 调用：输入收益val及后继p，run。
// 复杂度：O(n)时间/空间。
void solve() {
    int n;
    cin >> n;
    Knight t(n);
    for (int u = 1; u <= n; u++)
        cin >> t.val[u] >> t.p[u];
    cout << t.run() << '\n';
}
