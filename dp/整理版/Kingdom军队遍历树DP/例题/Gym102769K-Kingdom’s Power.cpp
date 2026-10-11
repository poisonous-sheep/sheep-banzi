// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// Gym102769K Kingdom’s Power
// 原题：https://codeforces.com/gym/102769/problem/K
// 所属知识点：Kingdom军队遍历树DP；使用模板：KingdomPower
// 题意：根有无限军队，每秒指定一支沿边移动一步，最少多久访问全树。
// 转化：单兵闭合分支每条边往返付2；开放分支可以接已有军队或另从根派兵，三种合并择优。
// 调用：读T及每组n、父数组，run，输出Case #x: ans。
// 复杂度：O(n)时间/O(n)空间。
void solve() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        int n;
        cin >> n;
        KingdomPower t(n);
        for (int u = 2; u <= n; u++)
            cin >> t.fa[u];
        cout << "Case #" << tc << ": " << t.run() << '\n';
    }
}
