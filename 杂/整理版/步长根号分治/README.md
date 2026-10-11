# 步长根号分治

**用途与条件：** 小步长预维护/预处理，大步长暴力跳跃；收录动态模下标和与静态跳跃两个模型。

**复杂度：** 动态修改O(B)、查询O(1)或O(n/B)，空间O(n+B²)；跳跃预处理O(nB)、空间O(nB)，B约sqrt(n)。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `change/qur`：动态单点加与下标模k等于r求和
- `build_jump/jump_count`：静态正数数组跳到p+a[p]+k，求越界前次数

## 例题

### CF1207F Remainder Problem

[原题](https://codeforces.com/problemset/problem/1207/F)

**题意：** 单点增加，查询所有下标模x等于y的位置和。

**为什么使用：** 小模数一次修改影响B个桶，大模数查询最多n/B个位置。

**如何调用：** init(500000)，操作1用change，操作2用qur。

**复杂度：** O(q sqrt N)时间、O(N)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF1207F-Remainder%20Problem.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### CF797E Array Queries

[原题](https://codeforces.com/contest/797/problem/E)

**题意：** 多次询问正数数组从p开始跳p+a[p]+k的次数。

**为什么使用：** k较小时重复查询可复用倒序DP；大k每次跳至少k格。

**如何调用：** 读数组后build_jump，再逐次jump_count。

**复杂度：** O(n sqrt n+q sqrt n)时间、O(n sqrt n)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF797E-Array%20Queries.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，1组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- 跳跃版必须a[i]>0，才能保证预处理依赖右侧与大步长次数界。
- 两个模型独立使用同一对象，不要build_jump后再用动态tag。
- jump计数存int32_t避免long long宏把nB内存翻倍。

## 个人资料来源

- `杂/根号分治.md`

未提交在线评测，不宣称AC。
