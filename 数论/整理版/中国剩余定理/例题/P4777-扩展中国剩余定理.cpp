// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4777 扩展中国剩余定理
// 原题：https://www.luogu.com.cn/problem/P4777
// 所属知识点：中国剩余定理；使用模板：CRT
// 题意：合并不保证互质的同余方程。
// 转化：差值必须被gcd整除；新模数取lcm而非乘积。
// 调用：逐式merge，按题面存在解约定输出ans。
// 复杂度：O(n log M)时间。
void solve() {
    int n;
    cin >> n;
    CRT crt;
    bool ok = true;
    while (n--) {
        int m, r;
        cin >> m >> r;
        if (ok)
            ok = crt.merge(r, m);
    }
    cout << (ok ? crt.ans : -1) << '\n';
}
