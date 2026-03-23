#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef double db;
const db EPS = 1e-9;

// 精度比较函数
inline int sign(db a) { return a < -EPS ? -1 : a > EPS ? 1 : 0; }
inline int cmp(db a, db b) { return sign(a - b); }

// ==================== 点与向量基础 ====================
struct P {
    db x, y;
    P() { x = 0, y = 0; }
    P(db _x, db _y) : x(_x), y(_y) {}
    
    // 基本运算符重载 (加上 const 保证能在 sort 等标准库中安全传递)
    P operator+(const P &p) const { return {x + p.x, y + p.y}; }
    P operator-(const P &p) const { return {x - p.x, y - p.y}; }
    P operator*(db d) const { return {x * d, y * d}; }
    P operator/(db d) const { return {x / d, y / d}; }

    // 比较运算符 (常用于去重或求凸包前的基础排序)
    bool operator<(const P &p) const {
        int c = cmp(x, p.x);
        if (c) return c == -1;
        return cmp(y, p.y) == -1;
    }
    bool operator==(const P &o) const {
        return cmp(x, o.x) == 0 && cmp(y, o.y) == 0;
    }

    // 点积与叉积
    db dot(const P &p) const { return x * p.x + y * p.y; }
    db det(const P &p) const { return x * p.y - y * p.x; }

    // 距离与模长
    db abs2() const { return x * x + y * y; }
    db abs() const { return sqrt(abs2()); }
    db distTo(const P &p) const { return (*this - p).abs(); }
    
    // 角度与旋转
    db alpha() const { return atan2(y, x); }
    P rot90() const { return P(-y, x); }
    P rot(db an) const { return {x * cos(an) - y * sin(an), x * sin(an) + y * cos(an)}; }
    P unit() const { return *this / abs(); }
    
    // 象限判定 (用于极角排序)
    // 1表示上半平面(含正x轴)，0表示下半平面(含负x轴)
    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
    
    // 输入输出
    void read() { cin >> x >> y; }
    void write() const { cout << "(" << x << "," << y << ")" << "\n"; }
};

// ==================== 极角排序比较函数 ====================
// 标准极角排序：从 x 轴正半轴开始，逆时针方向
bool polar_cmp(const P &a, const P &b) {
    int qa = a.quad(), qb = b.quad();
    if (qa != qb) return qa > qb;      // 上半平面排在下半平面之前
    int d = sign(a.det(b));
    if (d != 0) return d > 0;          // 逆时针排序，叉积 > 0
    return a.abs2() < b.abs2();        // 极角相同，按距离从小到大排
}

// ==================== 叉积宏定义 ====================
// cross: 计算 p1p2 与 p1p3 的叉积
#define cross(p1, p2, p3) ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y))
#define crossOp(p1, p2, p3) sign(cross(p1, p2, p3))

// ==================== 直线与线段相交 ====================
// 判断两直线是否相交 (p1p2 与 q1q2)
bool chkLL(P p1, P p2, P q1, P q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return sign(a1 + a2) != 0;
}

// 求两直线的交点 (需保证直线不平行，可先用 chkLL 判断)
P isLL(P p1, P p2, P q1, P q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 快速排斥实验 (一维投影相交判断)
bool intersect(db l1, db r1, db l2, db r2) {
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    return !(cmp(r1, l2) == -1 || cmp(r2, l1) == -1);
}

// 判断线段是否相交 (包含端点相交)
bool isSS(P p1, P p2, P q1, P q2) {
    return intersect(p1.x, p2.x, q1.x, q2.x) && intersect(p1.y, p2.y, q1.y, q2.y) &&
           crossOp(p1, p2, q1) * crossOp(p1, p2, q2) <= 0 &&
           crossOp(q1, q2, p1) * crossOp(q1, q2, p2) <= 0;
}

// 判断线段是否严格相交 (不包含端点相交和共线重叠)
bool isSS_strict(P p1, P p2, P q1, P q2) {
    return crossOp(p1, p2, q1) * crossOp(p1, p2, q2) < 0 &&
           crossOp(q1, q2, p1) * crossOp(q1, q2, p2) < 0;
}

// ==================== 点与线段的位置关系 ====================
// 判断坐标/点是否在边界内
bool isMiddle(db a, db m, db b) {
    return sign(a - m) == 0 || sign(b - m) == 0 || (a < m != b < m);
}
bool isMiddle(P a, P m, P b) {
    return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);
}

// 判断点 q 是否在线段 p1p2 上 (包含端点)
bool onSeg(P p1, P p2, P q) {
    return crossOp(p1, p2, q) == 0 && isMiddle(p1, q, p2);
}

// 判断点 q 是否严格在线段 p1p2 上 (不包含端点)
bool onSeg_strict(P p1, P p2, P q) {
    return crossOp(p1, p2, q) == 0 && sign((q - p1).dot(q - p2)) < 0;
}

// ==================== 投影与距离 ====================
// 求点 q 到直线 p1p2 的投影点
P proj(P p1, P p2, P q) {
    P dir = p2 - p1;
    return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}

// 求点 q 关于直线 p1p2 的对称点
P reflect(P p1, P p2, P q) {
    return proj(p1, p2, q) * 2 - q;
}

// 求点 q 到线段 p1p2 的最短距离
db nearest(P p1, P p2, P q) {
    P h = proj(p1, p2, q);
    if (isMiddle(p1, h, p2)) // 投影点在线段上
        return q.distTo(h);
    return min(q.distTo(p1), q.distTo(p2)); // 投影点不在线段上，取端点较近者
}

// 求线段 p1p2 到线段 q1q2 的最短距离
db disSS(P p1, P p2, P q1, P q2) {
    if (isSS(p1, p2, q1, q2)) return 0; // 若相交距离为0
    return min({nearest(p1, p2, q1), nearest(p1, p2, q2), 
                nearest(q1, q2, p1), nearest(q1, q2, p2)});
}
