// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3740 贴海报
// 原题：https://www.luogu.com.cn/problem/P3740
// 所属知识点：珂朵莉树；使用模板：ODT
// 题意：海报依次覆盖整数墙面，求最终仍可见的海报数量。
// 转化：每次覆盖就是区间赋值；最终扫描不为0的段收集编号。
// 调用：init(墙长,0)，第i张assign(l,r,i)，遍历odt中的v。
// 复杂度：最坏O(nm)，O(n+m)空间；此题墙长小。
void solve() {
    int n, m;
    cin >> n >> m;
    ODT t(n);
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        t.assign(l, r, i);
    }
    set<int> vis;
    for (auto z : t.odt)
        if (z.v)
            vis.insert(z.v);
    cout << vis.size() << '\n';
}
