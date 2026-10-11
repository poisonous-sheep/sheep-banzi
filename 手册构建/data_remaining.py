from common import *

odt=r'''
struct ODT {
    struct node { int l,r; mutable int v; bool operator<(const node&o)const{return l<o.l;} };
    int n; set<node> odt;
    ODT(int n=0,int v=0){init(n,v);}
    void init(int n_,int v=0){n=n_;odt.clear();if(n)odt.insert({1,n,v});}
    auto split(int x){
        if(x==n+1)return odt.end();
        assert(1<=x&&x<=n);
        auto it=odt.lower_bound({x,0,0});
        if(it!=odt.end()&&it->l==x)return it;
        --it;int l=it->l,r=it->r,v=it->v;odt.erase(it);
        odt.insert({l,x-1,v});return odt.insert({x,r,v}).first;
    }
    void assign(int l,int r,int v){auto itr=split(r+1),itl=split(l);odt.erase(itl,itr);odt.insert({l,r,v});}
    void add(int l,int r,int v){auto itr=split(r+1),itl=split(l);for(;itl!=itr;++itl)itl->v+=v;}
    int kth(int l,int r,int k){
        auto itr=split(r+1),itl=split(l);vector<pair<int,int>> a;
        for(;itl!=itr;++itl)a.push_back({itl->v,itl->r-itl->l+1});
        sort(a.begin(),a.end());for(auto[v,c]:a){if(k<=c)return v;k-=c;}assert(false);return 0;
    }
    int powmod(int a,int b,int p){int r=1%p;a%=p;while(b){if(b&1)r=(__int128)r*a%p;a=(__int128)a*a%p;b>>=1;}return r;}
    int qur(int l,int r,int k,int p){auto itr=split(r+1),itl=split(l);int ans=0;
        for(;itl!=itr;++itl)ans=(ans+(__int128)(itl->r-itl->l+1)*powmod(itl->v,k,p))%p;return ans;}
};
'''
add('数据结构','珂朵莉树','ODT',odt,'用 set 保存分段常数区间；区间赋值使区间数减少，支持逐段操作。','每次 O(log n+s)，s 为访问区间数；第k小另需 O(s log s)。最坏 O(nq)，空间 O(n)。',
 [('init(n,v)','建立全值v的1..n区间'),('split(x)','在x处分割；n+1返回end'),('assign/add(l,r,v)','闭区间赋值或增加'),('kth/qur','第k小、幂次和模p')],
 ['必须先 split(r+1) 再 split(l)，否则旧迭代器可能失效。','随机数据下常用，不保证普通对抗数据的高效；P3740只有覆盖操作可另用线段树。','k必须在区间长度内，p>0；拆分不自动合并相邻等值段。'],['数据结构/珂朵莉树.cpp'],[
 example('CF896C','Willem Chtholly and Seniorious','https://codeforces.com/contest/896/problem/C','生成数组和四种随机操作，维护增加、赋值、第k小、幂和。','随机操作与大量赋值符合ODT常见使用条件；区间长度作为元素重数。','按原题顺序调用rng生成全部参数，依操作调用add、assign、kth、qur。','最坏O(nm log n)，随机数据通常区间数较少；O(n)。',r'''
 void solve(){int n,m,seed,vmax;cin>>n>>m>>seed>>vmax;
 auto rnd=[&](){int ret=seed;seed=(seed*7+13)%1000000007;return ret;};
 ODT t(n);for(int i=1;i<=n;i++)t.assign(i,i,rnd()%vmax+1);
 for(int i=0;i<m;i++){int op=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1;if(l>r)swap(l,r);
 int x=op==3?rnd()%(r-l+1)+1:rnd()%vmax+1;
 if(op==1)t.add(l,r,x);if(op==2)t.assign(l,r,x);if(op==3)cout<<t.kth(l,r,x)<<'\n';
 if(op==4){int y=rnd()%vmax+1;cout<<t.qur(l,r,x,y)<<'\n';}}
 }
 '''),
 example('P3740','贴海报','https://www.luogu.com.cn/problem/P3740','海报依次覆盖整数墙面，求最终仍可见的海报数量。','每次覆盖就是区间赋值；最终扫描不为0的段收集编号。','init(墙长,0)，第i张assign(l,r,i)，遍历odt中的v。','最坏O(nm)，O(n+m)空间；此题墙长小。',r'''
 void solve(){int n,m;cin>>n>>m;ODT t(n);for(int i=1;i<=m;i++){int l,r;cin>>l>>r;t.assign(l,r,i);}
 set<int> vis;for(auto z:t.odt)if(z.v)vis.insert(z.v);cout<<vis.size()<<'\n';}
 ''')])

rect=r'''
struct RectangleCounter {
    struct point{int x,y;};
    struct query{int l,b,r,t;};
    vector<point> a;vector<query> q;
    void init(){a.clear();q.clear();}
    void add(int x,int y){a.push_back({x,y});}
    void ask(int l,int b,int r,int t){assert(l<=r&&b<=t);q.push_back({l,b,r,t});}
    vector<int> run(){
        struct event{int x,y,id,sgn;bool strictx,stricty;};
        vector<event> e;vector<int> ys,ans(q.size());
        for(auto p:a)ys.push_back(p.y);
        for(int i=0;i<(int)q.size();i++){auto z=q[i];
            e.push_back({z.r,z.t,i,1,false,false});e.push_back({z.l,z.t,i,-1,true,false});
            e.push_back({z.r,z.b,i,-1,false,true});e.push_back({z.l,z.b,i,1,true,true});}
        sort(ys.begin(),ys.end());ys.erase(unique(ys.begin(),ys.end()),ys.end());
        sort(a.begin(),a.end(),[](point p,point q){return p.x<q.x;});
        sort(e.begin(),e.end(),[](event p,event q){if(p.x!=q.x)return p.x<q.x;return p.strictx>q.strictx;});
        vector<int> c(ys.size()+1);int j=0;
        for(auto z:e){while(j<(int)a.size()&&(a[j].x<z.x||(!z.strictx&&a[j].x==z.x))){
            int k=lower_bound(ys.begin(),ys.end(),a[j].y)-ys.begin()+1;
            for(;k<(int)c.size();k+=k&-k)c[k]++;j++;}
            int k=(z.stricty?lower_bound(ys.begin(),ys.end(),z.y):upper_bound(ys.begin(),ys.end(),z.y))-ys.begin(),s=0;
            for(;k;k-=k&-k)s+=c[k];ans[z.id]+=z.sgn*s;}
        return ans;
    }
};
'''
add('数据结构','离线二维数点','RectangleCounter',rect,'按x扫描，树状数组维护y；四次前缀容斥回答闭矩形计数，允许重复点。','O((n+q)log(n+q))时间、O(n+q)空间。',
 [('add(x,y)','加入一个点，可重复'),('ask(l,b,r,t)','加入闭矩形询问'),('run()','返回询问顺序的计数')],
 ['严格小于端点的事件在等坐标点加入前处理；无需端点减1，支持LLONG_MIN。','y仅离散化点坐标，空点集也能运行。','原笔记部分标点损坏，整理版补全了可编译事件类型。'],['数据结构/扫描线/二维数点.md'],[
 example('P2163','园丁的烦恼','https://www.luogu.com.cn/problem/P2163','查询二维平面闭矩形内树木棵数。','静态点与离线矩形查询正好对应二维前缀容斥。','逐点add，逐询问ask，run后输出每个答案。','O((n+m)log(n+m))时间与O(n+m)空间。',r'''
 void solve(){int n,m;cin>>n>>m;RectangleCounter t;while(n--){int x,y;cin>>x>>y;t.add(x,y);}while(m--){int a,b,c,d;cin>>a>>b>>c>>d;t.ask(a,b,c,d);}for(int x:t.run())cout<<x<<'\n';}
 '''),
 example('P1972','HH的项链','https://www.luogu.com.cn/problem/P1972','询问区间内不同颜色数。','颜色只统计区间内第一次出现的位置；位置i贡献当且仅当pre[i]<l且l<=i<=r。映射为点(pre[i],i)。','读数组时用map保存上次位置并add；ask(0,l,l-1,r)。','O((n+m)log(n+m))时间与O(n+m)空间。',r'''
 void solve(){int n;cin>>n;RectangleCounter t;map<int,int> pre;for(int i=1;i<=n;i++){int x;cin>>x;t.add(pre[x],i);pre[x]=i;}int m;cin>>m;while(m--){int l,r;cin>>l>>r;t.ask(0,l,l-1,r);}for(int x:t.run())cout<<x<<'\n';}
 ''')])

small=r'''
struct SmallMerge {
    int n,segments;vector<int>a,id;vector<vector<int>>pos;
    SmallMerge(int n=0){init(n);}
    void init(int n_){n=n_;a.assign(n+2,0);pos.assign(n+1,{});id.clear();segments=0;}
    void build(const vector<int>&col,int kinds){id.resize(kinds+1);iota(id.begin(),id.end(),0);pos.resize(kinds+1);
        for(int i=1;i<=n;i++){a[i]=col[i];pos[a[i]].push_back(i);segments+=(i==1||a[i]!=a[i-1]);}}
    void change(int x,int y){if(x==y)return;
        if(pos[id[x]].size()>pos[id[y]].size())swap(id[x],id[y]);
        int u=id[x],v=id[y];
        for(int p:pos[u]){if(p>1)segments-=(a[p]!=a[p-1]);if(p<n)segments-=(a[p]!=a[p+1]);
            a[p]=v;if(p>1)segments+=(a[p]!=a[p-1]);if(p<n)segments+=(a[p]!=a[p+1]);pos[v].push_back(p);}
        vector<int>().swap(pos[u]);
    }
    // 另一种容器：小map并入大map，维护最大出现次数的颜色编号和。
    struct info {map<int,int> cnt;int mx=0,sum=0;};
    static void insert(info &s,int c,int k){int x=(s.cnt[c]+=k);if(x>s.mx)s.mx=x,s.sum=c;else if(x==s.mx)s.sum+=c;}
    static void merge(info &a,info &b){if(a.cnt.size()<b.cnt.size())swap(a,b);for(auto[c,k]:b.cnt)insert(a,c,k);b=info();}
};
'''
add('数据结构','启发式合并','SmallMerge',small,'每次枚举小容器合入大容器；保留颜色桶句柄交换与map统计两个原资料模型。','位置桶总O(n log n+q)，map树上合并O(n log²n)；空间O(n+颜色数)。',
 [('build(col,kinds)','建立颜色位置桶，颜色先离散化为1..kinds'),('change(x,y)','把逻辑颜色x全部变y，交换物理桶保证小并大'),('info/insert/merge','map颜色频率统计：合并后mx及sum为众数频率与颜色和')],
 ['交换的是逻辑颜色句柄，不能简单颠倒x->y语义。','map单次操作还有log因子；复杂度不能仅写O(n log n)。','数组边界使用显式判断，不依赖颜色0哨兵。'],['数据结构/模块一_启发式合并与启发式分治.md'],[
 example('P3201','梦幻布丁','https://www.luogu.com.cn/problem/P3201','把一种颜色的全部位置改色，并查询颜色段数。','改色等价合并位置集合，段数只在搬运位置两侧变化。','离线读取操作以压缩所有颜色；build、change，查询segments。','O((n+q)log(n+q)+n log n)时间，O(n+q)空间。',r'''
 void solve(){int n,m;cin>>n>>m;vector<int>a(n+1),all;for(int i=1;i<=n;i++)cin>>a[i],all.push_back(a[i]);
 struct op{int t,x,y;};vector<op>q(m);for(auto &z:q){cin>>z.t;if(z.t==1){cin>>z.x>>z.y;all.push_back(z.x);all.push_back(z.y);}}
 sort(all.begin(),all.end());all.erase(unique(all.begin(),all.end()),all.end());auto id=[&](int x){return lower_bound(all.begin(),all.end(),x)-all.begin()+1;};
 for(int i=1;i<=n;i++)a[i]=id(a[i]);SmallMerge t(n);t.build(a,all.size());
 for(auto z:q)if(z.t==1)t.change(id(z.x),id(z.y));else cout<<t.segments<<'\n';}
 '''),
 example('CF600E','Lomsat gelral','https://codeforces.com/problemset/problem/600/E','对每棵子树求出现最多的颜色的编号和。','子树统计是孩子容器的并集；小map并入大map并维护频率最大值。','每点insert自身颜色，DFS后merge孩子；合并后记录sum。','O(n log² n)时间、O(n)活动数据与递归空间。',r'''
 void solve(){int n;cin>>n;vector<int>c(n+1),ans(n+1);for(int i=1;i<=n;i++)cin>>c[i];vector<vector<int>>g(n+1);
 for(int i=1;i<n;i++){int u,v;cin>>u>>v;g[u].push_back(v);g[v].push_back(u);}vector<SmallMerge::info>f(n+1);
 function<void(int,int)>dfs=[&](int u,int p){SmallMerge::insert(f[u],c[u],1);for(int v:g[u])if(v!=p){dfs(v,u);SmallMerge::merge(f[u],f[v]);}ans[u]=f[u].sum;};
 dfs(1,0);for(int i=1;i<=n;i++)cout<<ans[i]<<" \n"[i==n];}
 ''')])

dsu=r'''
struct DSUOnTree {
    int n,tot=0;vector<vector<int>>adj;vector<int>fa,siz,son,l,r,seq;
    DSUOnTree(int n=0){init(n);}
    void init(int n_){n=n_;tot=0;adj.assign(n+1,{});fa.assign(n+1,0);siz=son=l=r=fa;seq.assign(n+1,0);}
    void add_edge(int u,int v){adj[u].push_back(v);adj[v].push_back(u);}
    void dfs1(int u,int p){fa[u]=p;siz[u]=1;l[u]=++tot;seq[tot]=u;
        for(int v:adj[u])if(v!=p){dfs1(v,u);siz[u]+=siz[v];if(siz[v]>siz[son[u]])son[u]=v;}r[u]=tot;}
    template<class Change,class Answer>void dfs2(int u,bool keep,Change&change,Answer&answer){
        for(int v:adj[u])if(v!=fa[u]&&v!=son[u])dfs2(v,false,change,answer);
        if(son[u])dfs2(son[u],true,change,answer);
        for(int v:adj[u])if(v!=fa[u]&&v!=son[u])for(int i=l[v];i<=r[v];i++)change(seq[i],1);
        change(u,1);answer(u);
        if(!keep)for(int i=l[u];i<=r[u];i++)change(seq[i],-1);
    }
    template<class Change,class Answer>void run(Change change,Answer answer,int root=1){tot=0;fill(son.begin(),son.end(),0);dfs1(root,0);dfs2(root,false,change,answer);}
};
'''
add('数据结构','DSU on Tree','DSUOnTree',dsu,'轻子树算完清空、重子树保留，以单一统计容器回答所有子树询问。','O(n log n)次增删；总时间再乘增删与询问成本；O(n)树结构空间。',
 [('add_edge','加入无向树边'),('run(change,answer,root)','change(u,+1/-1)增删，answer(u)读取完整子树状态')],
 ['移除必须与加入完全互逆；原“直接清零”仅限清空整个容器的特定统计，不适合通用回调。','run最终清空统计；多次运行须初始化外部答案和桶。','递归深度O(n)，链树可能需要较大栈。'],['杂/dsu on tree.cpp','数据结构/模块二_DSU_on_Tree与树上统计.md'],[
 example('CF600E','Lomsat gelral','https://codeforces.com/problemset/problem/600/E','求子树众数颜色编号和。','DSU保留重子树，颜色增删同时更新每个频率的颜色和与种类数。','change维护cnt、freqSum、freqCount及mx；answer读freqSum[mx]。','O(n log n)时间、O(n+颜色值域)空间。',r'''
 void solve(){int n;cin>>n;vector<int>c(n+1),ans(n+1),cnt(n+1),fc(n+1),sum(n+1);for(int i=1;i<=n;i++)cin>>c[i];DSUOnTree t(n);
 for(int i=1;i<n;i++){int u,v;cin>>u>>v;t.add_edge(u,v);}int mx=0;
 auto change=[&](int u,int d){int x=c[u],k=cnt[x];if(k)fc[k]--,sum[k]-=x;k=cnt[x]+=d;if(k)fc[k]++,sum[k]+=x;mx=max(mx,k);while(mx&&!fc[mx])mx--;};
 auto answer=[&](int u){ans[u]=sum[mx];};t.run(change,answer);for(int i=1;i<=n;i++)cout<<ans[i]<<" \n"[i==n];}
 '''),
 example('CF375D','Tree and Queries','https://codeforces.com/contest/375/problem/D','求子树内至少出现k次的颜色种数。','单次颜色频率从x变x+1，只使“至少x+1次”计数增加，删除逆操作；无需树状数组。','change对atleast新旧边界加减；answer回答挂在该点的全部询问。','O(n log n+m)时间、O(n+m+颜色值域)空间。',r'''
 void solve(){int n,m;cin>>n>>m;DSUOnTree t(n);vector<int>c(n+1),cnt(100001),atleast(n+1),ans(m);for(int i=1;i<=n;i++)cin>>c[i];
 for(int i=1;i<n;i++){int u,v;cin>>u>>v;t.add_edge(u,v);}vector<vector<pair<int,int>>>q(n+1);
 for(int i=0;i<m;i++){int u,k;cin>>u>>k;q[u].push_back({k,i});}
 auto change=[&](int u,int d){int &x=cnt[c[u]];if(d==1)atleast[++x]++;else atleast[x--]--;};
 auto answer=[&](int u){for(auto[k,i]:q[u])ans[i]=k<=n?atleast[k]:0;};t.run(change,answer);for(int x:ans)cout<<x<<'\n';}
 ''',tests=[dict(input='4 1\n1 2 3 4\n1 2\n2 3\n3 4\n1 1\n',output='4\n')])])

sqrt=r'''
struct SqrtDivide {
    int n,B;vector<int>a;vector<vector<int>>tag;vector<vector<int32_t>>jump;
    SqrtDivide(int n=0){init(n);}
    void init(int n_){n=n_;B=sqrt(max(1LL,n))+1;a.assign(n+1,0);tag.assign(B,{});for(int i=1;i<B;i++)tag[i].assign(i,0);jump.clear();}
    void change(int x,int v){assert(1<=x&&x<=n);a[x]+=v;for(int k=1;k<B;k++)tag[k][x%k]+=v;}
    int qur(int k,int r){assert(k>0&&0<=r&&r<k);if(k<B)return tag[k][r];int ans=0;for(int i=r?r:k;i<=n;i+=k)ans+=a[i];return ans;}
    void build_jump(const vector<int>&v){a=v;jump.assign(B,vector<int32_t>(n+2));
        for(int k=1;k<B;k++)for(int i=n;i>=1;i--){int j=i+a[i]+k;jump[k][i]=1+(j<=n?jump[k][j]:0);}}
    int jump_count(int p,int k){if(k<B)return jump[k][p];int ans=0;while(p<=n)ans++,p+=a[p]+k;return ans;}
};
'''
add('杂','步长根号分治','SqrtDivide',sqrt,'小步长预维护/预处理，大步长暴力跳跃；收录动态模下标和与静态跳跃两个模型。','动态修改O(B)、查询O(1)或O(n/B)，空间O(n+B²)；跳跃预处理O(nB)、空间O(nB)，B约sqrt(n)。',
 [('change/qur','动态单点加与下标模k等于r求和'),('build_jump/jump_count','静态正数数组跳到p+a[p]+k，求越界前次数')],
 ['跳跃版必须a[i]>0，才能保证预处理依赖右侧与大步长次数界。','两个模型独立使用同一对象，不要build_jump后再用动态tag。','jump计数存int32_t避免long long宏把nB内存翻倍。'],['杂/根号分治.md'],[
 example('CF1207F','Remainder Problem','https://codeforces.com/problemset/problem/1207/F','单点增加，查询所有下标模x等于y的位置和。','小模数一次修改影响B个桶，大模数查询最多n/B个位置。','init(500000)，操作1用change，操作2用qur。','O(q sqrt N)时间、O(N)空间。',r'''
 void solve(){int q;cin>>q;SqrtDivide t(500000);while(q--){int op,x,y;cin>>op>>x>>y;if(op==1)t.change(x,y);else cout<<t.qur(x,y)<<'\n';}}
 '''),
 example('CF797E','Array Queries','https://codeforces.com/contest/797/problem/E','多次询问正数数组从p开始跳p+a[p]+k的次数。','k较小时重复查询可复用倒序DP；大k每次跳至少k格。','读数组后build_jump，再逐次jump_count。','O(n sqrt n+q sqrt n)时间、O(n sqrt n)空间。',r'''
 void solve(){int n;cin>>n;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];SqrtDivide t(n);t.build_jump(a);int q;cin>>q;while(q--){int p,k;cin>>p>>k;cout<<t.jump_count(p,k)<<'\n';}}
 ''',tests=[dict(input='3\n1 1 1\n3\n1 1\n2 1\n3 1\n',output='2\n1\n1\n')])])
