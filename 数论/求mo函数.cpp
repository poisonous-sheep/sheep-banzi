const int N = 1e6 + 5;

int mu[N];          // mu[i] 表示莫比乌斯函数 μ(i)
int primes[N];      // 存储质数
int cnt;            // 质数个数
bool vis[N];        // vis[i] = 1 表示 i 是合数

void get_mu(int n) {
    // μ(1) = 1
    mu[1] = 1;

    for (int i = 2; i <= n; i++) {

        // 如果 i 没有被筛掉，说明 i 是质数
        if (!vis[i]) {
            primes[++cnt] = i;

            // 质数只有一个不同质因子
            // μ(p) = (-1)^1 = -1
            mu[i] = -1;
        }

        // 欧拉筛：用 i 去乘已经找到的质数
        for (int j = 1; j <= cnt && i * primes[j] <= n; j++) {

            int p = primes[j];

            // i * p 一定是合数
            vis[i * p] = 1;

            if (i % p == 0) {
                /*
                    p 已经是 i 的质因子

                    i 中已经有一个 p
                    现在再乘一个 p

                    所以 i * p 中一定含有 p^2

                    根据莫比乌斯函数定义：
                    如果一个数含有平方质因子，则 μ = 0
                */
                mu[i * p] = 0;

                /*
                    欧拉筛中：
                    每个合数只让它的最小质因子筛一次

                    所以这里必须 break
                */
                break;
            } else {
                /*
                    p 不是 i 的质因子

                    那么 i * p 相比 i，
                    多了一个“新的不同质因子”

                    不同质因子个数 +1，
                    奇偶性发生变化

                    所以 μ 的符号翻转
                */
                mu[i * p] = -mu[i];
            }
        }
    }
}
