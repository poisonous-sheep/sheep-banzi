//我们要求n个同余线性方程组用这个算法
inline ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll d = exgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return d;
}

void merge(ll &a, ll &b, ll c, ll d) {
  if (a == -1 && b == -1)
    return;

  ll x, y;
  ll g = exgcd(b, d, x, y);
  if ((c - a) % g != 0) {
    a = -1;
    b = -1;
    return;
  }
  d /= g;
  ll t = (c - a) / g % d;
  t = (__int128)t * x % d;

  if (t < 0)
    t += d;
  a = a + (__int128)b * t;
  b = b * d;
  a = (a % b + b) % b;
}

void solve() {
  int n;
  cin >> n;
  ll a = 0, b = 1; // x mod b = a;
  rep(1, n) {
    ll c, d;
    cin >> d >> c;
    merge(a, b, c, d);
  }
  cout << a << endl;
}
