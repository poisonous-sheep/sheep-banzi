// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2424 约数和
// 原题：https://www.luogu.com.cn/problem/P2424
// 所属知识点：整除分块；使用模板：FloorBlock
// 题意：求区间[x,y]每个数的约数和之和。
// 转化：前缀=Σ d*floor(n/d)，块内d的和用等差数列。
// 调用：divisor_sum(y)-divisor_sum(x-1)，print宽整数。
// 复杂度：O(sqrt y)时间、O(1)额外空间。
void solve() {
    int x, y;
    cin >> x >> y;
    FloorBlock f;
    f.print(f.divisor_sum(y) - f.divisor_sum(x - 1));
    cout << '\n';
}
