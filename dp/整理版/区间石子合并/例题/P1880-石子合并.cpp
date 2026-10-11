// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1880 石子合并
// 原题：https://www.luogu.com.cn/problem/P1880
// 所属知识点：区间石子合并；使用模板：StoneMerge
// 题意：圆周相邻两堆合并，求最小和最大总代价。
// 转化：复制数组后枚举长度n区间，覆盖全部断环位置；状态合并改min/max。
// 调用：binary(a,true,false)与binary(a,true,true)。
// 复杂度：O(n³)时间、O(n²)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    StoneMerge t;
    cout << t.binary(a, true) << '\n' << t.binary(a, true, true) << '\n';
}
