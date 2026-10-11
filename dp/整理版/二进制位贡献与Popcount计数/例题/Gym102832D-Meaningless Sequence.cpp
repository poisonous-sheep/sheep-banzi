// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// Gym102832D Meaningless Sequence
// 原题：https://codeforces.com/gym/102832/problem/D
// 所属知识点：二进制位贡献与Popcount计数；使用模板：PopcountDP
// 题意：按原递推定义序列，求0..N的项和，N用二进制给出。
// 转化：递推可化为c^popcount；首次低于上界后，剩余自由位贡献(1+c)^剩余位。
// 调用：PopcountDP(1e9+7).weighted(N,c)。
// 复杂度：O(|N|)时间与空间。
void solve() {
    string N;
    int c;
    cin >> N >> c;
    PopcountDP t;
    cout << t.weighted(N, c) << '\n';
}
