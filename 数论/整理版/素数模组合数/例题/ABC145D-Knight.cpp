// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC145D Knight
// 原题：https://atcoder.jp/contests/abc145/tasks/abc145_d
// 所属知识点：素数模组合数；使用模板：Comb
// 题意：每步(1,2)或(2,1)，求走到(X,Y)方案数。
// 转化：求两种步数a=(2Y-X)/3、b=(2X-Y)/3，非负整数时组合数计排列。
// 调用：检查整除与非负；init(a+b)，binom(a+b,a)。
// 复杂度：O(X+Y)时间与空间上界。
void solve() {
    int x, y;
    cin >> x >> y;
    int a = 2 * y - x, b = 2 * x - y;
    if (a < 0 || b < 0 || a % 3 || b % 3) {
        cout << 0 << '\n';
        return;
    }
    a /= 3;
    b /= 3;
    Comb c;
    c.init(a + b);
    cout << c.binom(a + b, a) << '\n';
}
