// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2163 园丁的烦恼
// 原题：https://www.luogu.com.cn/problem/P2163
// 所属知识点：离线二维数点；使用模板：RectangleCounter
// 题意：查询二维平面闭矩形内树木棵数。
// 转化：静态点与离线矩形查询正好对应二维前缀容斥。
// 调用：逐点add，逐询问ask，run后输出每个答案。
// 复杂度：O((n+m)log(n+m))时间与O(n+m)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    RectangleCounter t;
    while (n--) {
        int x, y;
        cin >> x >> y;
        t.add(x, y);
    }
    while (m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        t.ask(a, b, c, d);
    }
    for (int x : t.run())
        cout << x << '\n';
}
