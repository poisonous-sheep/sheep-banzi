// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// DP_N Slimes
// 原题：https://atcoder.jp/contests/dp/tasks/dp_n
// 所属知识点：区间石子合并；使用模板：StoneMerge
// 题意：相邻两堆合并，总代价最小。
// 转化：最后一次合并将区间分为左右两堆，枚举最后断点。
// 调用：读a后binary(a)。
// 复杂度：O(n³)时间、O(n²)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    StoneMerge t;
    cout << t.binary(a) << '\n';
}
