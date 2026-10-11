// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4171 满汉全席
// 原题：https://www.luogu.com.cn/problem/P4171
// 所属知识点：2-SAT；使用模板：TwoSAT
// 题意：每种材料做满式或汉式，满足每位评委至少喜欢一种菜。
// 转化：评委条件是两个取值命题的OR子句。
// 调用：h映射1、m映射0；每组init后add_or并判定。
// 复杂度：O(总变量+总条件)时间与空间。
void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        TwoSAT sat;
        sat.init_sat(n);
        while (m--) {
            char a, b;
            int x, y;
            cin >> a >> x >> b >> y;
            sat.add_or(x, a == 'h', y, b == 'h');
        }
        cout << (sat.solve_sat() ? "GOOD" : "BAD") << '\n';
    }
}
