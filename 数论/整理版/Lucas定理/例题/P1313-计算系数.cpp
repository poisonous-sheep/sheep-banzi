// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1313 计算系数
// 原题：https://www.luogu.com.cn/problem/P1313
// 所属知识点：Lucas定理；使用模板：Lucas
// 题意：求(ax+by)^k中x^n*y^m的系数模10007。
// 转化：二项式定理给C(k,n)*a^n*b^m；Lucas负责组合数部分。
// 调用：init(10007)，binom与powmod组合。
// 复杂度：O(10007+log k)时间、O(10007)空间。
void solve() {
    int a, b, k, n, m;
    cin >> a >> b >> k >> n >> m;
    Lucas c;
    c.init(10007);
    int ans = c.binom(k, n) * c.powmod(a, n) % 10007 * c.powmod(b, m) % 10007;
    cout << ans << '\n';
}
