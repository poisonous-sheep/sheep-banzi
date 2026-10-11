// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// AGC038C LCMs
// 原题：https://atcoder.jp/contests/agc038/tasks/agc038_c
// 所属知识点：LCM矩形与集合求和；使用模板：LCMSum
// 题意：求数组中所有i<j的lcm(ai,aj)之和，模998244353。
// 转化：倍数元素的单位权重和S(d)替代矩形三角数；同一h反演后用平方统计有序对，再扣对角除2。
// 调用：init(max a,998244353)，pairs(a)。
// 复杂度：O(V log V+n)时间，O(V+n)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    LCMSum t(*max_element(a.begin(), a.end()), 998244353);
    cout << t.pairs(a) << '\n';
}
