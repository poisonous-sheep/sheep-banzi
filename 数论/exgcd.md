## 📘 扩展欧几里得算法 (Extended Euclidean Algorithm)

### 1. 核心模板 (C++17) 🛠️

使用了 C++17 的 `std::array` 和结构化绑定，代码极简。

```cpp
#include <array>
#include <iostream>

using i64 = long long;

/**
 * @brief 扩展欧几里得算法
 * @param a, b 两个整数
 * @return std::array<i64, 3> {gcd(a, b), x, y}
 * @note 求解 ax + by = gcd(a, b) 的一组整数解 (x, y)
 */
std::array<i64, 3> exgcd(i64 a, i64 b) {
    if (b == 0) {
        return {a, 1, 0}; // 边界：gcd(a, 0) = a, a*1 + 0*0 = a
    }
    // 递归求解：bx' + (a%b)y' = gcd
    auto [g, x, y] = exgcd(b, a % b);
    // 递推公式：x = y', y = x' - (a/b) * y'
    return {g, y, x - a / b * y};
}

```

### 2. 原理简述 💡

贝祖定理指出，对于任意整数 ，存在整数  使得 。
`exgcd` 函数利用递归方式求解该方程：

1. **递归基**：当  时，，显然  是一组解。
2. **递归步**：
* 假设我们在下一层递归算出了 。
* 因为 。
* 代入整理得：。
* 对比系数可知：当前层的 ，当前层的 。



### 3. 常用应用：求乘法逆元 🔢

在模  意义下，如果  和  互质（即 ），则存在  使得 。这个  即为  的逆元。

```cpp
/**
 * @brief 求 a 在模 m 下的乘法逆元
 * @return 逆元 x (0 <= x < m)，如果不存在返回 -1
 */
i64 modInverse(i64 a, i64 m) {
    auto [g, x, y] = exgcd(a, m);
    if (g != 1) return -1; // 不互质，不存在逆元
    return (x % m + m) % m; // 调整 x 到 [0, m-1] 的正整数范围内
}

```

### 4. 使用示例 (Example) ✅

```cpp
int main() {
    i64 a = 3, m = 11;
    i64 inv = modInverse(a, m);
    
    if (inv != -1) {
        std::cout << a << " 在模 " << m << " 下的逆元是: " << inv << std::endl;
        // 验证: (3 * 4) % 11 = 12 % 11 = 1
    } else {
        std::cout << "逆元不存在" << std::endl;
    }
    return 0;
}

```

---

你可以把这个作为一个单独的 `Math.md` 或者放在你的算法模板库 `Algo/Math/exgcd.cpp` 里！ 🌟
