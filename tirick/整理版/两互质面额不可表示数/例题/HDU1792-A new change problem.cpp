// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// HDU1792 A new change problem
// 原题：https://acm.hdu.edu.cn/showproblem.php?pid=1792
// 所属知识点：两互质面额不可表示数；使用模板：Frobenius
// 题意：两种互质正面额，求最大不可表示金额及不可表示正金额个数。
// 转化：最高空缺公式给最大值；每个余数类空缺求和给(a-1)(b-1)/2，补充计数应用。
// 调用：循环到EOF读a,b，输出maximum和count。原站本次无法访问，输入输出格式待原站复核。
// 复杂度：O(log min(a,b))时间/O(1)空间。
void solve() {
    int a, b;
    Frobenius t;
    while (cin >> a >> b)
        cout << t.maximum(a, b) << ' ' << t.count(a, b) << '\n';
}
