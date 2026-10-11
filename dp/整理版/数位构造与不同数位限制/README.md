# 数位构造与不同数位限制

**用途与条件：** 按字典序DFS构造>=n的最小数；收录至多k种与至少k种数位两个原资料变体。

**复杂度：** at_most O(L*10)；at_least最多O(L²*1024*10)时间、O(L*1024)空间。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `at_most(n,k)`：正整数n字符串，至多k种数位的最小>=n
- `at_least(n,k)`：至少k种，返回字符串避免答案超过long long

## 例题

### CF1560F1 Nearest Beautiful Number easy

[原题](https://codeforces.com/contest/1560/problem/F1)

**题意：** k<=2时构造不小于n的最近美丽数。

**为什么使用：** 按数位升序找第一个可完成方案就是最小合法数。

**如何调用：** 每组at_most(to_string(n),k)。

**复杂度：** 每组O(L*10)时间、O(L+10)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF1560F1-Nearest%20Beautiful%20Number%20easy.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### CF1560F2 Nearest Beautiful Number hard

[原题](https://codeforces.com/contest/1560/problem/F2)

**题意：** 推广为k<=10的最小合法数。

**为什么使用：** 同一剪枝仍成立，无需枚举10位数字集合全部1024种。

**如何调用：** 沿用at_most；这是原题的困难版，注明与F1为同题两档。

**复杂度：** 每组O(L*10)时间、O(L+10)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF1560F2-Nearest%20Beautiful%20Number%20hard.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- vis必须用计数整数，bool++/--错误且C++17禁止bool++。
- 至少k种不保证只增加一位，要一直尝试到max(原长度,k)。
- 至多k种的非tight合法前缀总可填已有数字，因此只在tight路径回溯。

## 个人资料来源

- `dp/数位动态规划进阶_比赛板子.md`

未提交在线评测，不宣称AC。
