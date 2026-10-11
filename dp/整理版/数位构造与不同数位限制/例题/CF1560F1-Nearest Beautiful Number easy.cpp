// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1560F1 Nearest Beautiful Number easy
// 原题：https://codeforces.com/contest/1560/problem/F1
// 所属知识点：数位构造与不同数位限制；使用模板：DigitConstruct
// 题意：k<=2时构造不小于n的最近美丽数。
// 转化：按数位升序找第一个可完成方案就是最小合法数。
// 调用：每组at_most(to_string(n),k)。
// 复杂度：每组O(L*10)时间、O(L+10)空间。
void solve() {
    int T;
    cin >> T;
    DigitConstruct t;
    while (T--) {
        string n;
        int k;
        cin >> n >> k;
        cout << t.at_most(n, k) << '\n';
    }
}
