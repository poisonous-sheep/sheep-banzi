// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P7914 括号序列
// 原题：https://www.luogu.com.cn/problem/P7914
// 所属知识点：括号计数与无歧义区间DP；使用模板：BracketDP
// 题意：将?替换为括号或星号，使超级括号序列符合规范。
// 转化：规则是嵌套加合法块拼接，需区间计数与无歧义分解，不能套普通括号余额。
// 调用：BracketDP(1e9+7).super(s,k)。
// 复杂度：O(n³)时间、O(n²)空间。
void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    BracketDP t;
    cout << t.super(s, k) << '\n';
}
