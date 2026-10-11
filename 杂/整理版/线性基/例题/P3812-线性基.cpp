// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3812 线性基
// 原题：https://www.luogu.com.cn/problem/P3812
// 所属知识点：线性基；使用模板：LinearBasis
// 题意：从给定整数中选任意子集，使异或和最大。
// 转化：所有子集异或构成向量空间，逐位贪心最大化。
// 调用：逐个insert，输出qur()。
// 复杂度：O(nB)时间、O(B)空间。
void solve() {
    int n;
    cin >> n;
    LinearBasis t;
    while (n--) {
        int x;
        cin >> x;
        t.insert(x);
    }
    cout << t.qur() << '\n';
}
