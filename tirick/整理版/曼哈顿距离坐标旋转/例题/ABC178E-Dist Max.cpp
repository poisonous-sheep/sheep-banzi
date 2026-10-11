// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC178E Dist Max
// 原题：https://atcoder.jp/contests/abc178/tasks/abc178_e
// 所属知识点：曼哈顿距离坐标旋转；使用模板：Manhattan
// 题意：求平面n点两两曼哈顿距离的最大值。
// 转化：max(|Δu|,|Δv|)的最大值由每一维最大减最小得到。
// 调用：add所有点，diameter。
// 复杂度：O(n)时间/O(1)额外空间。
void solve() {
    int n;
    cin >> n;
    Manhattan t;
    while (n--) {
        int x, y;
        cin >> x >> y;
        t.add(x, y);
    }
    cout << t.diameter() << '\n';
}
