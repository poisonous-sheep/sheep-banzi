struct node {
    int l, r;
    mutable int v;
    bool operator < (const node& o) const {
        return l < o.l;
    }
};
set<node> odt;

auto split(int x) {
    auto it = odt.lower_bound({x, 0, 0});
    if (it != odt.end() && it->l == x) return it;
    it--;  // 找到左端点
    int l = it->l, r = it->r, v = it->v;
    odt.erase(it);
    odt.insert({l, x - 1, v});
    return odt.insert({x, r, v}).first;
}  // 从x点吧这个区间分开，返回从 x开始的迭代器

void assign(int l, int r, int v) {
    auto itr = split(r + 1), itl = split(l);
    odt.erase(itl, itr);  // 把l-r的元素都删除
    odt.insert({l, r, v});
}
//查询l，r区间的东西
void perform(int l, int r) {
    auto itr = split(r + 1), itl = split(l);
    for (; itl != itr; ++itl) {
        // Perform Operations here
    }
}
