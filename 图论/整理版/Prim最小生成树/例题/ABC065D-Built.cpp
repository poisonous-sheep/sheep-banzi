// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC065D Built
// 原题：https://atcoder.jp/contests/abc065/tasks/arc076_b
// 所属知识点：Prim最小生成树；使用模板：Prim
// 题意：平面点间建路，代价min(|dx|,|dy|)，求最小总费用。
// 转化：按x/y排序的相邻点边足以保留MST；把完全图稀疏化后运行Prim。
// 调用：两种排序加相邻边，权值取真实min差；run。
// 复杂度：O(n log n)时间、O(n)空间。
void solve() {
    int n;
    cin >> n;
    vector<array<int, 3>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i + 1;
    }
    Prim g;
    g.init(n);
    for (int dim = 0; dim < 2; dim++) {
        sort(a.begin(), a.end(), [&](auto x, auto y) { return x[dim] < y[dim]; });
        for (int i = 1; i < n; i++)
            g.addedge(a[i - 1][2], a[i][2],
                      min(llabs(a[i][0] - a[i - 1][0]), llabs(a[i][1] - a[i - 1][1])));
    }
    cout << g.run().second << '\n';
}
