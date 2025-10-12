#include <iostream>
#include <vector>

// 使用 #define int long long 来避免整数溢出，在处理大数据时很常见
#define int long long

using namespace std;

// --- 全局常量和变量 ---
const int N = 1e5 + 10; // 数组最大长度
int t[N * 4];          // 线段树核心数组，存储区间和
int tag[N * 4];        // 懒惰标记数组
int a[N];              // 存储输入的原始数组


// --- 辅助函数：获取左右子节点的编号 ---
// p 是当前父节点的编号
inline int ls(int p) { return p << 1; }     // 左儿子编号 (p * 2)
inline int rs(int p) { return p << 1 | 1; } // 右儿子编号 (p * 2 + 1)


/**
 * @brief 上传操作：根据左右子节点的值，更新父节点的值
 * @param p 当前父节点的编号
 */
void push_up(int p) {
    // 父节点的区间和等于左右子节点的区间和之和
    t[p] = t[ls(p)] + t[rs(p)];
}

/**
 * @brief 建树操作：递归地初始化线段树
 * @param p 当前节点编号
 * @param l 当前节点所表示区间的左端点
 * @param r 当前节点所表示区间的右端点
 */
void build(int p, int l, int r) {
    // 到达叶子节点，即区间长度为1
    if (l == r) {
        t[p] = a[l]; // 叶子节点的值等于原始数组对应位置的值
        return;
    }
    // 递归处理左右子树
    int mid = l + r >> 1; // 计算区间中点
    build(ls(p), l, mid);     // 构建左子树
    build(rs(p), mid + 1, r); // 构建右子树
    push_up(p);               // 根据建好的左右子树，更新当前节点的值
}

/**
 * @brief 辅助函数：将懒惰标记 k 的效果应用到节点 p 上
 * @param p 当前节点编号
 * @param l, r 当前节点所表示的区间 [l, r]
 * @param k 从父节点传下来的懒惰标记的值
 */
inline void f(int p, int l, int r, int k) {
    tag[p] += k;                        // 将懒惰标记累加到当前节点
    t[p] = t[p] + k * (r - l + 1);      // 更新当前节点的区间和
}

/**
 * @brief 下推操作：将父节点的懒惰标记下发给其子节点
 * @param p 当前父节点编号
 * @param l, r 当前父节点所表示的区间 [l, r]
 */
inline void push_down(int p, int l, int r) {
    // 计算中点，用于划分左右子节点的区间
    int mid = l + r >> 1;
    // 将父节点的 tag[p] 分别应用到左右子节点上
    f(ls(p), l, mid, tag[p]);
    f(rs(p), mid + 1, r, tag[p]);
    // 父节点的标记任务已完成并下发，清空父节点标记
    tag[p] = 0;
}

/**
 * @brief 区间修改操作
 * @param L, R 要修改的目标区间
 * @param l, r 当前节点所代表的区间
 * @param p 当前节点编号
 * @param k 要增加的值
 */
inline void update(int L, int R, int l, int r, int p, int k) {
    // 如果当前节点代表的区间被目标区间完全覆盖
    if (L <= l && r <= R) {
        t[p] += k * (r - l + 1); // 直接更新当前节点的区间和
        tag[p] += k;             // 给当前节点打上懒惰标记
        return;                  // 无需再往下递归
    }

    // 在访问子节点之前，先下推当前节点的懒惰标记
    push_down(p, l, r);

    // 递归处理与目标区间有交集的子节点
    int mid = l + r >> 1;
    if (L <= mid) update(L, R, l, mid, ls(p), k);     // 左子节点有交集
    if (R > mid) update(L, R, mid + 1, r, rs(p), k);  // 右子节点有交集
    
    // 子节点更新完毕后，上传更新当前父节点的值
    push_up(p);
}

/**
 * @brief 区间查询操作
 * @param q_x, q_y 要查询的目标区间
 * @param l, r 当前节点所代表的区间
 * @param p 当前节点编号
 * @return int 查询结果（区间和）
 */
int query(int q_x, int q_y, int l, int r, int p) {
    int res = 0;
    // 如果当前节点代表的区间被查询区间完全覆盖，直接返回当前节点的和
    if (q_x <= l && r <= q_y) return t[p];

    // 在访问子节点之前，先下推当前节点的懒惰标记，确保子节点数据正确
    int mid = (l + r) >> 1;
    push_down(p, l, r);

    // 递归查询与目标区间有交集的子节点，并累加结果
    if (q_x <= mid) res += query(q_x, q_y, l, mid, ls(p));
    if (q_y > mid) res += query(q_x, q_y, mid + 1, r, rs(p));
    return res;
}

/**
 * @brief 主逻辑函数：处理输入输出和操作分发
 */
void solve() {
    int n, q;
    cin >> n >> q; // 读取数组大小和操作次数
    for (int i = 1; i <= n; i++) cin >> a[i]; // 读取原始数组

    build(1, 1, n); // 根据原始数组构建线段树

    while (q--) {
        int op;
        cin >> op; // 读取操作类型
        if (op == 1) {
            // 类型1：区间修改
            int x, y, k;
            cin >> x >> y >> k;
            update(x, y, 1, n, 1, k);
        } else {
            // 类型2：区间查询
            int x, y;
            cin >> x >> y;
            cout << query(x, y, 1, n, 1) << endl;
        }
    }
}

signed main() {
    // 加速 C++ 的 cin/cout 输入输出
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // 通常用于多组测试用例，这里只有一组
    int t_cases = 1;
    // cin >> t_cases;
    while (t_cases--)
        solve();

    return 0;
}
