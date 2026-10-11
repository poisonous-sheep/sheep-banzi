// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC231E Minimal payments
// 原题：https://atcoder.jp/contests/abc231/tasks/abc231_e
// 所属知识点：进位支付与有符号数位；使用模板：CarryDP
// 题意：币值组成整倍数链，买X元物品时支付和找零总币数最少。
// 转化：低位余数只有向下支付和向上进位两种有效选择。
// 调用：读升序币值调用qur(a,X)。
// 复杂度：O(n log n)时间、O(n)状态空间。
void solve() {
    int n, X;
    cin >> n >> X;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    CarryDP t;
    cout << t.qur(a, X) << '\n';
}
