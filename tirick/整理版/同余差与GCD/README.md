# 同余差与GCD

**用途与条件：** 所有数同余模m当且仅当m整除全部差；最大可行模或步长来自差值GCD。

**复杂度：** stride/from O(n log A)时间/O(1)额外空间；partitions O(n*tau(n)*log A)时间。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `stride(a,k)`：相距k元素差值的GCD
- `partitions(a)`：CF1920C的可行分段长度数
- `from(a,x)`：所有点到x差值GCD

## 例题

### CF1920C Partitioning the Array

[原题](https://codeforces.com/problemset/problem/1920/C)

**题意：** 对n的每个因数k将数组分成长度k块，存在m≥2使各块对应位置模m相同则计数。

**为什么使用：** 对应位置的相邻块差为a[i]-a[i-k]；它们的GCD不为1正是存在合法模数。

**如何调用：** partitions(a)，枚举因数并调用stride。

**复杂度：** O(n*tau(n)*log A)时间/O(n)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF1920C-Partitioning%20the%20Array.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### ABC109C Skip

[原题](https://atcoder.jp/contests/abc109/tasks/abc109_c)

**题意：** 从X出发每次左右移动固定D，访问所有给定城市，求最大的正D。

**为什么使用：** 每个城市与X的差必须是D整数倍，最大D是这些差的GCD。

**如何调用：** from(a,X)。

**复杂度：** O(n log A)时间/O(n)空间（保存输入）。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/ABC109C-Skip.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，2组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- GCD=0表示所有差为0，任意正模均可，不是无解。
- CF1920C需要存在m≥2，因此g!=1，0也可行。
- llabs(a-b)先相减可能溢出，本例限定差值在long long内。

## 个人资料来源

- `tirick/总结.md`

未提交在线评测，不宣称AC。
