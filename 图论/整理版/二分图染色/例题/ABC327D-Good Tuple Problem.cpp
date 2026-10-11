// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC327D Good Tuple Problem
// 原题：https://atcoder.jp/contests/abc327/tasks/abc327_d
// 所属知识点：二分图染色；使用模板：BipColor
// 题意：给定成对约束X[Ai]!=X[Bi]，判断是否存在0/1赋值。
// 转化：每对不等约束就是边的两端必须不同色。
// 调用：分别读取A和B数组后addedge，run输出Yes/No。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m);
    for (int &x : a)
        cin >> x;
    for (int &x : b)
        cin >> x;
    BipColor g;
    g.init(n);
    for (int i = 0; i < m; i++)
        g.addedge(a[i], b[i]);
    cout << (g.run() ? "Yes" : "No") << '\n';
}
