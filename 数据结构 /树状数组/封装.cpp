template <typename T>
struct BIT {
  int n;
  vector<T> a; 

  BIT(int n_ = 0) { init(n_); }

  void init(int n_) {
    n = n_;
    a.assign(n + 1, T{});
  }
  void add(int x, const T &v) {
    // x 已经是 1-based，直接开始循环
    for (int i = x; i <= n; i += i & -i) {
      a[i] = a[i] + v; // 访问 1-based 的 a[i]
    }
  }

  T sum(int x) {
    T ans{};
    // x 已经是 1-based，直接开始循环
    for (int i = x; i > 0; i -= i & -i) {
      ans = ans + a[i]; // 访问 1-based 的 a[i]
    }
    return ans;
  }

  T rangeSum(int l, int r) {
    if (l > r)
      return T{};
    // [l, r] 的和 = sum(r) - sum(l - 1)
    return sum(r) - sum(l - 1);
  }
  //找到树状数组1-i中第一个小于k的数
  int select(const T &k) {
    int x = 0;
    T cur{};
    for (int i = 1 << int(std::log2(n + 0.5)); i; i /= 2) {
      if (x + i <= n && cur + a[x + i] <= k) {
        x += i;
        cur = cur + a[x];
      }
    }
    return x; 
  }
};
