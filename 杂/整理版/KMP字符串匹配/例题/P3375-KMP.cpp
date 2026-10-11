// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3375 KMP
// 原题：https://www.luogu.com.cn/problem/P3375
// 所属知识点：KMP字符串匹配；使用模板：KMP
// 题意：输出模式串所有出现位置及每个前缀的最长border。
// 转化：重复扫描通过前缀函数复用已知匹配长度。
// 调用：init(s2)，find(s1)，依次输出nxt。
// 复杂度：O(|s1|+|s2|)时间、O(|s2|+匹配数)空间。
void solve() {
    string s, p;
    cin >> s >> p;
    KMP t;
    t.init(p);
    for (int x : t.find(s))
        cout << x << '\n';
    for (int i = 0; i < (int)p.size(); i++)
        cout << t.nxt[i] << " \n"[i + 1 == (int)p.size()];
}
