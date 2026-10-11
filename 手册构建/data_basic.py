from common import *

add('数据结构','普通线段树','SegTree',r'''
struct SegTree {
    struct info {
        int mn;
        friend info operator+(const info &l, const info &r) {
            return {min(l.mn, r.mn)};
        }
    };
    struct node { info val; };
    int n=0;
    vector<node> seg;
    SegTree(int n_=0) { init(n_); }
    void init(int n_) { n=n_; seg.assign(4*n+4,{}); }
    int ls(int id) { return id<<1; }
    int rs(int id) { return id<<1|1; }
    void update(int id) { seg[id].val=seg[ls(id)].val+seg[rs(id)].val; }
    void build(int id,int l,int r,const vector<int> &a) {
        if(l==r) { seg[id].val={a[l]}; return; }
        int mid=(l+r)>>1;
        build(ls(id),l,mid,a); build(rs(id),mid+1,r,a); update(id);
    }
    void change(int id,int l,int r,int pos,int val) {
        if(l==r) { seg[id].val={val}; return; }
        int mid=(l+r)>>1;
        if(pos<=mid) change(ls(id),l,mid,pos,val);
        else change(rs(id),mid+1,r,pos,val);
        update(id);
    }
    info qur(int id,int l,int r,int ql,int qr) {
        if(ql<=l && r<=qr) return seg[id].val;
        int mid=(l+r)>>1;
        if(qr<=mid) return qur(ls(id),l,mid,ql,qr);
        if(ql>mid) return qur(rs(id),mid+1,r,ql,qr);
        return qur(ls(id),l,mid,ql,qr)+qur(rs(id),mid+1,r,ql,qr);
    }
    void build(const vector<int> &a) { init(a.size()-1); assert(n>0); build(1,1,n,a); }
    void change(int pos,int val) { assert(1<=pos && pos<=n); change(1,1,n,pos,val); }
    info qur(int l,int r) { assert(1<=l && l<=r && r<=n); return qur(1,1,n,l,r); }
};
''','单点赋值、区间最小值；数组1-based，查询为闭区间。','建树O(n)，修改/查询O(log n)，空间O(n)。',[('build(a)','a[1..n]建树'),('change(pos,val)','单点赋值'),('qur(l,r).mn','闭区间最小值')],['n必须为正；不支持懒标记。','自定义info必须满足结合律；保留合并左右顺序。'],['数据结构/线段树/区间查询单点修改.cpp'],[
example('P1816','忠诚','https://www.luogu.com.cn/problem/P1816','询问多段账目中的最小金额。','区间最小值满足结合律，建树后直接查询。','build(a)，每个区间qur(l,r).mn。','O(n+q log n)时间、O(n)空间。',r'''void solve() {
    int n,q; cin>>n>>q; vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    SegTree seg; seg.build(a);
    while(q--) { int l,r; cin>>l>>r; cout<<seg.qur(l,r).mn<<(q?' ':'\n'); }
}'''),
example('P1198','最大数','https://www.luogu.com.cn/problem/P1198','在线追加数，查询末尾L个数的最大值；追加依赖上次答案。','把追加视为预留数组上的单点赋值，查询变为后缀区间最大值。','预留M个位置build；change(++len,x)，qur(len-L+1,len)。','O(M log M)时间、O(M)空间。',r'''void solve() {
    int m,d; cin>>m>>d; vector<int>a(m+1,LLONG_MIN);
    SegTree seg; seg.build(a); int len=0,last=0;
    while(m--) { char op; int x; cin>>op>>x;
        if(op=='A') { int v=((__int128)x+last)%d; if(v<0)v+=d; seg.change(++len,v); }
        else { last=seg.qur(len-x+1,len).mn; cout<<last<<'\n'; }
    }
}''',changes='只将info的min合并改为max；成员mn沿用原名表示最大值。',replace=[['return {min(l.mn, r.mn)};','return {max(l.mn, r.mn)};']])])

add('数据结构','区间加线段树','SegTree',r'''
struct SegTree {
    struct info {
        int sum=0,len=0;
        friend info operator+(const info &l,const info &r) { return {l.sum+r.sum,l.len+r.len}; }
    };
    struct tag { int add=0; };
    struct node { info val; tag t; };
    int n=0; vector<node> seg;
    SegTree(int n_=0) { init(n_); }
    void init(int n_) { n=n_; seg.assign(4*n+4,{}); }
    int ls(int id){return id<<1;} int rs(int id){return id<<1|1;}
    void update(int id){seg[id].val=seg[ls(id)].val+seg[rs(id)].val;}
    void settag(int id,tag t){seg[id].val.sum+=t.add*seg[id].val.len;seg[id].t.add+=t.add;}
    void pushdown(int id){if(seg[id].t.add){settag(ls(id),seg[id].t);settag(rs(id),seg[id].t);seg[id].t.add=0;}}
    void build(int id,int l,int r,const vector<int>&a){
        if(l==r){seg[id].val={a[l],1};return;}
        int mid=(l+r)>>1;build(ls(id),l,mid,a);build(rs(id),mid+1,r,a);update(id);
    }
    void modify(int id,int l,int r,int ql,int qr,tag t){
        if(ql<=l&&r<=qr){settag(id,t);return;} pushdown(id);int mid=(l+r)>>1;
        if(ql<=mid)modify(ls(id),l,mid,ql,qr,t);
        if(qr>mid)modify(rs(id),mid+1,r,ql,qr,t);update(id);
    }
    int qur(int id,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr)return seg[id].val.sum;pushdown(id);int mid=(l+r)>>1,ans=0;
        if(ql<=mid)ans+=qur(ls(id),l,mid,ql,qr);
        if(qr>mid)ans+=qur(rs(id),mid+1,r,ql,qr);return ans;
    }
    void change(int id,int l,int r,int pos,int val){
        if(l==r){seg[id].val.sum=val;seg[id].t={};return;}
        pushdown(id);int mid=(l+r)>>1;
        if(pos<=mid)change(ls(id),l,mid,pos,val);else change(rs(id),mid+1,r,pos,val);update(id);
    }
    void build(const vector<int>&a){init(a.size()-1);assert(n>0);build(1,1,n,a);}
    void modify(int l,int r,tag t){assert(1<=l&&l<=r&&r<=n);modify(1,1,n,l,r,t);}
    void change(int pos,int val){assert(1<=pos&&pos<=n);change(1,1,n,pos,val);}
    int qur(int l,int r){if(l>r)return 0;assert(1<=l&&r<=n);return qur(1,1,n,l,r);}
};
''','闭区间加、区间和、单点赋值；1-based。','建树O(n)，修改/查询O(log n)，空间O(n)。',[('modify(l,r,{x})','区间加x'),('change(pos,val)','赋值前下放标记'),('qur(l,r)','区间和')],['t.add*len与总和不得溢出long long。','进入部分区间前pushdown，回溯update。'],['数据结构/线段树/区间修改区间查询.cpp'],[
example('P3372','线段树1','https://www.luogu.com.cn/problem/P3372','区间加和区间求和。','标记可累加，区间和的变化等于增量乘长度。','build后将1操作映射modify，2操作映射qur。','O((n+m)log n)时间、O(n)空间。',r'''void solve(){int n,m;cin>>n>>m;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];SegTree seg;seg.build(a);while(m--){int op,l,r,k;cin>>op>>l>>r;if(op==1){cin>>k;seg.modify(l,r,{k});}else cout<<seg.qur(l,r)<<'\n';}}'''),
example('P3374','树状数组1','https://www.luogu.com.cn/problem/P3374','单点增加，查询区间和。','单点是长度1的区间修改，直接复用懒标记板子。','modify(x,x,{k})；qur(x,y)。','O((n+m)log n)时间、O(n)空间。',r'''void solve(){int n,m;cin>>n>>m;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];SegTree seg;seg.build(a);while(m--){int op,x,y;cin>>op>>x>>y;if(op==1)seg.modify(x,x,{y});else cout<<seg.qur(x,y)<<'\n';}}''')])

add('数据结构','树状数组','BIT',r'''
template<typename T>
struct BIT {
    int n; vector<T>a;
    BIT(int n_=0){init(n_);}
    void init(int n_){n=n_;a.assign(n+1,T{});}
    void add(int x,const T&v){assert(1<=x&&x<=n);for(int i=x;i<=n;i+=i&-i)a[i]+=v;}
    T sum(int x){assert(0<=x&&x<=n);T ans{};for(int i=x;i;i-=i&-i)ans+=a[i];return ans;}
    T rangeSum(int l,int r){return l>r?T{}:sum(r)-sum(l-1);}
    // 非负原数组：返回满足prefix(x)<=k的最大x；k>=0，结果0..n。
    int select(const T&k){
        assert(k>=T{});int x=0,step=1;T cur{};
        while(step<=n/2)step<<=1;
        for(;step;step>>=1)if(x+step<=n&&cur+a[x+step]<=k){x+=step;cur+=a[x];}
        return x;
    }
};
''','单点加、前缀和、区间和；非负频率时支持前缀排名二分。','初始化O(n)，修改/查询/select为O(log n)，空间O(n)。',[('add(x,v)','下标1..n；禁止x=0'),('sum(x)','前缀[1,x]，sum(0)=0'),('rangeSum(l,r)','闭区间和'),('select(k)','最后一个前缀和<=k的下标；第k小可用select(k-1)+1')],['原select注释含义错误，现明确边界；不用浮点log2计算最高位。','select仅用于非负频率，否则前缀不单调。'],['数据结构/树状数组/封装.cpp'],[
example('P3374','树状数组1','https://www.luogu.com.cn/problem/P3374','单点加、区间和。','将区间和拆成两段前缀和之差。','init(n)，依次add初值；操作add或rangeSum。','O((n+m)log n)时间、O(n)空间。',r'''void solve(){int n,m;cin>>n>>m;BIT<int>bit(n);for(int i=1,x;i<=n;i++){cin>>x;bit.add(i,x);}while(m--){int op,x,y;cin>>op>>x>>y;if(op==1)bit.add(x,y);else cout<<bit.rangeSum(x,y)<<'\n';}}'''),
example('P1908','逆序对','https://www.luogu.com.cn/problem/P1908','统计i<j且a[i]>a[j]的数对。','按下标插入频率，已出现数中大于当前值的数量就是新增逆序对。','离散化；ans+=已插入数-sum(pos)，再add(pos,1)。','O(n log n)时间、O(n)空间。',r'''void solve(){int n;cin>>n;vector<int>a(n),v;for(auto&x:a)cin>>x;v=a;sort(v.begin(),v.end());v.erase(unique(v.begin(),v.end()),v.end());BIT<int>bit(v.size());int ans=0;for(int i=0;i<n;i++){int p=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;ans+=i-bit.sum(p);bit.add(p,1);}cout<<ans<<'\n';}''')])

add('数据结构','并查集','DSU',r'''
struct DSU {
    vector<int>fid,sz;
    DSU(int n=0){init(n);}
    void init(int n){fid.resize(n+1);iota(fid.begin(),fid.end(),0);sz.assign(n+1,1);}
    int root(int x){return fid[x]==x?x:fid[x]=root(fid[x]);}
    bool merge(int x,int y){x=root(x);y=root(y);if(x==y)return false;if(sz[x]>sz[y])swap(x,y);fid[x]=y;sz[y]+=sz[x];return true;}
    bool same(int x,int y){return root(x)==root(y);}
    int size(int x){return sz[root(x)];}
};
''','动态合并连通块，查询连通性与大小；编号0..n均可用。','初始化O(n)，按大小合并与路径压缩均摊O(alpha(n))，空间O(n)。',[('root(x)','沿用原名，压缩路径'),('merge(x,y)','返回是否成功合并'),('same(x,y)','判断同一连通块'),('size(x)','连通块大小')],['不支持删除边；删除类题优先考虑倒序离线。','若需要回滚，应另用不压缩路径的变体。'],['数据结构/并查集/板子.cpp','数据结构/并查集/并查集.md'],[
example('practice2_a','Disjoint Set Union','https://atcoder.jp/contests/practice2/tasks/practice2_a','加无向边或询问两点是否连通。','加边只会合并连通块，适用普通DSU。','0操作merge，1操作same；题目点号0-based。','O((n+q)alpha(n))时间、O(n)空间。',r'''void solve(){int n,q;cin>>n>>q;DSU dsu(n);while(q--){int op,u,v;cin>>op>>u>>v;if(!op)dsu.merge(u,v);else cout<<dsu.same(u,v)<<'\n';}}''',tests=[['4 7\n1 0 1\n0 0 1\n0 2 3\n1 0 1\n1 1 2\n0 0 2\n1 1 3\n','0 1 0 1']]),
example('ABC120D','Decayed Bridges','https://atcoder.jp/contests/abc120/tasks/abc120_d','按顺序删桥，输出每次删除后的不连通点对数。','逆序变成加边；合并大小a,b的块减少a*b对。','从空图开始，先记答案，读取size后merge。','O((n+m)alpha(n))时间、O(n+m)空间。',r'''void solve(){int n,m;cin>>n>>m;vector<pair<int,int>>e(m);for(auto&[u,v]:e)cin>>u>>v;DSU dsu(n);vector<int>ans(m);int cur=n*(n-1)/2;for(int i=m-1;i>=0;i--){ans[i]=cur;auto[u,v]=e[i];if(!dsu.same(u,v)){cur-=dsu.size(u)*dsu.size(v);dsu.merge(u,v);}}for(int x:ans)cout<<x<<'\n';}''')])

mid=source_struct('数据结构/对顶堆（multiset维护中位数）.cpp','Mid')
add('数据结构','对顶堆与中位数','Mid',mid,'动态插入删除，查询下中位数与到中位数的绝对值和；允许重复。','增删O(log n)，mid/cost为O(1)，空间O(n)。',[('add(x)','加入一个值'),('del(x)','删除一个已存在的值'),('mid()','非空集合下中位数'),('cost()','最小绝对偏差和，空集为0')],['L大小等于R或多1，且max(L)<=min(R)。','和与代价不得溢出；删除只删除一个重复值。'],['数据结构/对顶堆（multiset维护中位数）.cpp'],[
example('ABC127F','Absolute Minima','https://atcoder.jp/contests/abc127/tasks/abc127_f','不断加入|x-a|+b，查询使函数最小的最小x及最小值。','最小x是下中位数；常数b单独累加。','add(a)，查询mid()和cost()+常数和。','O(q log q)时间、O(q)空间。',r'''void solve(){int q;cin>>q;Mid st;int bsum=0;while(q--){int op;cin>>op;if(op==1){int a,b;cin>>a>>b;st.add(a);bsum+=b;}else cout<<st.mid()<<' '<<st.cost()+bsum<<'\n';}}'''),
example('P1168','中位数','https://www.luogu.com.cn/problem/P1168','依次读入整数，对每个奇数长度前缀输出中位数。','插入后保持两个集合的大小与顺序，中位数直接取L最大值。','逐个add，奇数次插入后输出mid()。','O(n log n)时间、O(n)空间。',r'''void solve(){int n;cin>>n;Mid st;for(int i=1,x;i<=n;i++){cin>>x;st.add(x);if(i%2)cout<<st.mid()<<'\n';}}''')])

add('数据结构','01Trie','Trie',r'''
struct Trie {
    struct node { int32_t t[2]={0,0}; int cnt=0; };
    int B;vector<node>seg;
    Trie(int b=32){init(b);}
    void init(int b=32){assert(0<=b&&b<=62);B=b;seg.assign(1,{});}
    void update(int x){assert(x>=0);int u=0;seg[u].cnt++;for(int i=B;i>=0;i--){int ch=x>>i&1;if(!seg[u].t[ch]){int id=seg.size();seg.push_back({});seg[u].t[ch]=id;}u=seg[u].t[ch];seg[u].cnt++;}}
    int count(int x){int u=0;for(int i=B;i>=0;i--){int ch=x>>i&1;if(!seg[u].t[ch])return 0;u=seg[u].t[ch];}return seg[u].cnt;}
    bool eras(int x){if(!count(x))return false;int u=0;seg[u].cnt--;for(int i=B;i>=0;i--){u=seg[u].t[x>>i&1];seg[u].cnt--;}return true;}
    int qur(int x){assert(seg[0].cnt>0);int u=0,ans=0;for(int i=B;i>=0;i--){int ch=x>>i&1,to=ch^1;int v=seg[u].t[to];if(v&&seg[v].cnt){ans|=1LL<<i;u=v;}else u=seg[u].t[ch];}return ans;}
};
''','非负整数的动态可重集合与最大异或查询；最高位B<=62。','增删/查询O(B)，空间O(D*B)，删除不回收节点。',[('update(x)','插入'),('eras(x)','删除一个值，不存在时返回false且不修改状态'),('qur(x)','最大x xor y')],['删除先验证完整路径，修复原代码不存在元素时部分减计数的问题。','值必须落在0..2^(B+1)-1；B=62只支持非负long long。'],['数据结构/01tire（支持删）.cpp'],[
example('CF706D','Vasiliy’s Multiset','https://codeforces.com/problemset/problem/706/D','初始有0的集合，支持增删和最大异或。','Trie逐位优先走相反位，贪心取得最大异或值。','init，update(0)；+用update，-用eras，?用qur。','O(qB)时间、O(qB)空间。',r'''void solve(){int q;cin>>q;Trie tr(30);tr.update(0);while(q--){char op;int x;cin>>op>>x;if(op=='+')tr.update(x);else if(op=='-')tr.eras(x);else cout<<tr.qur(x)<<'\n';}}'''),
example('P4551','最长异或路径','https://www.luogu.com.cn/problem/P4551','树上找边权异或最大的路径。','两点路径异或等于根到两点的前缀异或之xor，将所有前缀放入Trie。','DFS计算前缀；update每个前缀，再qur求最大。','O(nB)时间、O(nB)空间。',r'''void solve(){int n;cin>>n;vector<vector<pair<int,int>>>e(n+1);for(int i=1,u,v,w;i<n;i++){cin>>u>>v>>w;e[u].push_back({v,w});e[v].push_back({u,w});}vector<int>d(n+1);function<void(int,int)>dfs=[&](int u,int fa){for(auto[v,w]:e[u])if(v!=fa){d[v]=d[u]^w;dfs(v,u);}};dfs(1,0);Trie tr(30);for(int i=1;i<=n;i++)tr.update(d[i]);int ans=0;for(int i=1;i<=n;i++)ans=max(ans,tr.qur(d[i]));cout<<ans<<'\n';}''')])

add('数据结构','ST表','ST',r'''
struct ST {
    struct info { int mn,mx; friend info operator+(const info&l,const info&r){return {min(l.mn,r.mn),max(l.mx,r.mx)};} };
    int n=0;vector<int>lg;vector<vector<info>>st;
    void build(const vector<int>&a){n=a.size()-1;assert(n>0);lg.assign(n+1,0);for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;st.assign(lg[n]+1,vector<info>(n+1));for(int i=1;i<=n;i++)st[0][i]={a[i],a[i]};for(int j=1;j<=lg[n];j++)for(int i=1;i+(1LL<<j)-1<=n;i++)st[j][i]=st[j-1][i]+st[j-1][i+(1LL<<(j-1))];}
    info qur(int l,int r){assert(1<=l&&l<=r&&r<=n);int k=lg[r-l+1];return st[k][l]+st[k][r-(1LL<<k)+1];}
};
''','静态区间最小值与最大值；重叠两段要求合并幂等。','建表O(n log n)，查询O(1)，空间O(n log n)。',[('build(a)','1-based数组；按实际n动态分配'),('qur(l,r)','闭区间，返回mn/mx')],['不能直接用于求和；修改数组后重建。','从原int32_t定长320MiB表改为实际规模long long表；n很大仍须评估MLE。'],['数据结构/ST表.cpp'],[
example('P3865','ST表','https://www.luogu.com.cn/problem/P3865','静态区间最大值。','max幂等，重叠查询段不会重复影响答案。','build(a)，qur(l,r).mx。','O(n log n+q)时间、O(n log n)空间。',r'''void solve(){int n,q;cin>>n>>q;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];ST st;st.build(a);while(q--){int l,r;cin>>l>>r;cout<<st.qur(l,r).mx<<'\n';}}'''),
example('P2880','Balanced Lineup','https://www.luogu.com.cn/problem/P2880','每段牛身高的最大值与最小值之差。','一次info同时维护min/max，查询后相减。','qur返回info，输出mx-mn。','O(n log n+q)时间、O(n log n)空间。',r'''void solve(){int n,q;cin>>n>>q;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];ST st;st.build(a);while(q--){int l,r;cin>>l>>r;auto v=st.qur(l,r);cout<<v.mx-v.mn<<'\n';}}''')])
