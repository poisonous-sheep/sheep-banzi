// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1560F2 Nearest Beautiful Number hard
// 原题：https://codeforces.com/contest/1560/problem/F2
// 所属知识点：数位构造与不同数位限制；使用模板：DigitConstruct
// 题意：推广为k<=10的最小合法数。
// 转化：同一剪枝仍成立，无需枚举10位数字集合全部1024种。
// 调用：沿用at_most；这是原题的困难版，注明与F1为同题两档。
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
