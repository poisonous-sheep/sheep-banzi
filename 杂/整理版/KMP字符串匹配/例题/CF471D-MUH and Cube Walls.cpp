// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF471D MUH and Cube Walls
// 原题：https://codeforces.com/contest/471/problem/D
// 所属知识点：KMP字符串匹配；使用模板：KMP
// 题意：允许整体上下平移，统计目标高度序列出现次数。
// 转化：两序列可整体平移等价相邻差相同，转成整数序列匹配。
// 调用：w=1直接答n；否则差分后init和find。
// 复杂度：O(n+w)时间与O(n+w)空间。
void solve() {
    int n, w;
    cin >> n >> w;
    vector<int> a(n), b(w);
    for (int &x : a)
        cin >> x;
    for (int &x : b)
        cin >> x;
    if (w == 1) {
        cout << n << '\n';
        return;
    }
    vector<int> x, y;
    for (int i = 1; i < n; i++)
        x.push_back(a[i] - a[i - 1]);
    for (int i = 1; i < w; i++)
        y.push_back(b[i] - b[i - 1]);
    KMP t;
    t.init(y);
    cout << t.find(x).size() << '\n';
}
