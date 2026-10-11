// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4139 上帝与集合的正确用法
// 原题：https://www.luogu.com.cn/problem/P4139
// 所属知识点：扩展欧拉与指数塔；使用模板：PowerTower
// 题意：多组无限2幂塔模p。
// 转化：固定2的无限塔沿phi链递归，指数足够大可加phi。
// 调用：每组calc(p)，缓存phi可复用。
// 复杂度：各phi链试除与快速幂之和。
void solve() {
    int T;
    cin >> T;
    PowerTower tr;
    while (T--) {
        int p;
        cin >> p;
        cout << tr.calc(p) << '\n';
    }
}
