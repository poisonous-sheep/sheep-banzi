# 动态开点权值线段树

[完整模板](权值线段树（动态开点基础版）.cpp) · [合并分裂旧变体（GitHub）](https://github.com/poisonous-sheep/sheep-banzi/blob/main/数据结构%20/线段树/权值线段树（合并与分裂）.cpp)

维护值域闭区间 `[L,R]` 内的可重集合。叶子保存次数，内部节点保存次数和；排名按重数计算。保留原来的动态开点、递归结构、`seg/root/L/R` 和 `ls/rs/update/change/qur/kth` 命名。

| 接口 | 含义 |
|---|---|
| `WeightSegTree seg(L,R)` / `seg.init(L,R)` | 初始化/清空；重新初始化后所有旧根与节点编号失效 |
| `seg.change(x,{c})` | x 的次数增加 c；c 非零，删除前保证次数足够 |
| `seg.qur(l,r).cnt` | 闭区间内次数；自动与值域取交集，l>r 返回0 |
| `seg.all().cnt` / `seg.size()` | 集合总次数 |
| `seg.kth(k)` | 第 k 小，k 从1开始；非法排名返回-1 |
| `seg.kth_max(k)` | 第 k 大，k 从1开始；非法排名返回-1 |

`V=R-L+1`：修改、区间查询、排名查询 `O(1+log V)`，总次数查询 `O(1)`。首次初始化 `O(1)`，已有节点后重置销毁旧节点为 `O(节点数)`。累计 D 个不同插入值的空间上界 `O(1+D log V)`，同时不超过完整值域二叉树的节点数量。若离散化为 M 个值，节点数不超过约 `2M`。

注意：

- `seg[0]` 是次数为0的空节点；读查询不会新开点。删除不会回收节点，空间取决于累计出现过的不同值，不能只按当前集合大小估计。
- 不要把递归参数传错：外层直接 `change(x,{1})`、`qur(l,r)`、`kth(k)` 即可。
- 子节点编号保留 `int32_t` 以节省内存，计数使用 long long。总次数不能超过 `LLONG_MAX`，节点数不能超过 `INT32_MAX`；`assert` 用于检查调用前提，不能用它替代题目逻辑。
- 值域允许完整 long long 范围；中点差值使用 `__int128` 避免加法溢出，要求 GCC/Clang 支持该扩展。递归深度最多约64层。
- 值域包含-1时，非法排名的-1与合法答案-1可能相同；先用 `size()` 或区间计数判断排名是否合法。需要计算 x-1/x+1 时另行注意端点溢出。
- 扩容会使 vector 元素引用失效；不能跨递归/`newnode()` 保存 `seg[id]` 的引用，原代码的临时编号写法已保留。

## 代表性例题

以下原题已于2026-10-11读取核实；代码只含完整 `solve()`，依赖上面的模板，不能独立编译。

| 层次 | 原题 | 展示的调用 | 代码 |
|---|---|---|---|
| 基础动态集合 | [ABC253 C — Max - Min Query](https://atcoder.jp/contests/abc253/tasks/abc253_c) | 插入、按现有次数批量删除、第1大/小 | [solve](例题/ABC253C-Max-Min-Query.cpp) |
| 有序集合应用 | [P3369 — 普通平衡树](https://www.luogu.com.cn/problem/P3369) | 次数前缀转排名、严格前驱/后继、负值域 | [solve](例题/P3369-普通平衡树.cpp) |
| 大值域与限制排名 | [ABC241 D — Sequence Query](https://atcoder.jp/contests/abc241/tasks/abc241_d) | 1e18值域离散化、<=x第k大、>=x第k小 | [solve](例题/ABC241D-Sequence-Query.cpp) |

ABC253 C 删除 `min(c,次数)`，为0时不调用 change。P3369 的严格前驱排名为“小于x的次数”，后继排名为“小于等于x的次数+1”。ABC241 D 收集所有操作的 x，离散化后按原操作顺序处理；答案从压缩下标映射回原值。

## 验证与修复记录

与远端快照 `857d5f3c36ff1dbbab4cf27a13d52c443bdac4aa` 比较：

- 将 `info` 与 friend 合并逻辑移入 WeightSegTree；`change(x,{1})` 等调用不变，显式声明信息类型时改用 `WeightSegTree::info`。
- 将 `(l+r)>>1` 改为宽整数安全中点，避免大值域加法溢出。
- `kth_max` 先检查非法 k，避免计算 `size()-k+1` 时溢出；加上计数与节点编号范围断言。
- 把注释中的示例变成真实可执行的 solve；没有改动合并分裂变体。

验证命令：`python .work_review/library/verify_weight.py`。组合方法：取模板 solve 之前的定义，接例题片段，再接模板 signed main。本地验证记录：模板24,000次、例题合计39,600次随机操作通过；ABC253 C两组和ABC241 D一组官方样例通过。脚本与详细日志位于本地工作目录，不发布至本仓库。未提交在线评测，不声称AC。
