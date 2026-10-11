// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1966 火柴排队
// 原题：https://www.luogu.com.cn/problem/P1966
// 所属知识点：树状数组；使用模板：BIT
// 题意：两列高度互异的火柴，可相邻交换，先最小化平方距离，再求最少交换数。
// 转化：同秩配对最小化平方差；把第一列每个秩映射到第二列对应位置，最少相邻交换就是该位置排列逆序数。
// 调用：排序两列(value,index)，构造位置排列，用BIT频率统计先前更大元素，结果模100000000-3。
// 复杂度：O(n log n)时间/O(n)空间。
void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i].first;
        b[i].second = i + 1;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        p[a[i].second] = b[i].second;
    BIT<int> t(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + i - t.sum(p[i])) % (100000000 - 3);
        t.add(p[i], 1);
    }
    cout << ans << '\n';
}
