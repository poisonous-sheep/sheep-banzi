// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// ABC437F Manhattan Christmas Tree 2
// 原题：https://atcoder.jp/contests/abc437/tasks/abc437_f
// 所属知识点：曼哈顿距离坐标旋转；使用模板：Manhattan
// 题意：支持修改一个点坐标，查询下标区间内到指定坐标最远的曼哈顿距离。
// 转化：将Manhattan四个极值作为线段树合并信息，区间极值仍满足旋转距离公式。
// 调用：完整板子附ManhattanSeg；每点change初值；修改change，查询qur(L,R).qur(x,y)。
// 复杂度：O((n+q)log n)时间/O(n)空间。
void solve() {
    int n, q;
    cin >> n >> q;
    ManhattanSeg t(n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        t.change(i, x, y);
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i, x, y;
            cin >> i >> x >> y;
            t.change(i, x, y);
        } else {
            int l, r, x, y;
            cin >> l >> r >> x >> y;
            cout << t.qur(l, r).qur(x, y) << '\n';
        }
    }
}
