# DSU on Tree

**用途与条件：** 轻子树算完清空、重子树保留，以单一统计容器回答所有子树询问。

**复杂度：** O(n log n)次增删；总时间再乘增删与询问成本；O(n)树结构空间。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `add_edge`：加入无向树边
- `run(change,answer,root)`：change(u,+1/-1)增删，answer(u)读取完整子树状态

## 例题

### CF600E Lomsat gelral

[原题](https://codeforces.com/problemset/problem/600/E)

**题意：** 求子树众数颜色编号和。

**为什么使用：** DSU保留重子树，颜色增删同时更新每个频率的颜色和与种类数。

**如何调用：** change维护cnt、freqSum、freqCount及mx；answer读freqSum[mx]。

**复杂度：** O(n log n)时间、O(n+颜色值域)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF600E-Lomsat%20gelral.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### CF375D Tree and Queries

[原题](https://codeforces.com/contest/375/problem/D)

**题意：** 求子树内至少出现k次的颜色种数。

**为什么使用：** 单次颜色频率从x变x+1，只使“至少x+1次”计数增加，删除逆操作；无需树状数组。

**如何调用：** change对atleast新旧边界加减；answer回答挂在该点的全部询问。

**复杂度：** O(n log n+m)时间、O(n+m+颜色值域)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF375D-Tree%20and%20Queries.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，1组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- 移除必须与加入完全互逆；原“直接清零”仅限清空整个容器的特定统计，不适合通用回调。
- run最终清空统计；多次运行须初始化外部答案和桶。
- 递归深度O(n)，链树可能需要较大栈。

## 个人资料来源

- `杂/dsu on tree.cpp`
- `数据结构/模块二_DSU_on_Tree与树上统计.md`

未提交在线评测，不宣称AC。
