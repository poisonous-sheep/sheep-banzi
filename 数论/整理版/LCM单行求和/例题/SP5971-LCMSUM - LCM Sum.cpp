// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// SP5971 LCMSUM - LCM Sum
// 原题：https://www.luogu.com.cn/problem/SP5971
// 所属知识点：LCM单行求和；使用模板：LCMSumRow
// 题意：多组n求lcm(1,n)+...+lcm(n,n)。
// 转化：同一筛可预处理全部约数和，适合n<=1e6的多次查询。
// 调用：读全部n，init(max n)，每次qur并print128。
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
