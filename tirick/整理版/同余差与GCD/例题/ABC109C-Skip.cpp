// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC109C Skip
// 原题：https://atcoder.jp/contests/abc109/tasks/abc109_c
// 所属知识点：同余差与GCD；使用模板：GcdDifference
// 题意：从X出发每次左右移动固定D，访问所有给定城市，求最大的正D。
// 转化：每个城市与X的差必须是D整数倍，最大D是这些差的GCD。
// 调用：from(a,X)。
// 复杂度：O(n log A)时间/O(n)空间（保存输入）。
void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int &y : a)
        cin >> y;
    GcdDifference t;
    cout << t.from(a, x) << '\n';
}
