// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC247F Cards
// 原题：https://atcoder.jp/contests/abc247/tasks/abc247_f
// 所属知识点：置换环分解；使用模板：Permutation
// 题意：每张卡两面分别来自两个排列，选卡使1..n每个数至少出现在一张所选卡的任一面上，计数。
// 转化：用排列p的逆位置把卡映射成i→pos[q[i]]的置换。每个数是相邻两卡共享的环边，选卡等价于环顶点覆盖。长度L方案F[L-1]+F[L+1]。
// 调用：构造a，init，cover_ways；自环专门处理。
// 复杂度：O(n)时间/O(n)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1), pos(n + 1), a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    for (int i = 1, q; i <= n; i++) {
        cin >> q;
        a[i] = pos[q];
    }
    Permutation t;
    t.init(a);
    cout << t.cover_ways() << '\n';
}
