#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 4e5 + 10;

struct Edge {
    int u, v, w;
};

vector<int> tr[N];
int fa[N];
int val[N];

int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Edge> e(m);

    for (auto &[u, v, w] : e) {
        cin >> u >> v >> w;
    }

    // 最小生成树版本：
    //
    // 边权从小到大
    //
    // 最终：
    //
    //      父亲权值大
    //          ↑
    //          |
    //      儿子权值小
    //
    sort(e.begin(), e.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    /*
        一开始：

        原图有 n 个点

            1   2   3   4  ... n

        它们直接作为 Kruskal 重构树的叶子。

        所以：

        1 ~ n：原图节点
        n+1 ~ 2n-1：之后新建的“合并节点”
    */

    int tot = n;

    for (int i = 1; i <= 2 * n; i++) {
        fa[i] = i;
    }

    for (auto [u, v, w] : e) {

        /*
            找到 u、v 当前所在连通块对应的
            “重构树根节点”。

            例如：

                  5
                 / \
                1   2

            那么：

            find(1) = 5
            find(2) = 5
        */

        int fu = find(u);
        int fv = find(v);

        /*
            已经在同一个连通块：

                  fu
                 /  \
                u    v

            说明这条边不会造成新的合并。

            普通 Kruskal：
                不选这条边

            Kruskal 重构树：
                不建新节点
        */

        if (fu == fv) continue;

        /*
            当前边：

                u ------- v
                     w

            把两个不同连通块合并。

            原来：

                fu          fv

            创建新节点 tot：

                       tot
                      val=w
                     /     \
                   fu       fv

            这个 tot 表示：

            “当边权达到 w 时，
             fu、fv 这两个连通块第一次合并。”
        */

        ++tot;

        val[tot] = w;

        /*
                    tot(w)
                   /      \
                 fu        fv
        */

        tr[tot].push_back(fu);
        tr[tot].push_back(fv);

        /*
            并查集也要同步更新。

            注意！！！

            普通 Kruskal 常写：

                fa[fu] = fv;

            但是 Kruskal 重构树不能这么写。

            因为现在新连通块的代表应该是：

                       tot
                      /   \
                    fu     fv

            所以：
        */

        fa[fu] = tot;
        fa[fv] = tot;

        // tot 自己是新连通块的根
        fa[tot] = tot;
    }

    /*
        如果原图连通：

        最后 tot 就是整棵树的根。

        例如边：

        1 --2-- 2
        2 --5-- 3
        3 --8-- 4

        合并过程：

        第一次：

              5(2)
             /   \
            1     2


        第二次：

                  6(5)
                 /   \
              5(2)    3
             /   \
            1     2


        第三次：

                       7(8)
                      /   \
                   6(5)    4
                  /   \
               5(2)    3
              /   \
             1     2


        所以：

        val[5] = 2
        val[6] = 5
        val[7] = 8

        而且从叶子向根：

            1
            |
           5(2)
            |
           6(5)
            |
           7(8)

        权值单调不减。
    */
}
