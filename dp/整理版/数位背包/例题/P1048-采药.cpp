// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1048 采药
// 原题：https://www.luogu.com.cn/problem/P1048
// 所属知识点：数位背包；使用模板：DigitKnapsack
// 题意：每株草药只能采一次，限定时间内最大收益。
// 转化：普通0/1背包也可按体积幂分组；容量小会把LIM进一步截到W。
// 调用：输入先T后M；逐个add(时间,价值)，qur(T)。
// 复杂度：O((63+M)*min(T,Σodd(w)))时间、O(T+M)空间。
void solve() {
    int T, M;
    cin >> T >> M;
    DigitKnapsack t;
    while (M--) {
        int w, v;
        cin >> w >> v;
        t.add(w, v);
    }
    cout << t.qur(T) << '\n';
}
