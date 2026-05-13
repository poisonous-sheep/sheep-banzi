// ==========================================
// 🎨 DSU on Tree 相关变量定义
int n, m;
int arr[N];           // arr[i] 存节点 i 的颜色
vector<int> adj[N];   // 邻接表存树

int fa[N];            // fa[i]: 节点 i 的父亲，防止遍历时往回走
int siz[N];           // siz[i]: 以 i 为根的子树的大小（包含多少个节点）
int son[N];           // son[i]: 节点 i 的重儿子（它的所有儿子里，子树最大的那个）

int colorCnt[N];      // 类似一个“桶”，colorCnt[c] 表示颜色 c 当前出现了多少次
int ans[N];           // ans[i]: 记录离线计算后，节点 i 子树内的颜色种类数
int diffColors = 0;   // 全局变量，动态维护当前统计范围内的不同颜色总数

// 📌 DFS1: 预处理出每个节点的 父节点、子树大小 和 重儿子
void dfs1(int u, int f) {
    fa[u] = f;
    siz[u] = 1;      // 自己算 1 个节点
    son[u] = 0;      // 适配多组数据，清空旧的重儿子标记
    
    for (int v : adj[u]) {
        if (v != f) { // 不走回头路
            dfs1(v, u);
            siz[u] += siz[v]; // 把儿子的子树大小加给自己
            
            // 找重儿子：如果没有记录过重儿子，或者当前儿子的子树比记录的重儿子还大，就更新
            if (son[u] == 0 || siz[son[u]] < siz[v]) {
                son[u] = v;
            }
        }
    }
}

// ➕ 把以 u 为根的整棵子树的信息暴力加入全局状态
void addNode(int u) {
    // 如果某种颜色之前出现次数是 0，现在变成 1 了，说明多了一种新颜色
    if (++colorCnt[arr[u]] == 1) {
        diffColors++;
    }
    // 继续暴力遍历所有子节点，把它们也加进来
    for (int v : adj[u]) {
        if (v != fa[u]) {
            addNode(v);
        }
    }
}

// ➖ 把以 u 为根的整棵子树的信息暴力从全局状态中删去
void delNode(int u) {
    // 撤销贡献很简单，直接把这种颜色的计数器清零即可（也可以 -- 减到0再减 diffColors）
    // 题目通常只需要知道“有没有”，直接赋值为 0 更快
    colorCnt[arr[u]] = 0;
    
    for (int v : adj[u]) {
        if (v != fa[u]) {
            delNode(v);
        }
    }
}

// 🧠 DFS2: 核心逻辑（树上启发式合并）
// 参数 keep 决定了：处理完以 u 为根的子树后，要不要保留它的信息？
// keep = 1 表示保留（通常是重儿子）；keep = 0 表示算完就清空（通常是轻儿子）。
void dfs2(int u, int keep) {
    // 1️⃣ 第一步：先处理所有的 轻儿子。
    // 轻儿子算完答案后，必须立刻把它们产生的影响清空（传 0），否则会污染后续要计算的兄弟节点。
    for (int v : adj[u]) {
        if (v != fa[u] && v != son[u]) {
            dfs2(v, 0); 
        }
    }

    // 2️⃣ 第二步：处理 重儿子。
    // 重儿子的节点最多，为了省时间，算完它的答案后，把它的信息保留下来（传 1），不撤销！
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }

    // 3️⃣ 第三步：计算 u 自己的答案。
    // 此时全局变量里只保留了 重儿子 的信息。
    // 所以我们需要把 u 自己，以及刚才被清空的所有 轻儿子 的信息，重新暴力加回来。
    if (++colorCnt[arr[u]] == 1) {
        diffColors++;
    }
    for (int v : adj[u]) {
        if (v != fa[u] && v != son[u]) {
            addNode(v); // 暴力重新加上轻儿子子树的贡献
        }
    }

    // 4️⃣ 第四步：这时候该加的都加上了，当前的 diffColors 就是 u 节点子树的真实答案！
    ans[u] = diffColors;

    // 5️⃣ 第五步：收尾。
    // 如果 u 本身是它父亲的轻儿子（即传入的 keep == 0），
    // 那 u 计算完自己的答案后，为了不影响它父亲的其他节点，必须把 u 整个子树带来的影响全部清空！
    if (keep == 0) {
        diffColors = 0;
        delNode(u);
    }
}

void solve() {
    cin >> n;
    
    // 🧹 多组数据清空保护
    // 如果你在多组数据题目中忘了清空，这里能保命
    rep(1, n) {
        adj[i].clear();
        colorCnt[i] = 0; // 防止上一组数据的颜色桶计数残留
    }
    diffColors = 0;      // 全局统计量清零
    
    // 读入树边
    rep(1, n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // 读入每个点的初始颜色
    rep(1, n) {
        cin >> arr[i];
    }
    
    // 开始算法流程
    dfs1(1, 0); // 先算出每个节点的重儿子在哪
    dfs2(1, 0); // 开始计算答案（根节点算完也不需要保留，传 0 即可）
    
    // 离线查询回答
    cin >> m;
    rep(1, m) {
        int cur;
        cin >> cur;
        cout << ans[cur] << endl;
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // 🚨 如果题目给出第一行是测试组数 T，取消下一行的注释即可：
    // cin >> t; 
    while (t--) solve();
    return 0;
}
