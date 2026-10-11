// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1082 同余方程
// 原题：https://www.luogu.com.cn/problem/P1082
// 所属知识点：扩展欧几里得；使用模板：Exgcd
// 题意：求ax=1 mod b的最小正整数解。
// 转化：题目互质，扩展欧几里得系数给逆元。
// 调用：inverse(a,b)，将0按正解约定改成b。
// 复杂度：O(log b)时间与空间。
void solve() {
    int a, b;
    cin >> a >> b;
    Exgcd ex;
    int x = ex.inverse(a, b);
    cout << (x == 0 ? b : x) << '\n';
}
