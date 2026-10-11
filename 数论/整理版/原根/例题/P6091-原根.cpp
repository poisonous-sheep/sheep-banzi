// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P6091 原根
// 原题：https://www.luogu.com.cn/problem/P6091
// 所属知识点：原根；使用模板：PrimitiveRoot
// 题意：求全部原根数量，并输出排序后每第d个原根。
// 转化：求一原根后，互质指数生成全部原根。
// 调用：all(n)，输出size与下标d-1,2d-1,...。
// 复杂度：按模板找根与枚举复杂度。
void solve() {
    int T;
    cin >> T;
    PrimitiveRoot p;
    while (T--) {
        int n, d;
        cin >> n >> d;
        auto a = p.all(n);
        cout << a.size() << '\n';
        for (int i = d - 1; i < (int)a.size(); i += d)
            cout << a[i] << ' ';
        cout << '\n';
    }
}
