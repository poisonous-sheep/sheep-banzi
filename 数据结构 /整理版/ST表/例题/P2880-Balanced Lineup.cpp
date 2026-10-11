// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2880 Balanced Lineup
// 原题：https://www.luogu.com.cn/problem/P2880
// 所属知识点：ST表；使用模板：ST
// 题意：每段牛身高的最大值与最小值之差。
// 转化：一次info同时维护min/max，查询后相减。
// 调用：qur返回info，输出mx-mn。
// 复杂度：O(n log n+q)时间、O(n log n)空间。
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    ST st;
    st.build(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        auto v = st.qur(l, r);
        cout << v.mx - v.mn << '\n';
    }
}
