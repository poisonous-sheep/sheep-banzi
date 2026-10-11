// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4317 花神的数论题
// 原题：https://www.luogu.com.cn/problem/P4317
// 所属知识点：二进制位贡献与Popcount计数；使用模板：PopcountDP
// 题意：将1..N每个数的二进制1的个数相乘，模10000007。
// 转化：按popcount=k分组，每类贡献k^计数；需要精确计数作为指数。
// 调用：distribution(N)，从k=1累乘powmod(k,cnt[k])。
// 复杂度：O(log² N)时间/空间。
void solve() {
    int N;
    cin >> N;
    PopcountDP t(10000007);
    auto cnt = t.distribution(N);
    int ans = 1;
    for (int k = 1; k < (int)cnt.size(); k++)
        ans = (__int128)ans * t.powmod(k, cnt[k]) % t.mod;
    cout << ans << '\n';
}
