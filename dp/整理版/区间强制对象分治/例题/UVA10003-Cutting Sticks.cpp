// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。
// UVA10003 Cutting Sticks
// 原题：https://onlinejudge.org/external/100/10003.pdf
// 所属知识点：区间强制对象分治；使用模板：IntervalSplit
// 题意：在给定位置切断木棍，每次费用为正在切的那段长度，选切割顺序使总费用最小。
// 转化：把第一次切割k作为分界，左右后续独立。沿用相同dfs分界框架，将费用替换为两侧边界长度，允许分界为全部待切点。
// 调用：循环读length直到0，读q和切点，init_cuts，run，输出指定英文句式。
// 复杂度：O(q³)时间/O(q²)空间。
void solve() {
    int length;
    while (cin >> length && length) {
        int q;
        cin >> q;
        vector<int> cuts(q);
        for (int &x : cuts)
            cin >> x;
        IntervalSplit t;
        t.init_cuts(length, cuts);
        cout << "The minimum cutting is " << t.run() << ".\n";
    }
}
