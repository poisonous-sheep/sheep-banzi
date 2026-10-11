// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1720D1 Xor-Subsequence (easy version)
// 原题：https://codeforces.com/problemset/problem/1720/D1
// 所属知识点：异或比较与最高不同位；使用模板：XorCompare
// 题意：ai≤200，选最长子序列，使相邻所选下标i<j满足ai xor j < aj xor i，下标从0起。
// 转化：高于第7位只有下标贡献，间距≥256必然失败；仅枚举最近255个前驱。
// 调用：读T、a，subsequence(a,8)。
// 复杂度：O(256n)时间/O(n)空间。
void solve() {
    int T;
    cin >> T;
    XorCompare t;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x : a)
            cin >> x;
        cout << t.subsequence(a) << '\n';
    }
}
