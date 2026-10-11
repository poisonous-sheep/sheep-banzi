// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// Gym102992M Monster Hunter
// 原题：https://codeforces.com/gym/102992/problem/M
// 所属知识点：二状态树形背包；使用模板：BinaryTreeKnapsack
// 题意：有限魔法可无成本杀任意怪，普通杀怪受父亲和存活孩子血量影响，求每个魔法次数的最小总力量。
// 转化：先施放所有魔法；普通点自己的hp付一次，只有父子均普通时，子hp还会在父亲被杀时再付一次。
// 调用：普通cost=hp、魔法cost=0；edge_cost[v][0][0]=hp[v]，run后输出全部k。
// 复杂度：O(n²)时间/空间。
void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        BinaryTreeKnapsack t(n);
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            t.add_edge(p, i);
        }
        for (int i = 1; i <= n; i++) {
            int hp;
            cin >> hp;
            t.cost[i] = {hp, 0};
            t.edge_cost[i][0][0] = hp;
        }
        auto ans = t.run();
        for (int k = 0; k <= n; k++)
            cout << ans[k] << " \n"[k == n];
    }
}
