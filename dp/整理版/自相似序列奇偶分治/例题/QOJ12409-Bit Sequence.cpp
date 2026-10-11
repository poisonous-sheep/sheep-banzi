// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// QOJ12409 Bit Sequence
// 原题：https://qoj.ac/problem/12409
// 所属知识点：自相似序列奇偶分治；使用模板：SelfSimilar
// 题意：统计0..L中，popcount(x+i)奇偶序列与给定模式相符的x个数。
// 转化：Thue-Morse的偶数位置继承，奇数位置取反；起点奇偶两类各自将模式压半。
// 调用：每组init清memo，整数数组转01字符串，calc(L,s)。
// 复杂度：记忆化约O(m log² L)时间，上界状态空间同阶。
void solve() {
    int T;
    cin >> T;
    SelfSimilar t;
    while (T--) {
        int m, L;
        cin >> m >> L;
        string s;
        while (m--) {
            int x;
            cin >> x;
            s.push_back('0' + x);
        }
        t.init();
        cout << t.calc(L, s) << '\n';
    }
}
