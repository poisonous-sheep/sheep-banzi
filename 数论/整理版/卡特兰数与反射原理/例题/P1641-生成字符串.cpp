// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1641 生成字符串
// 原题：https://www.luogu.com.cn/problem/P1641
// 所属知识点：卡特兰数与反射原理；使用模板：Catalan
// 题意：由n个A和m个B组成字符串，每个前缀A数不少于B数。
// 转化：将A/B映射上/下步；总数减去第一次越界后反射的非法路径数。
// 调用：ballot(n,m,20100403)，不等数量也可使用。
// 复杂度：O(n+m)时间与空间。
void solve() {
    int n, m;
    cin >> n >> m;
    Catalan t;
    cout << t.ballot(n, m, 20100403) << '\n';
}
