// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC105D Candy Distribution
// 原题：https://atcoder.jp/contests/abc105/tasks/abc105_d
// 所属知识点：前缀关系计数；使用模板：PrefixPairs
// 题意：求数组区间和能被m整除的区间数。
// 转化：两前缀和同余，键为前缀和模m。
// 调用：add空前缀0，逐个取模加入，输出ans。
// 复杂度：期望O(n)时间/O(min(n,m))空间。
void solve() {
    int n, m;
    cin >> n >> m;
    PrefixPairs t;
    t.init(n + 1);
    t.add(0);
    int s = 0;
    while (n--) {
        int x;
        cin >> x;
        s = (s + x) % m;
        t.add(s);
    }
    cout << t.ans << '\n';
}
