// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC219G Propagation
// 原题：https://atcoder.jp/contests/abc219/tasks/abc219_g
// 所属知识点：度数根号分治；使用模板：DegreeDivide
// 题意：查询点将自身数字复制给所有邻居，最终输出所有点数字。
// 转化：高次数邻居更新用重度懒广播规避星形图退化。
// 调用：build初始col[i]=i；每次x先qur(x)，再change(x,c,false)。
// 复杂度：O(n+m+q sqrt m)时间、O(n+m)空间。
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    DegreeDivide t(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        t.add_edge(u, v);
    }
    vector<int> a(n + 1);
    iota(a.begin(), a.end(), 0);
    t.build(a);
    while (q--) {
        int x;
        cin >> x;
        int c = t.qur(x);
        t.change(x, c);
    }
    for (int i = 1; i <= n; i++)
        cout << t.qur(i) << " \n"[i == n];
}
