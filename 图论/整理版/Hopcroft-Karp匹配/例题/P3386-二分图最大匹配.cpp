// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3386 二分图最大匹配
// 原题：https://www.luogu.com.cn/problem/P3386
// 所属知识点：Hopcroft-Karp匹配；使用模板：HK
// 题意：求左右两部图最大匹配数。
// 转化：每点最多匹配一次，直接构造左到右的边。
// 调用：init(n,m)，add(u,v)，matching()。
// 复杂度：HK为O(E sqrt V)时间、O(V+E)空间。
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    HK hk;
    hk.init(n, m);
    while (q--) {
        int u, v;
        cin >> u >> v;
        hk.add(u, v);
    }
    cout << hk.matching() << '\n';
}
