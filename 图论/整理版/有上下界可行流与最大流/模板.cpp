#include <bits/stdc++.h>
using namespace std;
#define int long long

// 有上下界可行流与最大流：先强制下界并记录节点净流入差，超级源汇补平衡；有源汇加t->s并在可行残量上继续增广。
// 一般Dinic O(V²E)时间、O(V+E)空间。
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
struct BoundedFlow {
    static constexpr int INF = 4000000000000000000LL;
    struct edge {
        int u, v, l, r, id;
    };
    int n, S, T;
    vector<int> balance;
    vector<edge> edges;
    FlowGraph<int> g;
    vector<int> aux;
    BoundedFlow(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        S = n + 1;
        T = n + 2;
        balance.assign(n + 1, 0);
        edges.clear();
        aux.clear();
        g.init(S, T, T);
    }
    int add_edge(int u, int v, int l, int r) {
        assert(0 <= l && l <= r);
        int id = g.etot;
        g.addedge(u, v, r - l);
        balance[u] -= l;
        balance[v] += l;
        edges.push_back({u, v, l, r, id});
        return edges.size() - 1;
    }
    bool feasible() {
        int need = 0;
        for (int u = 1; u <= n; u++) {
            if (balance[u] > 0) {
                aux.push_back(g.etot);
                g.addedge(S, u, balance[u]);
                need += balance[u];
            }
            if (balance[u] < 0) {
                aux.push_back(g.etot);
                g.addedge(u, T, -balance[u]);
            }
        }
        return g.dinic() == need;
    }
    int value(int k) {
        auto z = edges[k];
        return z.r - g.e[z.id].f;
    }
    optional<int> maxflow(int s, int t) {
        int back = g.etot;
        g.addedge(t, s, INF);
        if (!feasible())
            return nullopt;
        int base = g.e[back ^ 1].f;
        g.e[back].f = g.e[back ^ 1].f = 0;
        for (int id : aux)
            g.e[id].f = g.e[id ^ 1].f = 0;
        g.s = s;
        g.t = t;
        return base + g.dinic();
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int s = n + 1, t = n + 2;
    BoundedFlow g(t);
    vector<array<int, 3>> choice;
    auto prime = [](int x) {
        if (x < 2)
            return false;
        for (int p = 2; p <= x / p; p++)
            if (x % p == 0)
                return false;
        return true;
    };
    for (int i = 1; i <= n; i++)
        if (a[i] & 1)
            g.add_edge(s, i, 2, 2);
        else
            g.add_edge(i, t, 2, 2);
    for (int i = 1; i <= n; i++)
        if (a[i] & 1)
            for (int j = 1; j <= n; j++)
                if (!(a[j] & 1) && prime(a[i] + a[j]))
                    choice.push_back({i, j, g.add_edge(i, j, 0, 1)});
    g.add_edge(t, s, 0, 2 * n);
    if (!g.feasible()) {
        cout << "Impossible\n";
        return;
    }
    vector<vector<int>> adj(n + 1), cycles;
    for (auto [u, v, k] : choice)
        if (g.value(k))
            adj[u].push_back(v), adj[v].push_back(u);
    vector<int> vis(n + 1);
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            vector<int> cyc;
            int u = i, p = 0;
            do {
                cyc.push_back(u);
                vis[u] = 1;
                int v = adj[u][0] == p ? adj[u][1] : adj[u][0];
                p = u;
                u = v;
            } while (u != i);
            cycles.push_back(cyc);
        }
    cout << cycles.size() << '\n';
    for (auto c : cycles) {
        cout << c.size();
        for (int u : c)
            cout << ' ' << u;
        cout << '\n';
    }
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
