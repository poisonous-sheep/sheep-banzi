# 二进制位贡献与Popcount计数

**用途与条件：** 位独立贡献的乘法原理：原Meaningless Sequence加权和、按掩码统计1位次数、按popcount分类。

**复杂度：** weighted O(L)时间/空间；masked O(log n)时间/O(1)空间；distribution O(log² n)时间/空间。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `weighted(s,c)`：二进制上界s，Σ0..N c^popcount(x)模mod
- `masked(n,mask)`：Σ0..n popcount(x&mask)
- `distribution(n)`：0..n按popcount计数，要求n<=1e18以保计数不溢出

## 例题

### Gym102832D Meaningless Sequence

[原题](https://codeforces.com/gym/102832/problem/D)

**题意：** 按原递推定义序列，求0..N的项和，N用二进制给出。

**为什么使用：** 递推可化为c^popcount；首次低于上界后，剩余自由位贡献(1+c)^剩余位。

**如何调用：** PopcountDP(1e9+7).weighted(N,c)。

**复杂度：** O(|N|)时间与空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/Gym102832D-Meaningless%20Sequence.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，1组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### ABC356D Masked Popcount

[原题](https://atcoder.jp/contests/abc356/tasks/abc356_d)

**题意：** 求0..N每个数与M按位与后的popcount总和。

**为什么使用：** 拆成M中每个1位出现次数；该位0/1按周期交替。

**如何调用：** PopcountDP(998244353).masked(N,M)。

**复杂度：** O(log N)时间、O(1)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/ABC356D-Masked%20Popcount.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，2组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### P4317 花神的数论题

[原题](https://www.luogu.com.cn/problem/P4317)

**题意：** 将1..N每个数的二进制1的个数相乘，模10000007。

**为什么使用：** 按popcount=k分组，每类贡献k^计数；需要精确计数作为指数。

**如何调用：** distribution(N)，从k=1累乘powmod(k,cnt[k])。

**复杂度：** O(log² N)时间/空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/P4317-%E8%8A%B1%E7%A5%9E%E7%9A%84%E6%95%B0%E8%AE%BA%E9%A2%98.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- 前导0在二进制统计中不改变popcount。
- c=0时0^0按序列a0=1处理，weighted仍正确。
- distribution输出精确指数，不对mod取模；指数模数也不能随意用答案模数。

## 个人资料来源

- `dp/数位动态规划进阶_比赛板子.md`

未提交在线评测，不宣称AC。
