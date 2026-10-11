// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4782 2-SAT
// 原题：https://www.luogu.com.cn/problem/P4782
// 所属知识点：2-SAT；使用模板：TwoSAT
// 题意：给OR子句求一个可行布尔赋值。
// 转化：每条OR拆成两个蕴含，变量两取值不能在同一SCC。
// 调用：add_or建图，solve_sat后输出ans。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    TwoSAT sat;
    sat.init_sat(n);
    while (m--) {
        int a, A, b, B;
        cin >> a >> A >> b >> B;
        sat.add_or(a, A, b, B);
    }
    if (!sat.solve_sat()) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    cout << "POSSIBLE\n";
    for (int i = 1; i <= n; i++)
        cout << sat.ans[i] << (i == n ? '\n' : ' ');
}
