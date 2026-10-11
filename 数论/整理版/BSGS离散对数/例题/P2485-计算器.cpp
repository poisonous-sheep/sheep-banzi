// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2485 计算器
// 原题：https://www.luogu.com.cn/problem/P2485
// 所属知识点：BSGS离散对数；使用模板：BSGS
// 题意：三类操作分别为快速幂、线性同余、离散对数。
// 转化：对模式3用BSGS；其他模式调用板子内的powmod和Exgcd。
// 调用：按k选择powmod、ex.linear、solve；无解按题面字符串输出。
// 复杂度：模式3每组O(sqrt p log p)，其他O(log p)。
void solve() {
    int T, k;
    cin >> T >> k;
    BSGS g;
    while (T--) {
        int y, z, p;
        cin >> y >> z >> p;
        int ans = k == 1   ? g.powmod(y, z, p)
                  : k == 2 ? g.ex.linear(y, z, p)
                           : g.solve(y, z, p);
        if (ans < 0)
            cout << "Orz, I cannot find x!\n";
        else
            cout << ans << '\n';
    }
}
