// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF598C Nearest vectors
// 原题：https://codeforces.com/contest/598/problem/C
// 所属知识点：极角排序；使用模板：PolarSort
// 题意：寻找最小夹角的一对非零向量。
// 转化：最小夹角一定来自极角序的相邻向量；包含首尾圆周相邻。
// 调用：按cmp排序带原编号向量，逐对用atan2(abs(det),dot)取夹角。
// 复杂度：O(n log n)时间、O(n)空间。
void solve() {
    int n;
    cin >> n;
    vector<pair<P, int>> a(n);
    for (int i = 0; i < n; i++)
        a[i].first.read(), a[i].second = i + 1;
    sort(a.begin(), a.end(),
         [](auto a, auto b) { return PolarSort::cmp(a.first, b.first); });
    db best = 10;
    pair<int, int> ans;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        db ang = atan2l(fabsl(a[i].first.det(a[j].first)), a[i].first.dot(a[j].first));
        if (ang < best)
            best = ang, ans = {a[i].second, a[j].second};
    }
    cout << ans.first << ' ' << ans.second << '\n';
}
