// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1495 曹冲养猪
// 原题：https://www.luogu.com.cn/problem/P1495
// 所属知识点：中国剩余定理；使用模板：CRT
// 题意：给若干除数和余数，求满足条件的最小猪数。
// 转化：各同余两两互质，是普通CRT。
// 调用：读入m,r后merge(r,m)，输出ans。
// 复杂度：O(n log M)时间。
void solve() {
    int n;
    cin >> n;
    CRT crt;
    while (n--) {
        int m, r;
        cin >> m >> r;
        crt.merge(r, m);
    }
    cout << crt.ans << '\n';
}
