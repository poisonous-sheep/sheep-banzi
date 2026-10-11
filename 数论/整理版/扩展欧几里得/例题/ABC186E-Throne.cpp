// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC186E Throne
// 原题：https://atcoder.jp/contests/abc186/tasks/abc186_e
// 所属知识点：扩展欧几里得；使用模板：Exgcd
// 题意：从位置S每次走K，最少几次回到模N的0点。
// 转化：K*x=-S mod N，gcd整除目标才有解。
// 调用：每组linear(K,-S,N)。
// 复杂度：O(T log N)时间、O(log N)空间。
void solve() {
    int T;
    cin >> T;
    Exgcd ex;
    while (T--) {
        int n, s, k;
        cin >> n >> s >> k;
        cout << ex.linear(k, -s, n) << '\n';
    }
}
