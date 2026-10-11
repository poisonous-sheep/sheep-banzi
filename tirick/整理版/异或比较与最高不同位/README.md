# 异或比较与最高不同位

**用途与条件：** 非负数满足|x-y|≤x xor y≤x+y；异或比较由最高不同位决定，低位值域可截断DP转移。

**复杂度：** subsequence O(n*2^B)时间/O(n)空间；max_xor O(log r)时间/O(1)空间。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `subsequence(a,B)`：0-based下标；每个a[i]<2^B，最长符合交叉异或比较的子序列
- `max_xor(l,r)`：区间内任意两个数的最大异或

## 例题

### CF1720D1 Xor-Subsequence (easy version)

[原题](https://codeforces.com/problemset/problem/1720/D1)

**题意：** ai≤200，选最长子序列，使相邻所选下标i<j满足ai xor j < aj xor i，下标从0起。

**为什么使用：** 高于第7位只有下标贡献，间距≥256必然失败；仅枚举最近255个前驱。

**如何调用：** 读T、a，subsequence(a,8)。

**复杂度：** O(256n)时间/O(n)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF1720D1-Xor-Subsequence%20%28easy%20version%29.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### CF276D Little Girl and Maximum XOR

[原题](https://codeforces.com/problemset/problem/276/D)

**题意：** 从整数区间[l,r]选两数使异或最大。

**为什么使用：** l,r最高不同位以下可以构造全1；最高不同位以上必须一致。

**如何调用：** max_xor(l,r)。

**复杂度：** O(log r)时间/O(1)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CF276D-Little%20Girl%20and%20Maximum%20XOR.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- 下标差≥2^B时，高位大小已经使CF1720条件不可能成立；只能在值域小于2^B时截断。
- D2没有D1的ai≤200限制，不能照用窗口256。
- max_xor由l xor r最高位确定，l=r时答案0。

## 个人资料来源

- `tirick/总结.md`

未提交在线评测，不宣称AC。
