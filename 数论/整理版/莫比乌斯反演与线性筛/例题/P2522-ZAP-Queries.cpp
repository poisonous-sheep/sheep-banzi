// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2522 ZAP-Queries
// 原题：https://www.luogu.com.cn/problem/P2522
// 所属知识点：莫比乌斯反演与线性筛；使用模板：Mobius
// 题意：统计1..a和1..b中gcd(x,y)=d的数对。
// 转化：同时除以d，转为互质矩形计数。
// 调用：离线读多组以求最大min(a/d,b/d)，init后coprime。
// 复杂度：O(N+T sqrt N)时间、O(N+T)空间。
void solve() {
    int T;
    cin >> T;
    vector<array<int, 3>> q(T);
    int N = 0;
    for (auto &z : q) {
        cin >> z[0] >> z[1] >> z[2];
        N = max(N, min(z[0] / z[2], z[1] / z[2]));
    }
    Mobius t(N);
    for (auto z : q)
        cout << t.coprime(z[0] / z[2], z[1] / z[2]) << '\n';
}
