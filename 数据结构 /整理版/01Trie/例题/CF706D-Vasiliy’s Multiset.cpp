// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF706D Vasiliy’s Multiset
// 原题：https://codeforces.com/problemset/problem/706/D
// 所属知识点：01Trie；使用模板：Trie
// 题意：初始有0的集合，支持增删和最大异或。
// 转化：Trie逐位优先走相反位，贪心取得最大异或值。
// 调用：init，update(0)；+用update，-用eras，?用qur。
// 复杂度：O(qB)时间、O(qB)空间。
void solve() {
    int q;
    cin >> q;
    Trie tr(30);
    tr.update(0);
    while (q--) {
        char op;
        int x;
        cin >> op >> x;
        if (op == '+')
            tr.update(x);
        else if (op == '-')
            tr.eras(x);
        else
            cout << tr.qur(x) << '\n';
    }
}
