vector<int> getNext(const string &s) {
    int m = s.size();

    if (m == 1) {
        return {-1};
    }

    vector<int> nxt(m);
    nxt[0] = -1;
    nxt[1] = 0;

    int i = 2;
    int len = 0;

    while (i < m) {
        if (s[i - 1] == s[len]) {
            nxt[i++] = ++len;
        } else if (len > 0) {
            len = nxt[len];
        } else {
            nxt[i++] = 0;
        }
    }

    return nxt;
}

int kmp(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0) {
        return 0;
    }

    vector<int> nxt = getNext(pattern);

    int x = 0;
    int y = 0;

    while (x < n && y < m) {
        if (text[x] == pattern[y]) {
            x++;
            y++;
        } else if (y == 0) {
            x++;
        } else {
            y = nxt[y];
        }
    }

    return y == m ? x - m : -1;
}
