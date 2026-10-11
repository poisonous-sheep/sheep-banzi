// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF896C Willem Chtholly and Seniorious
// 原题：https://codeforces.com/contest/896/problem/C
// 所属知识点：珂朵莉树；使用模板：ODT
// 题意：生成数组和四种随机操作，维护增加、赋值、第k小、幂和。
// 转化：随机操作与大量赋值符合ODT常见使用条件；区间长度作为元素重数。
// 调用：按原题顺序调用rng生成全部参数，依操作调用add、assign、kth、qur。
// 复杂度：最坏O(nm log n)，随机数据通常区间数较少；O(n)。
void solve() {
    int n, m, seed, vmax;
    cin >> n >> m >> seed >> vmax;
    auto rnd = [&]() {
        int ret = seed;
        seed = (seed * 7 + 13) % 1000000007;
        return ret;
    };
    ODT t(n);
    for (int i = 1; i <= n; i++)
        t.assign(i, i, rnd() % vmax + 1);
    for (int i = 0; i < m; i++) {
        int op = rnd() % 4 + 1, l = rnd() % n + 1, r = rnd() % n + 1;
        if (l > r)
            swap(l, r);
        int x = op == 3 ? rnd() % (r - l + 1) + 1 : rnd() % vmax + 1;
        if (op == 1)
            t.add(l, r, x);
        if (op == 2)
            t.assign(l, r, x);
        if (op == 3)
            cout << t.kth(l, r, x) << '\n';
        if (op == 4) {
            int y = rnd() % vmax + 1;
            cout << t.qur(l, r, x, y) << '\n';
        }
    }
}
