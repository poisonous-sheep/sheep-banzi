// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF508D Tanya and Password
// 原题：https://codeforces.com/contest/508/problem/D
// 所属知识点：有向欧拉路径；使用模板：Euler
// 题意：用三字符子串多重集还原原字符串。
// 转化：每个两字符串是节点，三字符串是前两位到后两位的有向边；所有子串恰用一次。
// 调用：字母数字映射62进制节点；run(false)；输出首节点两位，再输出后续节点末位。
// 复杂度：O(n+62^2)时间与空间。
void solve() {
    int n;
    cin >> n;
    string ch = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    auto cv = [&](char c) { return ch.find(c); };
    Euler g;
    g.init(62 * 62);
    while (n--) {
        string s;
        cin >> s;
        int u = cv(s[0]) * 62 + cv(s[1]) + 1, v = cv(s[1]) * 62 + cv(s[2]) + 1;
        g.addedge(u, v);
    }
    if (!g.run(false)) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    int first = g.path[0] - 1;
    cout << ch[first / 62] << ch[first % 62];
    for (int i = 1; i < (int)g.path.size(); i++)
        cout << ch[(g.path[i] - 1) % 62];
    cout << '\n';
}
