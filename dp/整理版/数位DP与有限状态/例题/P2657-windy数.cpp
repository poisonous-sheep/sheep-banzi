// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2657 windy数
// 原题：https://www.luogu.com.cn/problem/P2657
// 所属知识点：数位DP与有限状态；使用模板：DigitDP
// 题意：统计区间内相邻十进制数位之差至少2的正整数。
// 转化：状态仅需前一有效数位，前导零有独立状态。
// 调用：windy配置，然后qur(R)-qur(L-1)。
// 复杂度：O(位数*110)时间、O(11)空间。
void solve() {
    int L, R;
    cin >> L >> R;
    DigitDP t;
    t.windy();
    cout << t.qur(R) - t.qur(L - 1) << '\n';
}
