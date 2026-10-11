// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1273 有线电视网
// 原题：https://www.luogu.com.cn/problem/P1273
// 所属知识点：子树合并背包；使用模板：TreeKnapsack
// 题意：选择尽量多用户，在用户收益扣转播边费用后不亏本。
// 转化：只有叶子计用户数；某孩子子树接入了至少一个用户时才支付该边费用。
// 调用：内部节点w=0，叶子w=1且a=收益，add_edge含费用；从大到小找dp根[k]>=0。
// 复杂度：O(nm)时间/空间。
void solve() {
    int n, m;
    cin >> n >> m;
    TreeKnapsack t(n, m);
    for (int u = 1; u <= n - m; u++) {
        t.w[u] = 0;
        int k;
        cin >> k;
        while (k--) {
            int v, c;
            cin >> v >> c;
            t.add_edge(u, v, c);
        }
    }
    for (int u = n - m + 1; u <= n; u++)
        cin >> t.a[u];
    t.run(1);
    for (int k = m; k >= 0; k--)
        if (t.qur(1, k) >= 0) {
            cout << k << '\n';
            break;
        }
}
