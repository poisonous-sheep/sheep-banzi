// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// Gym103470H Crystalfly
// 原题：https://codeforces.com/gym/103470/problem/H
// 所属知识点：Crystalfly三状态树DP；使用模板：Crystalfly
// 题意：在树上行走抓晶蝶，邻点晶蝶被首次惊动后延迟1..3秒消失，求最大收益。
// 转化：t≤3使一个父亲处最多及时取得两个子点收益；枚举立即返回的第一子点，配不同的t=3第二子点，保留深入与后续失收益遍历两种贡献。
// 调用：读T、n、a、t、边，调用run(1)。
// 复杂度：O(n)时间/O(n)空间。
void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        Crystalfly c(n);
        for (int u = 1; u <= n; u++)
            cin >> c.a[u];
        for (int u = 1; u <= n; u++)
            cin >> c.t[u];
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            c.add_edge(u, v);
        }
        cout << c.run() << '\n';
    }
}
