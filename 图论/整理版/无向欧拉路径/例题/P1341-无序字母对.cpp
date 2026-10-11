// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1341 无序字母对
// 原题：https://www.luogu.com.cn/problem/P1341
// 所属知识点：无向欧拉路径；使用模板：Euler
// 题意：把无序字母对拼成字典序最小字符串，每对用一次。
// 转化：字母是节点，字母对是无向边；字符ASCII顺序就是要求的字典序。
// 调用：字符号加1避免节点0，run后逐点输出字符。
// 复杂度：O(m log m+128)时间、O(m+128)空间。
void solve() {
    int m;
    cin >> m;
    Euler g;
    g.init(128);
    while (m--) {
        string s;
        cin >> s;
        g.addedge((unsigned char)s[0] + 1, (unsigned char)s[1] + 1);
    }
    if (!g.run()) {
        cout << "No Solution\n";
        return;
    }
    for (int u : g.path)
        cout << char(u - 1);
    cout << '\n';
}
