// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4381 Island
// 原题：https://www.luogu.com.cn/problem/P4381
// 所属知识点：基环树最长路径与断环直径；使用模板：Island
// 题意：多个基环分量各取最长简单路径，再把长度相加。
// 转化：路径要么在一个外挂树内，要么经环连接不同树根，分别计算取最大。
// 调用：输入p[u],w[u]，run。
// 复杂度：O(n)时间与空间。
void solve() {
    int n;
    cin >> n;
    Island t(n);
    for (int i = 1; i <= n; i++)
        cin >> t.p[i] >> t.w[i];
    cout << t.run() << '\n';
}
