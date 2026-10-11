// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1829 Crash的数字表格
// 原题：https://www.luogu.com.cn/problem/P1829
// 所属知识点：LCM矩形与集合求和；使用模板：LCMSum
// 题意：求n乘m表格内全部lcm(i,j)，模20101009。
// 转化：反演后仅需Σh(t)S(n/t)S(m/t)，两个商相同的区间可合并。
// 调用：init(min(n,m),20101009)，输出qur(n,m)。
// 复杂度：O(min(n,m))预处理，O(sqrt min(n,m))查询，O(min(n,m))空间。
void solve() {
    int n, m;
    cin >> n >> m;
    LCMSum t(min(n, m), 20101009);
    cout << t.qur(n, m) << '\n';
}
