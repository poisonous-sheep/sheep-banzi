// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1920C Partitioning the Array
// 原题：https://codeforces.com/problemset/problem/1920/C
// 所属知识点：同余差与GCD；使用模板：GcdDifference
// 题意：对n的每个因数k将数组分成长度k块，存在m≥2使各块对应位置模m相同则计数。
// 转化：对应位置的相邻块差为a[i]-a[i-k]；它们的GCD不为1正是存在合法模数。
// 调用：partitions(a)，枚举因数并调用stride。
// 复杂度：O(n*tau(n)*log A)时间/O(n)空间。
void solve() {
    int T;
    cin >> T;
    GcdDifference t;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x : a)
            cin >> x;
        cout << t.partitions(a) << '\n';
    }
}
