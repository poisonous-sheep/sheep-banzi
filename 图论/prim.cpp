ll prim() {
    vector<ll> dist(n + 1, INF);
    set<pll> st;
    bitset<N> vis;
    dist[1] = 0;
    ll ans = 0;
    rep(1, n) st.insert({dist[i], i});
    for (int i = 1; i <= n; i++) {
        int x = st.begin()->second;
        ll d = st.begin()->first;
        if (d == INF) return -1;
        st.erase(st.begin());
        ans += dist[x];
        vis[x] = 1;
        for (auto [v, w] : edge[x]) {
            if (!vis[v] &&  w < dist[v]) {
                st.erase({dist[v], v});
                dist[v] = w;
                st.insert({dist[v], v});
            }
        }
    }
    return ans;
}
