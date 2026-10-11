// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P3201 梦幻布丁
// 原题：https://www.luogu.com.cn/problem/P3201
// 所属知识点：启发式合并；使用模板：SmallMerge
// 题意：把一种颜色的全部位置改色，并查询颜色段数。
// 转化：改色等价合并位置集合，段数只在搬运位置两侧变化。
// 调用：离线读取操作以压缩所有颜色；build、change，查询segments。
// 复杂度：O((n+q)log(n+q)+n log n)时间，O(n+q)空间。
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), all;
    for (int i = 1; i <= n; i++)
        cin >> a[i], all.push_back(a[i]);
    struct op {
        int t, x, y;
    };
    vector<op> q(m);
    for (auto &z : q) {
        cin >> z.t;
        if (z.t == 1) {
            cin >> z.x >> z.y;
            all.push_back(z.x);
            all.push_back(z.y);
        }
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    auto id = [&](int x) {
        return lower_bound(all.begin(), all.end(), x) - all.begin() + 1;
    };
    for (int i = 1; i <= n; i++)
        a[i] = id(a[i]);
    SmallMerge t(n);
    t.build(a, all.size());
    for (auto z : q)
        if (z.t == 1)
            t.change(id(z.x), id(z.y));
        else
            cout << t.segments << '\n';
}
