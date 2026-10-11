// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC139F Engines
// 原题：https://atcoder.jp/contests/abc139/tasks/abc139_f
// 所属知识点：极角排序；使用模板：PolarSort
// 题意：选择若干向量，使和的长度最大。
// 转化：最优向量集合可取为沿某个方向点积非负的半平面；极角序中是连续区间。枚举所有圆周连续区间必覆盖最优。
// 调用：过滤零向量，run排序，枚举起点并累加最多n个向量。
// 复杂度：O(n²+n log n)时间、O(n)空间。
void solve() {
    int n;
    cin >> n;
    vector<P> a;
    while (n--) {
        P p;
        p.read();
        if (p.abs2() > 0)
            a.push_back(p);
    }
    PolarSort t;
    t.run(a);
    n = a.size();
    db ans = 0;
    for (int i = 0; i < n; i++) {
        P s;
        for (int k = 0; k < n; k++) {
            s = s + a[(i + k) % n];
            ans = max(ans, s.abs2());
        }
    }
    cout << fixed << setprecision(12) << sqrtl(ans) << '\n';
}
