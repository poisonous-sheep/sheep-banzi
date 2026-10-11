// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1168 中位数
// 原题：https://www.luogu.com.cn/problem/P1168
// 所属知识点：对顶堆与中位数；使用模板：Mid
// 题意：依次读入整数，对每个奇数长度前缀输出中位数。
// 转化：插入后保持两个集合的大小与顺序，中位数直接取L最大值。
// 调用：逐个add，奇数次插入后输出mid()。
// 复杂度：O(n log n)时间、O(n)空间。
void solve() {
    int n;
    cin >> n;
    Mid st;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        st.add(x);
        if (i % 2)
            cout << st.mid() << '\n';
    }
}
