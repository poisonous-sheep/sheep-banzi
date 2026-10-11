// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1403 约数研究
// 原题：https://www.luogu.com.cn/problem/P1403
// 所属知识点：整除分块；使用模板：FloorBlock
// 题意：求1..n每个数的约数个数之和。
// 转化：交换求和得到sum floor(n/d)，按相同商合并。
// 调用：count_divisors_sum(n)。
// 复杂度：O(sqrt n)时间、O(1)空间。
void solve() {
    int n;
    cin >> n;
    FloorBlock f;
    cout << f.count_divisors_sum(n) << '\n';
}
