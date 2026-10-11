// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1453 城市环路
// 原题：https://www.luogu.com.cn/problem/P1453
// 所属知识点：基环树最大权独立集；使用模板：Knight
// 题意：城市构成无向基环图，不能选相邻城市建店，求利润。
// 转化：无向唯一环可定向为函数图，之后独立集模型与骑士相同。
// 调用：0基城市转1基，orient(edges)，run后乘系数k，保留1位小数。
// 复杂度：O(n)时间/空间。
void solve() {
    int n;
    cin >> n;
    Knight t(n);
    for (int i = 1; i <= n; i++)
        cin >> t.val[i];
    vector<array<int, 3>> e(n);
    for (auto &z : e) {
        cin >> z[0] >> z[1];
        z[0]++;
        z[1]++;
        z[2] = 0;
    }
    long double k;
    cin >> k;
    t.orient(e);
    cout << fixed << setprecision(1) << t.run() * k << '\n';
}
