from common import *

select=r'''
struct TreePathSelect {
    struct info {int x,y,w;};
    int n,lg,timer;vector<vector<int>>e;vector<vector<info>>path;
    vector<int>fa,dep,l,r,dp,sdp,bit;vector<vector<int32_t>>up;
    TreePathSelect(int n=0){init(n);}
    void init(int n_){n=n_;lg=1;while((1LL<<lg)<=n)lg++;timer=0;e.assign(n+1,{});path.assign(n+1,{});
        fa.assign(n+1,0);dep=fa;l=fa;r=fa;dp=fa;sdp=fa;bit.assign(n+2,0);up.assign(lg,vector<int32_t>(n+1));}
    void add_edge(int u,int v){e[u].push_back(v);e[v].push_back(u);}
    void build(int u,int p){fa[u]=p;dep[u]=dep[p]+1;l[u]=++timer;up[0][u]=p;
        for(int k=1;k<lg;k++)up[k][u]=up[k-1][up[k-1][u]];
        for(int v:e[u])if(v!=p)build(v,u);r[u]=timer;}
    void build(int root=1){timer=0;build(root,0);}
    int lca(int x,int y){if(dep[x]<dep[y])swap(x,y);int d=dep[x]-dep[y];for(int k=0;k<lg;k++)if(d>>k&1)x=up[k][x];
        if(x==y)return x;for(int k=lg-1;k>=0;k--)if(up[k][x]!=up[k][y]){x=up[k][x];y=up[k][y];}return fa[x];}
    void add_path(int x,int y,int w){path[lca(x,y)].push_back({x,y,w});}
    void change(int x,int v){for(;x<=n+1;x+=x&-x)bit[x]+=v;}
    int qur(int x){int ans=0;for(;x;x-=x&-x)ans+=bit[x];return ans;}
    void dfs(int u,bool fast){sdp[u]=0;for(int v:e[u])if(v!=fa[u]){dfs(v,fast);sdp[u]+=dp[v];}dp[u]=sdp[u];
        for(auto p:path[u]){int tmp=sdp[u]+p.w;
            if(fast)tmp+=qur(l[p.x])+qur(l[p.y]);
            else{int x=p.x,y=p.y;while(x!=u){tmp+=sdp[x]-dp[x];x=fa[x];}while(y!=u){tmp+=sdp[y]-dp[y];y=fa[y];}}
            dp[u]=max(dp[u],tmp);}
        if(fast){int delta=sdp[u]-dp[u];change(l[u],delta);change(r[u]+1,-delta);}}
    int run(int root=1,bool fast=true){fill(bit.begin(),bit.end(),0);dfs(root,fast);return dp[root];}
};
'''
add('dp','树上不相交给定路径','TreePathSelect',select,'选择给定带权路径，每个顶点至多使用一次。在LCA处决策，沿路径累加sdp-dp；保留课堂逐点版并提供DFS序树状数组优化。','build O(n log n)；逐点版O(nm)，fast版O((n+m)log n)；空间O(n log n+m)。',
 [('add_edge(u,v); build(root)','先建树，计算父亲、LCA与DFS序'),('add_path(x,y,w)','将给定路径挂到其LCA，须先build'),('run(root,fast)','返回最大权值和；false使用原逐点delta，true使用树状数组')],
 ['点不相交，不能换成仅边不相交。','树状数组对子树加delta；查询端点时，尚未处理的当前LCA及更高祖先不会被计入。','可不选任何路径，所以负权自然被忽略。','长链递归有栈溢出风险。HDU原站本次不可访问，题目输入格式保留待原站复核状态。'],['dp/树形动态规划进阶_比赛板子.md','代码源272（原题不可访问，按已存课堂模型整理）'],[
 example('HDU5293','Tree chain problem','https://acm.hdu.edu.cn/showproblem.php?pid=5293','树上给出带权链，选择顶点互不相交的链使权值和最大。','与课堂路径1的点不相交带权模型一致；delta之和扣掉所选路径占用顶点造成的子树最优损失。','读T；每组n,m、n-1条边、m条x,y,w；build后add_path，run使用优化版。','O((n+m)log n)时间、O(n log n+m)空间。',r'''
 void solve(){int T;cin>>T;while(T--){int n,m;cin>>n>>m;TreePathSelect t(n);for(int i=1;i<n;i++){int u,v;cin>>u>>v;t.add_edge(u,v);}t.build();while(m--){int x,y,w;cin>>x>>y>>w;t.add_path(x,y,w);}cout<<t.run()<<'\n';}}
 ''',tests=[dict(input='1\n3 3\n1 2\n1 3\n2 3 5\n2 2 4\n3 3 4\n',output='8\n')]),
 example('HDU4912','Paths on the tree','https://acm.hdu.edu.cn/showproblem.php?pid=4912','从给定树上路径中选尽量多条，使所选路径顶点互不相交。','把每条路径权重设为1就是同一带权选择问题；原题可用贪心，本例展示通用DP的等权特例。','循环到EOF读n,m及树边、路径端点；build，add_path(x,y,1)，run。','O((n+m)log n)时间、O(n log n+m)空间。',r'''
 void solve(){int n,m;while(cin>>n>>m){TreePathSelect t(n);for(int i=1;i<n;i++){int u,v;cin>>u>>v;t.add_edge(u,v);}t.build();while(m--){int x,y;cin>>x>>y;t.add_path(x,y,1);}cout<<t.run()<<'\n';}}
 ''',tests=[dict(input='3 3\n1 2\n1 3\n2 3\n2 2\n3 3\n',output='2\n')])])

cover=r'''
struct AncestorCover {
    struct node{int ls=0,rs=0,dist=1,key=0,lazy=0,top=0;};
    static constexpr int INF=4000000000000000000LL;
    int n,answer;bool ok;vector<vector<int>>son;vector<vector<pair<int,int>>>path;
    vector<int>dep,rt;vector<vector<int>>dp;vector<node>tr;
    AncestorCover(int n=0){init(n);}
    void init(int n_){n=n_;son.assign(n+1,{});path.assign(n+1,{});dep.assign(n+1,0);rt=dep;dp.assign(n+1,{});tr.assign(1,node{});tr[0].dist=0;}
    void add_edge(int u,int v){son[u].push_back(v);}
    void build(int u=1){for(int v:son[u]){dep[v]=dep[u]+1;build(v);}}
    void add_path(int bottom,int top,int cost){assert(cost>=0);path[bottom].push_back({dep[top],cost});}
    void dfs(int u){int L=dep[u]+1;dp[u].assign(L+1,INF);dp[u][L]=0;
        for(auto [d,w]:path[u])dp[u][d]=min(dp[u][d],w);
        for(int v:son[u]){dfs(v);vector<int>a=dp[u],b=dp[v],sa(L+2,INF),sb(L+2,INF);
            for(int k=L;k>=0;k--){sa[k]=min(sa[k+1],a[k]);sb[k]=min(sb[k+1],b[k]);}
            for(int k=0;k<=L;k++)dp[u][k]=min(INF,min(a[k]+sb[k],b[k]+sa[k]));}
        dp[u][L]=INF; // 返回父亲前，u必须已经被覆盖。
    }
    int run(int root=1){dfs(root);int z=*min_element(dp[root].begin(),dp[root].end());return z>=INF?-1:z;}
    void apply(int p,int v){if(p){tr[p].key+=v;tr[p].lazy+=v;}}
    void push(int p){if(tr[p].lazy){apply(tr[p].ls,tr[p].lazy);apply(tr[p].rs,tr[p].lazy);tr[p].lazy=0;}}
    int merge(int x,int y){if(!x||!y)return x+y;if(tr[x].key>tr[y].key)swap(x,y);push(x);tr[x].rs=merge(tr[x].rs,y);
        if(tr[tr[x].ls].dist<tr[tr[x].rs].dist)swap(tr[x].ls,tr[x].rs);tr[x].dist=tr[tr[x].rs].dist+1;return x;}
    int pop(int x){push(x);return merge(tr[x].ls,tr[x].rs);}
    void dfs_heap(int u){rt[u]=0;for(int v:son[u]){dfs_heap(v);rt[u]=merge(rt[u],rt[v]);}
        for(auto [d,w]:path[u]){node a;a.key=w;a.top=d;tr.push_back(a);rt[u]=merge(rt[u],tr.size()-1);}
        while(rt[u]&&tr[rt[u]].top>dep[u])rt[u]=pop(rt[u]);
        if(!rt[u]){ok=false;return;}int val=tr[rt[u]].key;answer+=val;apply(rt[u],-val);
    }
    int run_heap(int root=1){tr.assign(1,node{});tr[0].dist=0;answer=0;ok=true;dfs_heap(root);return ok?answer:-1;}
};
'''
add('dp','祖先路径最小费用覆盖','AncestorCover',cover,'从给定非负费用祖先—后代路径中选若干条覆盖全部点，可重叠。保留最高到达深度DP，补充适合大数据的可并堆费用扣减版。','深度DP O(n²+m)时间/最坏O(n²)空间；可并堆O((n+m)log(m+1))时间/O(n+m)空间。',
 [('add_edge(父,子); build(root)','先建有根树与深度'),('add_path(bottom,top,cost)','top必须是bottom祖先或自身；费用非负'),('run(root)','课堂深度DP，小数据；-1表示无解'),('run_heap(root)','大数据可并堆版；根也需要覆盖')],
 ['原稿merge只有f[k]+后缀min(child)一侧；必须补child[k]+后缀min(f)。','合并前哨兵表示u未覆盖，合并后必须禁用该哨兵才能返回父亲。','堆中的费用是剩余费用：各子树先缴费，再把全部候选统一减去已缴最小值；每个候选只被删除一次。','边覆盖改成点覆盖时，路径最高点应为原top下方的孩子；根加费用0的单点路径。','CF1675D是所有根到叶路径费用1的特例；允许重叠的最优值等于叶子数，可切去重复前缀获得原题恰好覆盖一次的输出。','树的长链递归有栈风险。'],['dp/树形动态规划进阶_比赛板子.md','代码源273（原题不可访问，保留点覆盖模型）'],[
 example('CF1675D','Vertical Paths','https://codeforces.com/problemset/problem/1675/D','将有根树分成最少条向下的互不相交路径，输出路径划分。','每个叶子至少需要一条路径；把所有根到叶路径作为费用1候选，用覆盖接口得到叶子数。逐叶上溯切去已经覆盖的前缀，保持最优条数且每点恰好一次。','从parent确定任意root；build，每个叶子add_path(leaf,root,1)，run_heap；另用used恢复不重叠路径。','本通用调用O(n log n)时间/O(n)空间；此特例可仅用构造降为O(n)。',r'''
 void solve(){int T;cin>>T;while(T--){int n;cin>>n;AncestorCover t(n);vector<int>fa(n+1),used(n+1);int root=0;for(int u=1;u<=n;u++){cin>>fa[u];if(fa[u]==u)root=u;else t.add_edge(fa[u],u);}t.build(root);for(int u=1;u<=n;u++)if(t.son[u].empty())t.add_path(u,root,1);cout<<t.run_heap(root)<<'\n';for(int u=1;u<=n;u++)if(t.son[u].empty()){vector<int>p;int v=u;while(!used[v]){p.push_back(v);used[v]=1;if(v==root)break;v=fa[v];}reverse(p.begin(),p.end());cout<<p.size()<<'\n';for(int x:p)cout<<x<<' ';cout<<'\n';}cout<<'\n';}}
 ''',tests=[dict(input='1\n5\n3 1 3 3 1\n',output='3\n3\n3 1 2\n1\n4\n1\n5\n')]),
 example('CF671D','Roads in Yusland','https://codeforces.com/problemset/problem/671/D','给定工人各可修一条祖先路径，付费雇佣工人覆盖所有树边，求最小总费用。','把边(parent[x],x)映射为点x。u到v的边集合变成u到v下一层孩子的点路径；忽略u=v的空路径，根用免费单点覆盖。','DFS建立fa、倍增表；将v下方孩子作为top，add_path；run_heap。原题n,m≤300000，不能调用O(n²)深度DP。','O(n log n+(n+m)log(m+1))时间；O(n log n+m)空间。',r'''
 void solve(){int n,m;cin>>n>>m;vector<vector<int>>e(n+1);for(int i=1;i<n;i++){int u,v;cin>>u>>v;e[u].push_back(v);e[v].push_back(u);}AncestorCover t(n);int L=1;while((1LL<<L)<=n)L++;vector<vector<int32_t>>up(L,vector<int32_t>(n+1));function<void(int,int)>dfs=[&](int u,int p){up[0][u]=p;for(int k=1;k<L;k++)up[k][u]=up[k-1][up[k-1][u]];for(int v:e[u])if(v!=p){t.add_edge(u,v);t.dep[v]=t.dep[u]+1;dfs(v,u);}};dfs(1,0);t.add_path(1,1,0);while(m--){int u,v,c;cin>>u>>v>>c;if(u==v)continue;int x=u,d=t.dep[u]-t.dep[v]-1;for(int k=0;k<L;k++)if(d>>k&1)x=up[k][x];t.add_path(u,x,c);}cout<<t.run_heap()<<'\n';}
 ''',tests=[dict(input='6 5\n1 2\n1 3\n3 4\n4 5\n4 6\n2 1 2\n3 1 4\n4 1 3\n5 3 1\n6 3 2\n',output='8\n')])])
