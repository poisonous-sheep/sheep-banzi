// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1044 栈
// 原题：https://www.luogu.com.cn/problem/P1044
// 所属知识点：卡特兰数与反射原理；使用模板：Catalan
// 题意：顺序入栈的n个数有多少种合法出栈序列。
// 转化：入栈和出栈分别是上步和下步，任意前缀不能出栈多于入栈。
// 调用：调用exact(n)。
// 复杂度：O(n)时间、O(1)空间。
void solve() {
    int n;
    cin >> n;
    Catalan t;
    cout << t.exact(n) << '\n';
}
