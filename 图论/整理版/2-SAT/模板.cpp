#include <bits/stdc++.h>
using namespace std;
#define int long long

// 2-SAT：二元布尔变量OR子句与蕴含约束；内部独立Tarjan SCC。
// O(变量数+子句数)时间与空间。
struct SCC {
    // 以下顶点表均由init按n+1项assign重建；顶点下标1..n，0号预留不用。
    // 内层邻接位置从0开始，init清空旧边；标记/时间戳/归属表清0。
    int n;   // 顶点数，n>=1；顶点编号为 1..n。
    int idx; // DFS 时钟，范围 [0,n]；每首次访问一个点加 1。
    int cnt; // SCC 数，范围 [0,n]；按弹栈先后编号。

    // e：二维变长邻接表；e[u][j] 为 u 的第 j 条出边终点。
    // u=1..n，j=0..e[u].size()-1；init 中 clear；允许重边、自环。
    vector<vector<int>> e;
    // dfn：一维；dfn[u] 为首次访问时间，0 表示未访问；init 清 0；有效值 1..n。
    vector<int> dfn;
    // low：一维；low[u] 为子树按 Tarjan 规则能追溯到的最早未封闭时间戳。
    // 下标 1..n；init 清 0；首次访问置 dfn[u]，随后取 min。
    vector<int> low;
    // ins：一维；ins[u] 为 u 是否仍在 Tarjan 栈中；init 清0，标记取0/1，入栈置 true，弹栈置 false。
    vector<int> ins;
    // bel：一维；bel[u] 为 SCC 编号 1..cnt；init 清 0；0 表示尚未分配。
    vector<int> bel;
    // stk：一维栈，元素为顶点编号 1..n；init 弹空；最多存 n 个点。
    stack<int> stk;
    // scc：二维变长表；scc[c-1] 为 SCC c 的全部原图顶点；init clear；总成员数 n。
    vector<vector<int>> scc;

    // init(n_)：参数为顶点数；返回 void；清图和 Tarjan 状态。
    // 前提：n_>=1，下一步重新加边；首次初始化时间O(n_)；复用对象还需销毁旧图的邻接元素。
    void init(int n_) {
        n = n_;
        idx = cnt = 0;
        e.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        ins.assign(n + 1, 0);
        bel.assign(n + 1, 0);
        while (!stk.empty())
            stk.pop();
        scc.clear();
    }

    // dfs(u)：u 为当前顶点；返回 void；递归求 SCC 并填写 bel、scc。
    // 前提：图已建好，dfn[u]==0；一次 DFS 为 O(所访问顶点+扫描边)，全图 O(n+m)。
    void dfs(int u) {
        dfn[u] = low[u] = ++idx;
        ins[u] = true;
        stk.push(u);
        for (int v : e[u]) { // v：出边终点，范围 1..n。
            if (!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (ins[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            ++cnt;
            vector<int> c; // 一维临时点集，初始为空；存当前 SCC 顶点，大小至少 1。
            while (true) {
                int v = stk.top(); // v：当前弹出顶点，1..n；最后一次必为 u。
                stk.pop();
                ins[v] = false;
                bel[v] = cnt;
                c.push_back(v);
                if (v == u)
                    break;
            }
            scc.push_back(c);
        }
    }

    // run()：无参数，返回 void；遍历 DFS 森林，完成全图 SCC。
    // 前提：已 init 并加边，尚未运行；时间 O(n+m)，递归栈最坏 O(n)。
    void run() {
        for (int u = 1; u <= n; u++)
            if (!dfn[u])
                dfs(u);
    }

    // addedge(u,v)：参数为有向边起终点1..n；返回void；前提已init且尚未run。
    // 作用：只封装原PPT邻接表push_back；摊还时间O(1)。
    void addedge(int u, int v) {
        e[u].push_back(v);
    }
};
struct TwoSAT {
    // scc：内部SCC对象，独立保存2*vars个命题点的邻接表、dfn/low/bel与点栈。
    // init_sat调用scc.init清图；调用前提2*vars不溢出int，不与外部SCC对象共享状态。
    SCC scc;

    int vars; // 布尔变量数，要求 1<=vars 且 2*vars不溢出int；Tarjan 的 n=2*vars。
    // ans：一维，ans[i] 为变量 i 的值 0/1；下标 1..vars。
    // init_sat 以 vars+1 项清 0；求解失败时不可使用 ans。
    vector<int> ans;

    // id(i,value)：变量 i 的取值命题编号；返回 1..2*vars 的 int。
    // 前提 i=1..vars，value=0/1；作用：统一映射；时间 O(1)。
    int id(int i, int value) {
        return i + value * vars;
    }
    // neg(u)：u 为命题点；返回同变量相反取值的命题点；前提 u=1..2*vars；O(1)。
    int neg(int u) {
        return u <= vars ? u + vars : u - vars;
    }
    // init_sat(k)：k 为布尔变量数；返回 void；清 Tarjan 图并初始化答案。
    // 前提 k>=1且2*k+1不溢出int，随后重新加子句；时间 O(k)。
    void init_sat(int k) {
        vars = k;
        scc.init(2 * vars);
        ans.assign(vars + 1, 0);
    }
    // add_or(a,A,b,B)：加入 (变量a=A) OR (变量b=B)；返回 void。
    // 前提 a/b=1..vars，A/B=0/1，已 init_sat；摊还 O(1)。
    void add_or(int a, int A, int b, int B) {
        scc.e[id(a, A ^ 1)].push_back(id(b, B));
        scc.e[id(b, B ^ 1)].push_back(id(a, A));
    }
    // imply(u,v)：加入命题 u 推出 v，及其逆否；返回 void。
    // 前提 u/v=1..2*vars；作用：保证蕴含图成对建边；摊还 O(1)。
    void imply(int u, int v) {
        scc.e[u].push_back(v);
        scc.e[neg(v)].push_back(neg(u));
    }
    // solve_sat()：无参数；返回是否可行；成功时写 ans。
    // 前提尚未 run，且使用第1.2节 Tarjan 的反拓扑 SCC 编号；时间 O(vars+子句数)。
    bool solve_sat() {
        scc.run();
        for (int i = 1; i <= vars; i++) { // i：布尔变量编号。
            if (scc.bel[id(i, 0)] == scc.bel[id(i, 1)])
                return false;
            ans[i] = scc.bel[id(i, 1)] < scc.bel[id(i, 0)];
        }
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    TwoSAT sat;
    sat.init_sat(n);
    while (m--) {
        int a, A, b, B;
        cin >> a >> A >> b >> B;
        sat.add_or(a, A, b, B);
    }
    if (!sat.solve_sat()) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    cout << "POSSIBLE\n";
    for (int i = 1; i <= n; i++)
        cout << sat.ans[i] << (i == n ? '\n' : ' ');
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}
