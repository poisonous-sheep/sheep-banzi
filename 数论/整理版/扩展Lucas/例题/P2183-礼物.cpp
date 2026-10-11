// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P2183 礼物
// 原题：https://www.luogu.com.cn/problem/P2183
// 所属知识点：扩展Lucas；使用模板：ExLucas
// 题意：n件不同礼物分给m人，每人指定件数，模合数p求方案。
// 转化：多项式系数可写成依次选人的组合数连乘；同一个模数复用预处理。
// 调用：先判断需求总和<=n；逐人binom(remaining,wi)后扣减。
// 复杂度：预处理一次，加m次组合数查询；空间Σp^e。
void solve() {
    int p, n, m;
    cin >> p >> n >> m;
    vector<int> w(m);
    int sum = 0;
    for (int &x : w) {
        cin >> x;
        sum += x;
    }
    if (sum > n) {
        cout << "Impossible\n";
        return;
    }
    ExLucas c;
    c.init(p);
    int ans = 1 % p;
    for (int x : w) {
        ans = (__int128)ans * c.binom(n, x) % p;
        n -= x;
    }
    cout << ans << '\n';
}
