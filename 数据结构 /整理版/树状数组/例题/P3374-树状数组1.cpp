// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3374 树状数组1
// 原题：https://www.luogu.com.cn/problem/P3374
// 所属知识点：树状数组；使用模板：BIT
// 题意：单点加、区间和。
// 转化：将区间和拆成两段前缀和之差。
// 调用：init(n)，依次add初值；操作add或rangeSum。
// 复杂度：O((n+m)log n)时间、O(n)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    BIT<int> bit(n);
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        bit.add(i, x);
    }
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
            bit.add(x, y);
        else
            cout << bit.rangeSum(x, y) << '\n';
    }
}
