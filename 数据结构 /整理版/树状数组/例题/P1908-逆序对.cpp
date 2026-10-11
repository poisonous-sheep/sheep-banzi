// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1908 逆序对
// 原题：https://www.luogu.com.cn/problem/P1908
// 所属知识点：树状数组；使用模板：BIT
// 题意：统计i<j且a[i]>a[j]的数对。
// 转化：按下标插入频率，已出现数中大于当前值的数量就是新增逆序对。
// 调用：离散化；ans+=已插入数-sum(pos)，再add(pos,1)。
// 复杂度：O(n log n)时间、O(n)空间。
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), v;
    for (auto &x : a)
        cin >> x;
    v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    BIT<int> bit(v.size());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int p = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        ans += i - bit.sum(p);
        bit.add(p, 1);
    }
    cout << ans << '\n';
}
