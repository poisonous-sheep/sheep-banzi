// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CGL_1_A Projection
// 原题：https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A
// 所属知识点：点直线与线段几何；使用模板：Geometry
// 题意：求多点到给定直线的垂足。
// 转化：点在直线方向上的正交分量由点积给出。
// 调用：读取a,b，每点proj后输出x,y。
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
        P h = t.proj(a, b, p);
        cout << h.x << ' ' << h.y << '\n';
    }
}
