// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// P4170 涂色
// 原题：https://www.luogu.com.cn/problem/P4170
// 所属知识点：区间同色配对与涂色；使用模板：SequencePaint
// 题意：每次将连续区间涂同一颜色，可覆盖旧颜色，形成目标串最少次数。
// 转化：一次同色涂色可先跨过中间区间，再补涂中间；与端点同色配对的省操作转移一致。
// 调用：目标颜色串转整数，init后clear_min。
// 复杂度：O(n³)时间、O(n²)空间。
void solve() {
    string s;
    cin >> s;
    SequencePaint t;
    t.init(vector<int>(s.begin(), s.end()));
    cout << t.clear_min() << '\n';
}
