# sheep-banzi

小羊的算法竞赛模板。C++17；按个人 WeightSegTree 风格维护。

## 本次完成的知识点

| 知识点 | 模板与说明 | 功能 | 复杂度 | 代表例题 |
|---|---|---|---|---|
| 动态开点权值线段树 | [模板](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E7%BA%BF%E6%AE%B5%E6%A0%91/%E6%9D%83%E5%80%BC%E7%BA%BF%E6%AE%B5%E6%A0%91%EF%BC%88%E5%8A%A8%E6%80%81%E5%BC%80%E7%82%B9%E5%9F%BA%E7%A1%80%E7%89%88%EF%BC%89.cpp) · [README](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E7%BA%BF%E6%AE%B5%E6%A0%91/%E6%9D%83%E5%80%BC%E7%BA%BF%E6%AE%B5%E6%A0%91-README.md) | 可重集合增删、值域计数、第k小/大 | 操作 O(log V)，空间 O(D log V)；单值域 O(1) | [ABC253 C](https://atcoder.jp/contests/abc253/tasks/abc253_c) · [P3369](https://www.luogu.com.cn/problem/P3369) · [ABC241 D](https://atcoder.jp/contests/abc241/tasks/abc241_d) |

例题是依赖模板的 solve 片段；对应 README 有调用说明和代码链接。验证：模板24,000次随机操作，三例题合计39,600次随机操作；ABC253 C两组、ABC241 D一组官方样例通过。未提交在线评测，不声称AC。

## 原有 GitHub 模板索引

以下旧内容按原样保留并导入本地，没有将语法检查当作算法正确性或AC证明。缺少 main 的代码仍按片段使用。

| 分类 | 文件 | 当前状态 |
|---|---|---|
| tirick | [总结.md](tirick/%E6%80%BB%E7%BB%93.md) | 原有说明/代码块，未逐块验证 |
| 图论 | [HK二分图最大匹配.cpp](%E5%9B%BE%E8%AE%BA/HK%E4%BA%8C%E5%88%86%E5%9B%BE%E6%9C%80%E5%A4%A7%E5%8C%B9%E9%85%8D.cpp) | 独立语法检查通过；有main，未运行 |
| 图论 | [Kruskal重构树.cpp](%E5%9B%BE%E8%AE%BA/Kruskal%E9%87%8D%E6%9E%84%E6%A0%91.cpp) | 独立语法检查通过；无main，片段 |
| 图论 | [Kruskal重构树板子 (1).md](%E5%9B%BE%E8%AE%BA/Kruskal%E9%87%8D%E6%9E%84%E6%A0%91%E6%9D%BF%E5%AD%90%20%281%29.md) | 原有说明/代码块，未逐块验证 |
| 图论 | [SCC.md](%E5%9B%BE%E8%AE%BA/SCC.md) | 原有说明/代码块，未逐块验证 |
| 图论 | [prim.cpp](%E5%9B%BE%E8%AE%BA/prim.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 图论 | [二分图匹配.cpp](%E5%9B%BE%E8%AE%BA/%E4%BA%8C%E5%88%86%E5%9B%BE%E5%8C%B9%E9%85%8D.cpp) | 独立语法检查失败，依赖/错误待整理；有main，未运行 |
| 图论 | [二分图染色.cpp](%E5%9B%BE%E8%AE%BA/%E4%BA%8C%E5%88%86%E5%9B%BE%E6%9F%93%E8%89%B2.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 图论 | [倍增求lca.cpp](%E5%9B%BE%E8%AE%BA/%E5%80%8D%E5%A2%9E%E6%B1%82lca.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 图论 | [差分约束.cpp](%E5%9B%BE%E8%AE%BA/%E5%B7%AE%E5%88%86%E7%BA%A6%E6%9D%9F.cpp) | 独立语法检查通过；有main，未运行 |
| 图论 | [拓扑.cpp](%E5%9B%BE%E8%AE%BA/%E6%8B%93%E6%89%91.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 图论 | [欧拉路径.md](%E5%9B%BE%E8%AE%BA/%E6%AC%A7%E6%8B%89%E8%B7%AF%E5%BE%84.md) | 原有说明/代码块，未逐块验证 |
| 数据结构 | [01tire（支持删）.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/01tire%EF%BC%88%E6%94%AF%E6%8C%81%E5%88%A0%EF%BC%89.cpp) | 独立语法检查通过；有main，未运行 |
| 数据结构 | [ST表.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/ST%E8%A1%A8.cpp) | 独立语法检查通过；有main，未运行 |
| 数据结构 | [对顶堆（multiset维护中位数）.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E5%AF%B9%E9%A1%B6%E5%A0%86%EF%BC%88multiset%E7%BB%B4%E6%8A%A4%E4%B8%AD%E4%BD%8D%E6%95%B0%EF%BC%89.cpp) | 独立语法检查通过；有main，未运行 |
| 数据结构 | [并查集.md](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E5%B9%B6%E6%9F%A5%E9%9B%86/%E5%B9%B6%E6%9F%A5%E9%9B%86.md) | 原有说明/代码块，未逐块验证 |
| 数据结构 | [板子.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E5%B9%B6%E6%9F%A5%E9%9B%86/%E6%9D%BF%E5%AD%90.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 数据结构 | [二维数点.md](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E6%89%AB%E6%8F%8F%E7%BA%BF/%E4%BA%8C%E7%BB%B4%E6%95%B0%E7%82%B9.md) | 原有说明/代码块，未逐块验证 |
| 数据结构 | [封装.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E6%A0%91%E7%8A%B6%E6%95%B0%E7%BB%84/%E5%B0%81%E8%A3%85.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 数据结构 | [珂朵莉树.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E7%8F%82%E6%9C%B5%E8%8E%89%E6%A0%91.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 数据结构 | [势能线段树.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E7%BA%BF%E6%AE%B5%E6%A0%91/%E5%8A%BF%E8%83%BD%E7%BA%BF%E6%AE%B5%E6%A0%91.cpp) | 独立语法检查通过；有main，未运行 |
| 数据结构 | [区间修改区间查询.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E7%BA%BF%E6%AE%B5%E6%A0%91/%E5%8C%BA%E9%97%B4%E4%BF%AE%E6%94%B9%E5%8C%BA%E9%97%B4%E6%9F%A5%E8%AF%A2.cpp) | 独立语法检查通过；有main，未运行 |
| 数据结构 | [区间查询单点修改.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E7%BA%BF%E6%AE%B5%E6%A0%91/%E5%8C%BA%E9%97%B4%E6%9F%A5%E8%AF%A2%E5%8D%95%E7%82%B9%E4%BF%AE%E6%94%B9.cpp) | 独立语法检查通过；有main，未运行 |
| 数据结构 | [权值线段树（动态开点基础版）.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E7%BA%BF%E6%AE%B5%E6%A0%91/%E6%9D%83%E5%80%BC%E7%BA%BF%E6%AE%B5%E6%A0%91%EF%BC%88%E5%8A%A8%E6%80%81%E5%BC%80%E7%82%B9%E5%9F%BA%E7%A1%80%E7%89%88%EF%BC%89.cpp) | 已整理；独立编译与运行、随机对拍通过；3例题 |
| 数据结构 | [权值线段树（合并与分裂）.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E7%BA%BF%E6%AE%B5%E6%A0%91/%E6%9D%83%E5%80%BC%E7%BA%BF%E6%AE%B5%E6%A0%91%EF%BC%88%E5%90%88%E5%B9%B6%E4%B8%8E%E5%88%86%E8%A3%82%EF%BC%89.cpp) | 独立语法检查通过；有main，未运行 |
| 数据结构 | [线段树.md](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E7%BA%BF%E6%AE%B5%E6%A0%91/%E7%BA%BF%E6%AE%B5%E6%A0%91.md) | 原有说明/代码块，未逐块验证 |
| 数据结构 | [线段树优化建图.cpp](%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%20/%E7%BA%BF%E6%AE%B5%E6%A0%91/%E7%BA%BF%E6%AE%B5%E6%A0%91%E4%BC%98%E5%8C%96%E5%BB%BA%E5%9B%BE.cpp) | 独立语法检查通过；有main，未运行 |
| 数论 | [CRT（中国剩余定理）.cpp](%E6%95%B0%E8%AE%BA/CRT%EF%BC%88%E4%B8%AD%E5%9B%BD%E5%89%A9%E4%BD%99%E5%AE%9A%E7%90%86%EF%BC%89.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 数论 | [exgcd.md](%E6%95%B0%E8%AE%BA/exgcd.md) | 原有说明/代码块，未逐块验证 |
| 数论 | [数论分块.cpp](%E6%95%B0%E8%AE%BA/%E6%95%B0%E8%AE%BA%E5%88%86%E5%9D%97.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 数论 | [数论分块.md](%E6%95%B0%E8%AE%BA/%E6%95%B0%E8%AE%BA%E5%88%86%E5%9D%97.md) | 原有说明/代码块，未逐块验证 |
| 数论 | [求mo函数.cpp](%E6%95%B0%E8%AE%BA/%E6%B1%82mo%E5%87%BD%E6%95%B0.cpp) | 独立语法检查通过；无main，片段 |
| 数论 | [组合数.cpp](%E6%95%B0%E8%AE%BA/%E7%BB%84%E5%90%88%E6%95%B0.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 杂 | [dsu on tree.cpp](%E6%9D%82/dsu%20on%20tree.cpp) | 独立语法检查失败，依赖/错误待整理；有main，未运行 |
| 杂 | [kmp.cpp](%E6%9D%82/kmp.cpp) | 独立语法检查失败，依赖/错误待整理；无main，片段 |
| 杂 | [根号分治.md](%E6%9D%82/%E6%A0%B9%E5%8F%B7%E5%88%86%E6%B2%BB.md) | 原有说明/代码块，未逐块验证 |
| 杂 | [点线.cpp](%E6%9D%82/%E7%82%B9%E7%BA%BF.cpp) | 独立语法检查通过；无main，片段 |
| 杂 | [线性基.md](%E6%9D%82/%E7%BA%BF%E6%80%A7%E5%9F%BA.md) | 原有说明/代码块，未逐块验证 |

## 维护规范

[维护规范](维护规范.md) · [执行规则](AGENTS.md)。旧文件保留，新增算法先比较已有实现，每个完成整理的知识点配套真实例题和实际验证。

