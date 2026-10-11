// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1156E Special Segments
// 原题：https://codeforces.com/contest/1156/problem/E
// 所属知识点：启发式分治；使用模板：HeuristicDivide
// 题意：排列中计数两端和等于区间最大值的区间。
// 转化：以区间最大值m分界，跨分界的两端只枚举短侧，另一值及位置由最大值减已知值确定。
// 调用：init排列，maximum_pairs。
// 复杂度：O(n log n)时间/空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    HeuristicDivide t;
    t.init(a);
    cout << t.maximum_pairs() << '\n';
}
