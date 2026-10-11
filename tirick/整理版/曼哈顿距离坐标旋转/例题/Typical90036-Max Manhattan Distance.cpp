// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// Typical90036 Max Manhattan Distance
// 原题：https://atcoder.jp/contests/typical90/tasks/typical90_aj
// 所属知识点：曼哈顿距离坐标旋转；使用模板：Manhattan
// 题意：多次指定一个已有点，询问到所有点的最大曼哈顿距离。
// 转化：两维极值由全部点共享，每问只比较到四个端点。
// 调用：保留点数组；add预处理，qur(a[q])。
// 复杂度：O(n+q)时间/O(n)空间（保存输入点）。
void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n + 1);
    Manhattan t;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
        t.add(a[i].first, a[i].second);
    }
    while (q--) {
        int k;
        cin >> k;
        cout << t.qur(a[k].first, a[k].second) << '\n';
    }
}
