// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1967 货车运输
// 原题：https://www.luogu.com.cn/problem/P1967
// 所属知识点：Kruskal重构树；使用模板：KruskalTree
// 题意：求路径上最小载重尽可能大的容量。
// 转化：降序合并首次连通阈值是最大最小边。
// 调用：build(true)，qur，不连通-1。
// 复杂度：O(m log m+n log n+q log n)时间、O(m+n log n)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    KruskalTree tr;
    tr.init(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        tr.addedge(u, v, w);
    }
    tr.build(true);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << tr.qur(u, v) << '\n';
    }
}
