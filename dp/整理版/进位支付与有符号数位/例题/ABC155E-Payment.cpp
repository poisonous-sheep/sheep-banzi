// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC155E Payment
// 原题：https://atcoder.jp/contests/abc155/tasks/abc155_e
// 所属知识点：进位支付与有符号数位；使用模板：CarryDP
// 题意：币值为10的幂，巨大十进制金额最少支付及找零币数。
// 转化：不能转long long，直接滚动“当前前缀付精确值/付前缀+1”的两个状态。
// 调用：调用digits(N,10)。
// 复杂度：O(|N|)时间、O(1)空间。
void solve() {
    string N;
    cin >> N;
    CarryDP t;
    cout << t.digits(N, 10) << '\n';
}
