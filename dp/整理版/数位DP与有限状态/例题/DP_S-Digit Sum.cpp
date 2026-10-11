// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// DP_S Digit Sum
// 原题：https://atcoder.jp/contests/dp/tasks/dp_s
// 所属知识点：数位DP与有限状态；使用模板：DigitDP
// 题意：1..K中数位和能被D整除的数字个数，K可达10000位。
// 转化：数位和只需模D的余数，滚动状态避免把巨大上界转整数。
// 调用：digit_sum(D,1e9+7)，qur(K)后减去0。
// 复杂度：O(|K|*D*10)时间、O(D)空间。
void solve() {
    string K;
    int D;
    cin >> K >> D;
    DigitDP t;
    t.digit_sum(D, 1000000007);
    cout << (t.qur(K) - 1 + 1000000007) % 1000000007 << '\n';
}
