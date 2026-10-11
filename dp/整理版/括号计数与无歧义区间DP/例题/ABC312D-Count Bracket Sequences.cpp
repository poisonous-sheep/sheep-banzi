// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC312D Count Bracket Sequences
// 原题：https://atcoder.jp/contests/abc312/tasks/abc312_d
// 所属知识点：括号计数与无歧义区间DP；使用模板：BracketDP
// 题意：无星号情况下，将?替换成括号并计数。
// 转化：无星号退化为普通平衡括号，n=3000必须用余额滚动DP。
// 调用：BracketDP(998244353).normal(s)。
// 复杂度：O(n²)时间、O(n)空间。
void solve() {
    string s;
    cin >> s;
    BracketDP t(998244353);
    cout << t.normal(s) << '\n';
}
