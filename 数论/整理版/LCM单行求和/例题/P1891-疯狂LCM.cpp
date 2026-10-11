// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P1891 疯狂LCM
// 原题：https://www.luogu.com.cn/problem/P1891
// 所属知识点：LCM单行求和；使用模板：LCMSumRow
// 题意：最多300000次查询n≤1000000的单行LCM和。
// 转化：与SP5971使用同一约数和预处理；本题大量查询不可逐次试除，必须一次筛到最大n。
// 调用：读全部n，init(max n)，依次qur并精确输出。
// 复杂度：O(N log N+T)时间、O(N+T)空间。
void solve() {
    int T;
    cin >> T;
    vector<int> a(T);
    for (int &x : a)
        cin >> x;
    LCMSumRow t;
    t.init(*max_element(a.begin(), a.end()));
    for (int x : a) {
        print128(t.qur(x));
        cout << '\n';
    }
}
