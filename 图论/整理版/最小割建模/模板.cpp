#include <bits/stdc++.h>
using namespace std;
#define int long long

// 最小割建模：复用Dinic，支持最大权闭合子图、二元选择与二分图最大权独立集。
// 最大流一般O(V^2 E)，源侧恢复O(V+E)；空间O(V+E)。
template <typename T> struct FlowGraph {
    int s, t; // 源/汇编号1..vtot，要求s!=t；init赋值。
    int vtot; // 顶点总数，>=1；包含全部辅助节点。
    int etot; // 已存残量边数，等于e.size()，始终偶数；边号须在int范围内；init清0。
    // head：一维vector，init分配vtot+1项，下标1..vtot；邻接链首边编号，-1为空；init置-1。
    vector<int> head;
    // dis：一维vector，init分配vtot+1项并清0；下标1..vtot；BFS层数，0未访问，源为1；DFS死点置-1；每次bfs清0。
    vector<int> dis;
    // cur：一维vector，init分配vtot+1项并置-1；下标1..vtot；当前弧下标或-1；每次bfs由head复制，DFS沿链推进。
    vector<int> cur;
    struct edge {
        int v;   // 边终点，1..vtot。
        int nxt; // 同起点的下一边编号，-1或0..etot-1；由addedge填写。
        T f;     // 当前残量，>=0；正向初始为输入容量，反向初始0。
    };
    // e：一维动态边表，下标0..etot-1；配对边i^1。
    // init执行e.clear并令etot=0；addedge成对push_back，不提前resize占用边号。
    vector<edge> e;

    // init(s_,t_,vtot_)：设置源汇与点数；返回void；清边数与邻接链。
    // 前提合法编号、s_!=t_，随后重新建图；首次时间O(vtot_)；重建还包括清除旧边。
    void init(int s_, int t_, int vtot_) {
        s = s_;
        t = t_;
        vtot = vtot_;
        etot = 0; // 多次建图必须清etot。
        head.assign(vtot + 1, -1);
        dis.assign(vtot + 1, 0);
        cur.assign(vtot + 1, -1);
        e.clear();
    }
    // addedge(u,v,f)：加入原始有向边及撤销边；返回void；两次push_back摊还时间O(1)。
    // 前提u/v=1..vtot，f>=0，边号及etot不溢出int；原容量需另存时由调用方记录。
    void addedge(int u, int v, T f) {
        e.push_back({v, head[u], f});
        head[u] = etot++;
        e.push_back({u, head[v], 0});
        head[v] = etot++;
    }
    // bfs()：无参数；返回残量图中汇是否可达；完成分层并重置cur。
    // 前提图已建好或上轮增广完成；时间O(vtot+etot)。
    bool bfs() {
        for (int i = 1; i <= vtot; i++) {
            dis[i] = 0;
            cur[i] = head[i];
        }
        queue<int> q; // 一维BFS队列，初始空；存顶点1..vtot，每点至多入队一次。
        q.push(s);
        dis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();                                       // u：当前扩展顶点，1..vtot。
            for (int i = head[u]; i != -1; i = e[i].nxt) { // i：当前残量边编号。
                if (e[i].f > 0 && dis[e[i].v] == 0) {
                    int v = e[i].v; // v：当前可达边终点，1..vtot。
                    dis[v] = dis[u] + 1;
                    if (v == t)
                        return true;
                    q.push(v);
                }
            }
        }
        return false;
    }
    // dfs(u,m)：u当前点；m为本次允许送出的剩余流量，m>0；返回实际送出量T。
    // 作用：按分层图多路增广；前提bfs成功，cur已重置；一轮阻塞流一般O(VE)。
    T dfs(int u, T m) {
        if (u == t)
            return m;
        T flow = 0; // 本次从u成功送出的总量，0..初始m。
        for (int i = cur[u]; i != -1; cur[u] = i = e[i].nxt) {
            // i：当前弧；保留PPT的cur推进方式，送满本次额度时不前移。
            if (e[i].f > 0 && dis[e[i].v] == dis[u] + 1) {
                T f = dfs(e[i].v, min(m, e[i].f)); // 实际成功增广量，0..min(m,残量)。
                e[i].f -= f;
                e[i ^ 1].f += f;
                m -= f;
                flow += f;
                if (m == 0)
                    break;
            }
        }
        if (flow == 0)
            dis[u] = -1;
        return flow;
    }
    // dinic()：无参数；返回本次新增最大流T；作用：反复分层并求阻塞流。
    // 前提合法源汇、图已建好、总流量不溢出；一般时间O(Vnet²*Enet)，空间O(Vnet+Enet)，额外递归栈O(Vnet)。
    T dinic() {
        T flow = 0; // 本次调用新增流量，init后首次调用即总最大流。
        while (bfs())
            flow += dfs(s, numeric_limits<T>::max());
        return flow;
    }
    vector<int> cut_side() {
        vector<int> vis(vtot + 1);
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i != -1; i = e[i].nxt)
                if (e[i].f > 0 && !vis[e[i].v]) {
                    vis[e[i].v] = 1;
                    q.push(e[i].v);
                }
        }
        return vis;
    }
};
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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    int total = 0;
    for (auto &row : a)
        for (int &x : row) {
            cin >> x;
            total += x;
        }
    int s = n * m + 1, t = s + 1;
    FlowGraph<int> g;
    g.init(s, t, t);
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int u = i * m + j + 1;
            if ((i + j) % 2 == 0) {
                g.addedge(s, u, a[i][j]);
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    if (0 <= x && x < n && 0 <= y && y < m)
                        g.addedge(u, x * m + y + 1, total + 1);
                }
            } else
                g.addedge(u, t, a[i][j]);
        }
    cout << total - g.dinic() << '\n';
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
