// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1972 HH的项链
// 原题：https://www.luogu.com.cn/problem/P1972
// 所属知识点：离线二维数点；使用模板：RectangleCounter
// 题意：询问区间内不同颜色数。
// 转化：颜色只统计区间内第一次出现的位置；位置i贡献当且仅当pre[i]<l且l<=i<=r。映射为点(pre[i],i)。
// 调用：读数组时用map保存上次位置并add；ask(0,l,l-1,r)。
// 复杂度：O((n+m)log(n+m))时间与O(n+m)空间。
void solve() {
    int n;
    cin >> n;
    RectangleCounter t;
    map<int, int> pre;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        t.add(pre[x], i);
        pre[x] = i;
    }
    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        t.ask(0, l, l - 1, r);
    }
    for (int x : t.run())
        cout << x << '\n';
}
