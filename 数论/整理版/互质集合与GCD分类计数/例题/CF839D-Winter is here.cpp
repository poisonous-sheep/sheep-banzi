// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF839D Winter is here
// 原题：https://codeforces.com/contest/839/problem/D
// 所属知识点：互质集合与GCD分类计数；使用模板：CoprimeSet
// 题意：累加gcd>1子序列的长度乘gcd。
// 转化：含c个候选的所有子集长度和为c*2^(c-1)；从大到小减掉更大gcd的贡献。
// 调用：构造CoprimeSet后调用weighted，精确类别存exact。
// 复杂度：O(V log V+n)时间、O(V+n)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    CoprimeSet t(a);
    cout << t.weighted() << '\n';
}
