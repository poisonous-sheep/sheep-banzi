// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF276D Little Girl and Maximum XOR
// 原题：https://codeforces.com/problemset/problem/276/D
// 所属知识点：异或比较与最高不同位；使用模板：XorCompare
// 题意：从整数区间[l,r]选两数使异或最大。
// 转化：l,r最高不同位以下可以构造全1；最高不同位以上必须一致。
// 调用：max_xor(l,r)。
// 复杂度：O(log r)时间/O(1)空间。
void solve() {
    int l, r;
    cin >> l >> r;
    XorCompare t;
    cout << t.max_xor(l, r) << '\n';
}
