// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2014 选课
// 原题：https://www.luogu.com.cn/problem/P2014
// 所属知识点：子树合并背包；使用模板：TreeKnapsack
// 题意：恰好选m门课并满足先修依赖，使学分最大。
// 转化：无先修课程挂在虚根0，虚根w=0不计课程数；每个真实课程w=1。
// 调用：add_edge(先修,i)，run(0)，qur(0,m)。
// 复杂度：O(nm)时间/空间。
void solve() {
    int n, m;
    cin >> n >> m;
    TreeKnapsack t(n, m);
    t.w[0] = 0;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p >> t.a[i];
        t.add_edge(p, i);
    }
    t.run(0);
    cout << t.qur(0, m) << '\n';
}
