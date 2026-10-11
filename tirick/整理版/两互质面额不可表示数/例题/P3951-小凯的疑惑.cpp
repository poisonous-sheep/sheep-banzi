// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3951 小凯的疑惑
// 原题：https://www.luogu.com.cn/problem/P3951
// 所属知识点：两互质面额不可表示数；使用模板：Frobenius
// 题意：两种无限互质金币面额，求不能支付的最高价格。
// 转化：每个模a余数由0..a-1个b恰好遍历；每个余数类最高空缺在其最小可表示数之前一个a，最大值ab-a-b。
// 调用：maximum(a,b)，题目保证存在正数不可表示。
// 复杂度：O(log min(a,b))时间/O(1)空间（含gcd断言）。
void solve() {
    int a, b;
    cin >> a >> b;
    Frobenius t;
    cout << t.maximum(a, b) << '\n';
}
