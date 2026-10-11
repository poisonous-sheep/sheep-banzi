// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF284A Cows and Primitive Roots
// 原题：https://codeforces.com/problemset/problem/284/A
// 所属知识点：原根；使用模板：PrimitiveRoot
// 题意：素数p下有多少个原根。
// 转化：枚举所有原根并计数；p小，能展示判定与构造接口。
// 调用：all(p).size()；也可用phi(phi(p))验证数量。
// 复杂度：O(p log p+找根耗时)时间、O(p)空间。
void solve() {
    int p;
    cin >> p;
    PrimitiveRoot g;
    cout << g.all(p).size() << '\n';
}
