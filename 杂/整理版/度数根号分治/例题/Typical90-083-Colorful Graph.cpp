// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// Typical90-083 Colorful Graph
// 原题：https://atcoder.jp/contests/typical90/tasks/typical90_ce
// 所属知识点：度数根号分治；使用模板：DegreeDivide
// 题意：输出指定点当前颜色后，将它及全部邻居改成新颜色。
// 转化：邻居广播与前题同模型，区别是本点也赋值。
// 调用：初始全1；qur(x)输出后change(x,y,true)。
// 复杂度：O(n+m+q sqrt m)时间、O(n+m)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    DegreeDivide t(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    t.build(vector<int>(n + 1, 1));
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << t.qur(x) << '\n';
        t.change(x, y, true);
    }
}
