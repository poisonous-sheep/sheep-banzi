// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF797E Array Queries
// 原题：https://codeforces.com/contest/797/problem/E
// 所属知识点：步长根号分治；使用模板：SqrtDivide
// 题意：多次询问正数数组从p开始跳p+a[p]+k的次数。
// 转化：k较小时重复查询可复用倒序DP；大k每次跳至少k格。
// 调用：读数组后build_jump，再逐次jump_count。
// 复杂度：O(n sqrt n+q sqrt n)时间、O(n sqrt n)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    SqrtDivide t(n);
    t.build_jump(a);
    int q;
    cin >> q;
    while (q--) {
        int p, k;
        cin >> p >> k;
        cout << t.jump_count(p, k) << '\n';
    }
}
