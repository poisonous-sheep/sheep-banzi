// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3455 Problem b
// 原题：https://www.luogu.com.cn/problem/P3455
// 所属知识点：莫比乌斯反演与线性筛；使用模板：Mobius
// 题意：统计两个闭区间内gcd=k的数对。
// 转化：将区间容斥为四个前缀矩形，再缩放为互质计数。
// 调用：读取a,b,c,d,k，计算F(b,d)-F(a-1,d)-F(b,c-1)+F(a-1,c-1)。
// 复杂度：O(N+T sqrt N)时间、O(N+T)空间。
void solve() {
    int T;
    cin >> T;
    vector<array<int, 5>> q(T);
    int N = 0;
    for (auto &z : q) {
        for (int &x : z)
            cin >> x;
        N = max(N, min(z[1] / z[4], z[3] / z[4]));
    }
    Mobius t(N);
    for (auto z : q) {
        auto F = [&](int a, int b) { return t.coprime(a / z[4], b / z[4]); };
        cout << F(z[1], z[3]) - F(z[0] - 1, z[3]) - F(z[1], z[2] - 1) +
                    F(z[0] - 1, z[2] - 1)
             << '\n';
    }
}
