// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// UVA1608 Non-boring sequences
// 原题：https://onlinejudge.org/external/16/1608.pdf
// 所属知识点：启发式分治；使用模板：HeuristicDivide
// 题意：判定任意子区间是否都有只出现一次的值。
// 转化：选当前区间唯一值为分界，含分界的所有区间已合法，只递归左右。
// 调用：init后non_boring，多测输出non-boring或boring。
// 复杂度：O(n log n)时间、O(n)空间。
void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        HeuristicDivide t;
        t.init(a);
        cout << (t.non_boring() ? "non-boring" : "boring") << '\n';
    }
}
