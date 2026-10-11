// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3188 梦幻岛宝珠
// 原题：https://www.luogu.com.cn/problem/P3188
// 所属知识点：数位背包；使用模板：DigitKnapsack
// 题意：重量很大但w=a*2^b且a<=10的0/1背包。
// 转化：Σ奇数部分<=10n，使容量与2^30脱钩。
// 调用：每组建立对象add全部物品，qur(W)，读到-1 -1终止。
// 复杂度：O((63+n)*10n)时间、O(n)量级状态空间。
void solve() {
    int n, W;
    while (cin >> n >> W && n != -1) {
        DigitKnapsack t;
        while (n--) {
            int w, v;
            cin >> w >> v;
            t.add(w, v);
        }
        cout << t.qur(W) << '\n';
    }
}
