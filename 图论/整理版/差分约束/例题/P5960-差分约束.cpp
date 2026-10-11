// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P5960 差分约束
// 原题：https://www.luogu.com.cn/problem/P5960
// 所属知识点：差分约束；使用模板：Difference
// 题意：求形如x[c]-x[c2]<=y的不等式组可行解。
// 转化：边c2->c权y，用全零初值等价于超级源连到全部点。
// 调用：add_constraint(c2,c,y)，solve后输出x。
// 复杂度：O(nm)时间、O(n+m)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    Difference g;
    g.init(n);
    while (m--) {
        int c, d, y;
        cin >> c >> d >> y;
        g.add_constraint(d, c, y);
    }
    if (!g.solve()) {
        cout << "NO\n";
        return;
    }
    for (int i = 1; i <= n; i++)
        cout << g.x[i] << (i == n ? '\n' : ' ');
}
