// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1675D Vertical Paths
// 原题：https://codeforces.com/problemset/problem/1675/D
// 所属知识点：祖先路径最小费用覆盖；使用模板：AncestorCover
// 题意：将有根树分成最少条向下的互不相交路径，输出路径划分。
// 转化：每个叶子至少需要一条路径；把所有根到叶路径作为费用1候选，用覆盖接口得到叶子数。逐叶上溯切去已经覆盖的前缀，保持最优条数且每点恰好一次。
// 调用：从parent确定任意root；build，每个叶子add_path(leaf,root,1)，run_heap；另用used恢复不重叠路径。
// 复杂度：本通用调用O(n log n)时间/O(n)空间；此特例可仅用构造降为O(n)。
void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        AncestorCover t(n);
        vector<int> fa(n + 1), used(n + 1);
        int root = 0;
        for (int u = 1; u <= n; u++) {
            cin >> fa[u];
            if (fa[u] == u)
                root = u;
            else
                t.add_edge(fa[u], u);
        }
        t.build(root);
        for (int u = 1; u <= n; u++)
            if (t.son[u].empty())
                t.add_path(u, root, 1);
        cout << t.run_heap(root) << '\n';
        for (int u = 1; u <= n; u++)
            if (t.son[u].empty()) {
                vector<int> p;
                int v = u;
                while (!used[v]) {
                    p.push_back(v);
                    used[v] = 1;
                    if (v == root)
                        break;
                    v = fa[v];
                }
                reverse(p.begin(), p.end());
                cout << p.size() << '\n';
                for (int x : p)
                    cout << x << ' ';
                cout << '\n';
            }
        cout << '\n';
    }
}
