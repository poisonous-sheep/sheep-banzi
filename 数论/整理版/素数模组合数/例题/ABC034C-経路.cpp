// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC034C 経路
// 原题：https://atcoder.jp/contests/abc034/tasks/abc034_c
// 所属知识点：素数模组合数；使用模板：Comb
// 题意：W乘H网格从左上向右下仅向右或下走，求路径数。
// 转化：总步数W+H-2，选W-1步向右。
// 调用：init(W+H-2)，binom(total,W-1)。
// 复杂度：O(W+H)时间与空间。
void solve() {
    int w, h;
    cin >> w >> h;
    Comb c;
    c.init(w + h - 2);
    cout << c.binom(w + h - 2, w - 1) << '\n';
}
