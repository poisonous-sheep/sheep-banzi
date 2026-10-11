// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF803F Coprime Subsequences
// 原题：https://codeforces.com/contest/803/problem/F
// 所属知识点：互质集合与GCD分类计数；使用模板：CoprimeSet
// 题意：求gcd为1的非空子序列数。
// 转化：选择下标后顺序唯一，因此子序列数等于下标子集数。每个d的候选有2^cnt[d]-1个。
// 调用：读数组构造CoprimeSet，输出qur。
// 复杂度：O(V log V+n)时间、O(V+n)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    CoprimeSet t(a);
    cout << t.qur() << '\n';
}
