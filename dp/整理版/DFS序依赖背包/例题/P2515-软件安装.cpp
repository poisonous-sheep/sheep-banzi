// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2515 软件安装
// 原题：https://www.luogu.com.cn/problem/P2515
// 所属知识点：DFS序依赖背包；使用模板：DependencyKnapsack
// 题意：有最多一个依赖的软件选择，可能存在依赖环，限定容量求最大价值。
// 转化：环中软件必须全选或全不选；SCC缩点后依赖变森林，再DFS序背包。
// 调用：SCC.scc取得col，合计包w/a；无前提包接虚根；run(0)。
// 复杂度：O(nM+n)时间、O(nM)空间。
void solve() {
    int n, M;
    cin >> n >> M;
    vector<int> w(n + 1), a(n + 1), p(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    SCC s;
    s.init(n);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        if (p[i])
            s.addedge(p[i], i);
    }
    s.run();
    DependencyKnapsack t(s.cnt, M);
    vector<int> in(s.cnt + 1);
    for (int i = 1; i <= n; i++) {
        t.w[s.bel[i]] += w[i];
        t.a[s.bel[i]] += a[i];
        if (p[i] && s.bel[p[i]] != s.bel[i])
            t.add_edge(s.bel[p[i]], s.bel[i]), in[s.bel[i]] = 1;
    }
    for (int i = 1; i <= s.cnt; i++)
        if (!in[i])
            t.add_edge(0, i);
    cout << t.run(0) << '\n';
}
