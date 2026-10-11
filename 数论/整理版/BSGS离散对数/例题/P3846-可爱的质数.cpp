// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3846 可爱的质数
// 原题：https://www.luogu.com.cn/problem/P3846
// 所属知识点：BSGS离散对数；使用模板：BSGS
// 题意：输入p,b,n，求b^x=n mod p。
// 转化：素数模下通常互质，直接用BSGS。
// 调用：solve(b,n,p)，无解输出no solution。
// 复杂度：O(sqrt p log p)时间、O(sqrt p)空间。
void solve() {
    int p, b, n;
    cin >> p >> b >> n;
    BSGS g;
    int ans = g.solve(b, n, p);
    if (ans < 0)
        cout << "no solution\n";
    else
        cout << ans << '\n';
}
