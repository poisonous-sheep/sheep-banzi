// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4766 Outer space invaders
// 原题：https://www.luogu.com.cn/problem/P4766
// 所属知识点：区间强制对象分治；使用模板：IntervalSplit
// 题意：敌人在各时间区间出现，一次半径R的冲击波可击中当前距离≤R的敌人，费用R，求全灭最小费用。
// 转化：先考虑最远敌人被杀时刻k；该击可消灭所有跨k敌人，余下左右期限区间独立。
// 调用：读T及期限a,b和距离d，init_enemies，run。
// 复杂度：O(n³)时间/O(n²)空间，离散时间点≤2n。
void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<IntervalSplit::info> a(n);
        for (auto &z : a)
            cin >> z.l >> z.r >> z.w;
        IntervalSplit t;
        t.init_enemies(a);
        cout << t.run() << '\n';
    }
}
