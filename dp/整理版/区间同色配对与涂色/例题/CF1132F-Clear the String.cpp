// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// CF1132F Clear the String
// 原题：https://codeforces.com/contest/1132/problem/F
// 所属知识点：区间同色配对与涂色；使用模板：SequencePaint
// 题意：每次删除一段相同字符，求清空字符串最少次数。
// 转化：先清空两个同色位置中间内容，使两端可共同删除，节省一次。
// 调用：字符转整数，init后clear_min。
// 复杂度：O(n³)时间、O(n²)空间。
void solve() {
    int n;
    string s;
    cin >> n >> s;
    SequencePaint t;
    t.init(vector<int>(s.begin(), s.end()));
    cout << t.clear_min() << '\n';
}
