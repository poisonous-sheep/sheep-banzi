// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P5192 Shoot the Bullet
// 原题：https://www.luogu.com.cn/problem/P5192
// 所属知识点：有上下界可行流与最大流；使用模板：BoundedFlow
// 题意：每天拍摄总量上限、每次对象数量区间、每位少女总需求下限，最大拍摄量。
// 转化：每项区间对应一天到少女的上下界边，少女到汇的下界代表需求，属于有源汇上下界最大流。
// 调用：S->天[0,D]，天->少女[L,R]，少女->T[G,INF]，maxflow。重复少女边分别保留。
// 复杂度：一般O(V²E)时间、O(V+E)空间。
void solve() {
    int n, m;
    while (cin >> n >> m) {
        int s = n + m + 1, t = s + 1;
        BoundedFlow g(t);
        for (int j = 0; j < m; j++) {
            int G;
            cin >> G;
            g.add_edge(n + j + 1, t, G, 1000000000);
        }
        for (int i = 1; i <= n; i++) {
            int C, D;
            cin >> C >> D;
            g.add_edge(s, i, 0, D);
            while (C--) {
                int j, L, R;
                cin >> j >> L >> R;
                g.add_edge(i, n + j + 1, L, R);
            }
        }
        auto ans = g.maxflow(s, t);
        cout << (ans ? *ans : -1) << "\n\n";
    }
}
