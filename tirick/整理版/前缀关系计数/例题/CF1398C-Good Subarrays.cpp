// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1398C Good Subarrays
// 原题：https://codeforces.com/problemset/problem/1398/C
// 所属知识点：前缀关系计数；使用模板：PrefixPairs
// 题意：数字字符串中求元素和等于长度的子区间数。
// 转化：s[r]-s[l]=r-l转为s[r]-r=s[l]-l，键为前缀和减前缀长度。
// 调用：init(n+1)，add(0)，逐位计算sum-i并add，输出ans。
// 复杂度：期望O(n)时间/O(n)空间。
void solve() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        PrefixPairs t;
        t.init(n + 1);
        t.add(0);
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += s[i - 1] - '0';
            t.add(sum - i);
        }
        cout << t.ans << '\n';
    }
}
