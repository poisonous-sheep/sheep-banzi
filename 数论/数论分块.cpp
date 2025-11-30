void solve() {
  int n;
  cin >> n;
  ll sum = 0;
  for (int l = 1; l <= n; i++) {
    int d = n / l, r = n / d;
    // 里面是要计算的内容,用求和举例子
    sum += (l - r + 1) * d;
    l = r;
  }
}
