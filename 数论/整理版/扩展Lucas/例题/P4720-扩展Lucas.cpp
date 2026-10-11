// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4720 扩展Lucas
// 原题：https://www.luogu.com.cn/problem/P4720
// 所属知识点：扩展Lucas；使用模板：ExLucas
// 题意：求C(n,m)模给定合数p。
// 转化：普通逆阶乘不适用；分解为质数幂计算后CRT。
// 调用：init(p)，binom(n,m)。
// 复杂度：按模板复杂度。
void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    ExLucas c;
    c.init(p);
    cout << c.binom(n, m) << '\n';
}
