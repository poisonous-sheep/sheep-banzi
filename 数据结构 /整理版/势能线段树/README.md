# 势能线段树

**用途与条件：** 非负数组区间开方、区间取模、单点赋值和区间和；用mx跳过不变节点。

**复杂度：** 开方每值只改变O(log log A)次；取模有效改变使值至少减半，累计O((n+m)log A log n)；查询O(log n)，空间O(n)。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `update_sqrt(l,r)`：向下取整开方
- `modify_mod(l,r,x)`：x>0，区间取模
- `change(p,x)`：非负赋值
- `qur(l,r).sum`：区间和

## 例题

### P4145 花神游历各国

[原题](https://www.luogu.com.cn/problem/P4145)

**题意：** 区间开方或区间和。

**为什么使用：** max<=1的节点所有值已稳定，可停止递归。

**如何调用：** op0调用update_sqrt，op1调用qur；先交换反向端点。

**复杂度：** 累计O(n log log A log n+m log n)时间、O(n)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/P4145-%E8%8A%B1%E7%A5%9E%E6%B8%B8%E5%8E%86%E5%90%84%E5%9B%BD.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### CF438D The Child and Sequence

[原题](https://codeforces.com/problemset/problem/438/D)

**题意：** 区间和、区间取模、单点赋值。

**为什么使用：** a%x只有在a>=x时改变，并且改变后小于原值一半。

**如何调用：** modify_mod用区间max剪枝；赋值change恢复势能。

**复杂度：** 摊还O((n+m)log A log n)时间、O(n)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF438D-The%20Child%20and%20Sequence.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，1组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- 用整数平方比较修正sqrt浮点误差。
- 不能将单次修改声称总是O(log n)；需势能摊还分析。

## 个人资料来源

- `数据结构/线段树/势能线段树.cpp`

未提交在线评测，不宣称AC。
