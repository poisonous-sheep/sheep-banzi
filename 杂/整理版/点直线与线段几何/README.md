# 点直线与线段几何

**用途与条件：** 保留P向量运算与相交、投影、反射、距离等接口，使用long double并处理退化线段。

**复杂度：** 单次运算O(1)时间/空间。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `P::dot/det/rot/unit`：点积叉积、旋转和单位向量
- `isSS/isSS_strict/onSeg`：含边界与严格相交/在线段判定
- `chkLL/isLL/proj/reflect`：非平行直线交点、投影、反射
- `nearest/disSS`：点段或段段距离，支持点状线段

## 例题

### CGL_1_A Projection

[原题](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A)

**题意：** 求多点到给定直线的垂足。

**为什么使用：** 点在直线方向上的正交分量由点积给出。

**如何调用：** 读取a,b，每点proj后输出x,y。

**复杂度：** O(q)时间、O(1)额外空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CGL_1_A-Projection.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### CGL_1_B Reflection

[原题](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B)

**题意：** 求点关于直线的镜像。

**为什么使用：** 垂足是点与镜像的中点，镜像=2*投影-原点。

**如何调用：** 调用reflect(a,b,p)。

**复杂度：** O(q)时间、O(1)额外空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/CGL_1_B-Reflection.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过；未登记样例运行；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- sort用精确字典序；EPS比较不满足严格弱序，不能用于排序。
- proj要求a!=b，isLL要求非平行；nearest单独处理a==b。
- EPS按数据尺度调整；整数精确几何可改用__int128叉积。

## 个人资料来源

- `杂/点线.cpp`

未提交在线评测，不宣称AC。
