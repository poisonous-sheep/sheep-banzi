// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1207F Remainder Problem
// 原题：https://codeforces.com/problemset/problem/1207/F
// 所属知识点：步长根号分治；使用模板：SqrtDivide
// 题意：单点增加，查询所有下标模x等于y的位置和。
// 转化：小模数一次修改影响B个桶，大模数查询最多n/B个位置。
// 调用：init(500000)，操作1用change，操作2用qur。
// 复杂度：O(q sqrt N)时间、O(N)空间。
void solve() {
    int q;
    cin >> q;
    SqrtDivide t(500000);
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
            t.change(x, y);
        else
            cout << t.qur(x, y) << '\n';
    }
}
