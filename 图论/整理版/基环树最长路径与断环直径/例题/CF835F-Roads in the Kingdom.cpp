// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF835F Roads in the Kingdom
// 原题：https://codeforces.com/contest/835/problem/F
// 所属知识点：基环树最长路径与断环直径；使用模板：Island
// 题意：删去基环图的一条边保持连通，使剩余图最大点距最小。
// 转化：只能删环边；每种断法对应复制环的k点连续窗口，窗口内最长路径由有序聚合信息维护。
// 调用：读边orient；调用minimum_cut_diameter，与树内直径取max。
// 复杂度：O(n)时间与空间。
void solve() {
    int n;
    cin >> n;
    vector<array<int, 3>> e(n);
    for (auto &z : e)
        cin >> z[0] >> z[1] >> z[2];
    Island t(n);
    t.orient(e);
    cout << t.minimum_cut_diameter() << '\n';
}
