# 曼哈顿距离坐标旋转

**用途与条件：** 用u=x+y,v=x-y把平面曼哈顿距离变为旋转坐标的切比雪夫距离；最大距离只需两维极值。

**复杂度：** add/qur/diameter O(1)；建n点O(n)时间/O(1)额外空间。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `add(x,y)`：加入点，维护两维极值
- `diameter()`：已有点中最大曼哈顿距离
- `qur(x,y)`：询问到已有点的最大曼哈顿距离

## 例题

### ABC178E Dist Max

[原题](https://atcoder.jp/contests/abc178/tasks/abc178_e)

**题意：** 求平面n点两两曼哈顿距离的最大值。

**为什么使用：** max(|Δu|,|Δv|)的最大值由每一维最大减最小得到。

**如何调用：** add所有点，diameter。

**复杂度：** O(n)时间/O(1)额外空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/ABC178E-Dist%20Max.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，1组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### Typical90036 Max Manhattan Distance

[原题](https://atcoder.jp/contests/typical90/tasks/typical90_aj)

**题意：** 多次指定一个已有点，询问到所有点的最大曼哈顿距离。

**为什么使用：** 两维极值由全部点共享，每问只比较到四个端点。

**如何调用：** 保留点数组；add预处理，qur(a[q])。

**复杂度：** O(n+q)时间/O(n)空间（保存输入点）。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/Typical90036-Max%20Manhattan%20Distance.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，2组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### ABC437F Manhattan Christmas Tree 2

[原题](https://atcoder.jp/contests/abc437/tasks/abc437_f)

**题意：** 支持修改一个点坐标，查询下标区间内到指定坐标最远的曼哈顿距离。

**为什么使用：** 将Manhattan四个极值作为线段树合并信息，区间极值仍满足旋转距离公式。

**如何调用：** 完整板子附ManhattanSeg；每点change初值；修改change，查询qur(L,R).qur(x,y)。

**复杂度：** O((n+q)log n)时间/O(n)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/ABC437F-Manhattan%20Christmas%20Tree%202.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，2组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- 坐标和、差、最终距离均须在long long内。
- 旋转后的整数坐标满足奇偶约束，若反求点或统计格点必须检查；本最大值问题不需要。
- 仅维护極值无法回答最小距离。

## 个人资料来源

- `tirick/总结.md`

未提交在线评测，不宣称AC。
