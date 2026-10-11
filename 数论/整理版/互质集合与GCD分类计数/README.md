# 互质集合与GCD分类计数

**用途与条件：** 统计非空下标子集的gcd；按倍数统计与反演恢复恰好gcd=d的子集权重。

**复杂度：** O(V log V+n)时间、O(V+n)空间，V=max(a)。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `init(a,mod)`：a是无前导占位的正整数数组，预处理倍数个数和2幂
- `qur()`：gcd=1的非空下标子集数
- `weighted()`：gcd>1子集的size*gcd之和

## 例题

### CF803F Coprime Subsequences

[原题](https://codeforces.com/contest/803/problem/F)

**题意：** 求gcd为1的非空子序列数。

**为什么使用：** 选择下标后顺序唯一，因此子序列数等于下标子集数。每个d的候选有2^cnt[d]-1个。

**如何调用：** 读数组构造CoprimeSet，输出qur。

**复杂度：** O(V log V+n)时间、O(V+n)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF803F-Coprime%20Subsequences.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，2组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### CF839D Winter is here

[原题](https://codeforces.com/contest/839/problem/D)

**题意：** 累加gcd>1子序列的长度乘gcd。

**为什么使用：** 含c个候选的所有子集长度和为c*2^(c-1)；从大到小减掉更大gcd的贡献。

**如何调用：** 构造CoprimeSet后调用weighted，精确类别存exact。

**复杂度：** O(V log V+n)时间、O(V+n)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF839D-Winter%20is%20here.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，2组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- 不同下标视为不同选择，重复值不可去重。
- 减法取模需归一化；空集必须扣掉。
- 不是两两互质，而是整个子集gcd为1。

## 个人资料来源

- `数论/数论10_ACM板子.md`

未提交在线评测，不宣称AC。
