# 度数根号分治

**用途与条件：** 小度点广播直接修改邻居，大度点广播记录时间戳；查询从相邻大点恢复最后一次颜色。

**复杂度：** 预处理O(n+m)，每次O(B+m/B)，B约sqrt(m)；空间O(n+m)。

[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。

## 接口

- `add_edge/build(a)`：静态无向图，a为1基初始颜色
- `qur(u)`：读取含懒广播影响的当前颜色
- `change(u,c,self)`：向所有邻居广播c；self=true也更新自己

## 例题

### ABC219G Propagation

[原题](https://atcoder.jp/contests/abc219/tasks/abc219_g)

**题意：** 查询点将自身数字复制给所有邻居，最终输出所有点数字。

**为什么使用：** 高次数邻居更新用重度懒广播规避星形图退化。

**如何调用：** build初始col[i]=i；每次x先qur(x)，再change(x,c,false)。

**复杂度：** O(n+m+q sqrt m)时间、O(n+m)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/ABC219G-Propagation.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，2组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

### Typical90-083 Colorful Graph

[原题](https://atcoder.jp/contests/typical90/tasks/typical90_ce)

**题意：** 输出指定点当前颜色后，将它及全部邻居改成新颜色。

**为什么使用：** 邻居广播与前题同模型，区别是本点也赋值。

**如何调用：** 初始全1；qur(x)输出后change(x,y,true)。

**复杂度：** O(n+m+q sqrt m)时间、O(n+m)空间。

[solve及辅助代码](%E4%BE%8B%E9%A2%98/Typical90-083-Colorful%20Graph.cpp)；依赖本节模板，替换原solve后组合编译。

**验证：** C++17组合编译通过，1组登记运行通过；未在线提交

**来源：** 已读取原站题面并核实题号、模型与输入格式

## 易错点

- qur必须先于广播读取当前颜色，懒标记比较时间戳。
- 建图后build一次，动态增边不适用。
- 大点只有O(m/B)个，因此查询扫描的大点邻居有上界。

## 个人资料来源

- `杂/根号分治.md`

未提交在线评测，不宣称AC。
