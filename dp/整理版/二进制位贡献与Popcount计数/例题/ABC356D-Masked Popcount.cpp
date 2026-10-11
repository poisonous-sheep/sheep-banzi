// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC356D Masked Popcount
// 原题：https://atcoder.jp/contests/abc356/tasks/abc356_d
// 所属知识点：二进制位贡献与Popcount计数；使用模板：PopcountDP
// 题意：求0..N每个数与M按位与后的popcount总和。
// 转化：拆成M中每个1位出现次数；该位0/1按周期交替。
// 调用：PopcountDP(998244353).masked(N,M)。
// 复杂度：O(log N)时间、O(1)空间。
void solve() {
    int N, M;
    cin >> N >> M;
    PopcountDP t(998244353);
    cout << t.masked(N, M) << '\n';
}
