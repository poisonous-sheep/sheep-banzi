ll fac[N+10], fnv[N+10];

void init() {
  fac[0] = 1;
  rep(1, N) fac[i] = fac[i - 1] * i % mod;
  fnv[N] = qpow(fac[N], mod - 2);
  lep(N, 1) fnv[i - 1] = fnv[i] * i % mod;
  assert(fnv[0] == 1);
}

ll binom(int n, int m) {
  if (m < 0 || m > n)
    return 0;
  return fac[n] * fnv[m] % mod * fnv[n - m] % mod;
}
