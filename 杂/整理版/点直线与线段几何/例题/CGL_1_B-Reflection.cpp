// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CGL_1_B Reflection
// 原题：https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B
// 所属知识点：点直线与线段几何；使用模板：Geometry
// 题意：求点关于直线的镜像。
// 转化：垂足是点与镜像的中点，镜像=2*投影-原点。
// 调用：调用reflect(a,b,p)。
// 复杂度：O(q)时间、O(1)额外空间。
void solve() {
    P a, b;
    a.read();
    b.read();
    Geometry t;
    int q;
    cin >> q;
    cout << fixed << setprecision(10);
    while (q--) {
        P p;
        p.read();
        P h = t.reflect(a, b, p);
        cout << h.x << ' ' << h.y << '\n';
    }
}
