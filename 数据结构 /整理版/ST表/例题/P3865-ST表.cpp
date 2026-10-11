// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3865 ST表
// 原题：https://www.luogu.com.cn/problem/P3865
// 所属知识点：ST表；使用模板：ST
// 题意：静态区间最大值。
// 转化：max幂等，重叠查询段不会重复影响答案。
// 调用：build(a)，qur(l,r).mx。
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
        cout << st.qur(l, r).mx << '\n';
    }
}
