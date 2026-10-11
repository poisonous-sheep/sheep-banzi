// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3807 Lucas定理
// 原题：https://www.luogu.com.cn/problem/P3807
// 所属知识点：Lucas定理；使用模板：Lucas
// 题意：多组求C(n+m,n) mod p。
// 转化：n可大于p，逐位Lucas降为小组合数。
// 调用：每个p重新init，binom(n+m,n)。
// 复杂度：每组O(p+log_p(n+m))时间、O(p)空间。
void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n, m, p;
        cin >> n >> m >> p;
        Lucas c;
        c.init(p);
        cout << c.binom(n + m, n) << '\n';
    }
}
