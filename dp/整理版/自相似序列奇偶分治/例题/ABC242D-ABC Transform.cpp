// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC242D ABC Transform
// 原题：https://atcoder.jp/contests/abc242/tasks/abc242_d
// 所属知识点：自相似序列奇偶分治；使用模板：SelfSimilar
// 题意：ABC字符同时替换t轮后，查询第k个字符，t可能很大。
// 转化：每个字符生成左右两子字符，0基位置的奇偶决定对子字符编号增加1或2；逆向回父位置。
// 调用：将k转0基，transform(S,t,k-1)，返回值+A。
// 复杂度：每询问O(min(t,log k))时间与递归空间。
void solve() {
    string s;
    int q;
    cin >> s >> q;
    SelfSimilar t;
    while (q--) {
        int time, k;
        cin >> time >> k;
        cout << char('A' + t.transform(s, time, k - 1)) << '\n';
    }
}
