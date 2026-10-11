from common import *

match_basic=r'''void solve(){int n,m,q;cin>>n>>m>>q;HK hk;hk.init(n,m);while(q--){int u,v;cin>>u>>v;hk.add(u,v);}cout<<hk.matching()<<'\n';}'''
match_grid=r'''void solve(){int n,m;cin>>n>>m;vector<string>a(n);for(auto&s:a)cin>>s;HK hk;hk.init(n*m,n*m);int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i][j]=='.'&&(i+j)%2==0)for(int k=0;k<4;k++){int x=i+dx[k],y=j+dy[k];if(0<=x&&x<n&&0<=y&&y<m&&a[x][y]=='.')hk.add(i*m+j+1,x*m+y+1);}cout<<hk.matching()<<'\n';for(int u=1;u<=n*m;u++)if(hk.ml[u]){int v=hk.ml[u],x=(u-1)/m,y=(u-1)%m,p=(v-1)/m,q=(v-1)%m;if(x==p){a[x][min(y,q)]='>';a[x][max(y,q)]='<';}else{a[min(x,p)][y]='v';a[max(x,p)][y]='^';}}for(auto&s:a)cout<<s<<'\n';}'''
hk=source_struct('图论/HK二分图最大匹配.cpp','HK')
matching_examples=[example('P3386','二分图最大匹配','https://www.luogu.com.cn/problem/P3386','求左右两部图最大匹配数。','每点最多匹配一次，直接构造左到右的边。','init(n,m)，add(u,v)，matching()。','HK为O(E sqrt V)时间、O(V+E)空间。',match_basic),example('practice2_d','Maxflow','https://atcoder.jp/contests/practice2/tasks/practice2_d','障碍格盘上放最多1x2骨牌，并输出方案。','棋盘黑白染色后每个骨牌是一条二分图匹配边。','空白相邻格add；matching后从ml恢复箭头。','HK为O(E sqrt V)时间、O(V+E)空间。',match_grid)]
add('图论','Hopcroft-Karp匹配','HK',hk,'二分图最大匹配；左右编号独立且从1开始，0表示未匹配。','O(E sqrt V)时间、O(V+E)空间。',[('init(n1,n2)','清空图和匹配'),('add(u,v)','左部到右部的边'),('matching()','最大匹配数，重复调用不重复累计'),('ml/mr','匹配关系')],['只用于二分图，不用于一般图匹配。','递归增广路深度最坏O(V)，极深数据有栈风险。'],['图论/HK二分图最大匹配.cpp'],matching_examples)

kuhn=r'''
struct HK {
    int n1,n2;vector<vector<int>>adj;vector<int>ml,mr,vis;
    void init(int n,int m){n1=n;n2=m;adj.assign(n+1,{});ml.assign(n+1,0);mr.assign(m+1,0);vis.assign(m+1,0);}
    void add(int u,int v){adj[u].push_back(v);}
    bool dfs(int x){for(int v:adj[x]){if(vis[v])continue;vis[v]=1;if(!mr[v]||dfs(mr[v])){ml[x]=v;mr[v]=x;return true;}}return false;}
    int matching(){int ans=0;for(int x=1;x<=n1;x++)if(ml[x])ans++;for(int x=1;x<=n1;x++)if(!ml[x]){fill(vis.begin(),vis.end(),0);if(dfs(x))ans++;}return ans;}
};
'''
ex=[dict(e) for e in matching_examples]
for e in ex:e['complexity']='O(V_left*E)时间、O(V+E)空间。'
add('图论','DFS增广路匹配','HK',kuhn,'保留原逐左点DFS增广写法；接口与HK统一，便于比较两种算法。','O(V_left*E)时间、O(V+E)空间。',[('init(n,m)','独立左右编号'),('add(u,v)','合法匹配边'),('matching()','每轮清vis再增广')],['每次未匹配左点增广前必须重置vis。','大图优先HK；这里保留简单递归作为小规模变体。'],['图论/二分图匹配.cpp'],ex)

add('图论','二分图染色','BipColor',r'''
struct BipColor {
    int n;vector<vector<int>>e;vector<int>col;vector<array<int,2>>cnt;
    void init(int n_){n=n_;e.assign(n+1,{});col.assign(n+1,-1);cnt.clear();}
    void addedge(int u,int v){e[u].push_back(v);e[v].push_back(u);}
    bool dfs(int u,int c,array<int,2>&num){col[u]=c;num[c]++;for(int v:e[u]){if(col[v]==-1){if(!dfs(v,c^1,num))return false;}else if(col[v]==c)return false;}return true;}
    bool run(){fill(col.begin(),col.end(),-1);cnt.clear();for(int u=1;u<=n;u++)if(col[u]==-1){array<int,2>num={0,0};if(!dfs(u,0,num))return false;cnt.push_back(num);}return true;}
};
''','判断无向图是否可二染色，并统计每个连通块的两色数量。','O(n+m)时间与空间。',[('init(n)','颜色-1代表未访问'),('addedge(u,v)','无向边'),('run()','不可染返回false；cnt记录各块两色数')],['遍历全部连通块；自环必然矛盾。','深链递归有RE风险，运行环境需足够栈。'],['图论/二分图染色.cpp'],[
example('ABC327D','Good Tuple Problem','https://atcoder.jp/contests/abc327/tasks/abc327_d','给定成对约束X[Ai]!=X[Bi]，判断是否存在0/1赋值。','每对不等约束就是边的两端必须不同色。','分别读取A和B数组后addedge，run输出Yes/No。','O(n+m)时间与空间。',r'''void solve(){int n,m;cin>>n>>m;vector<int>a(m),b(m);for(int&x:a)cin>>x;for(int&x:b)cin>>x;BipColor g;g.init(n);for(int i=0;i<m;i++)g.addedge(a[i],b[i]);cout<<(g.run()?"Yes":"No")<<'\n';}'''),
example('P1330','封锁阳光大学','https://www.luogu.com.cn/problem/P1330','选择点封锁边，并要求相连点不能同时被选，最少选多少。','每条边恰有一端被选，每个块只能选二分图的一侧；取较小侧。','run判奇环，无解Impossible；累加min(cnt[0],cnt[1])。','O(n+m)时间与空间。',r'''void solve(){int n,m;cin>>n>>m;BipColor g;g.init(n);while(m--){int u,v;cin>>u>>v;g.addedge(u,v);}if(!g.run()){cout<<"Impossible\n";return;}int ans=0;for(auto c:g.cnt)ans+=min(c[0],c[1]);cout<<ans<<'\n';}''')])

add('图论','倍增LCA','LCA',r'''
struct LCA {
    int n,LOG;vector<vector<int>>e,fa;vector<int>dep;
    void init(int n_){n=n_;LOG=1;while((1LL<<LOG)<=n)LOG++;e.assign(n+1,{});fa.assign(LOG,vector<int>(n+1));dep.assign(n+1,0);}
    void addedge(int u,int v){e[u].push_back(v);e[v].push_back(u);}
    void dfs(int u,int f){fa[0][u]=f;dep[u]=dep[f]+1;for(int j=1;j<LOG;j++)fa[j][u]=fa[j-1][fa[j-1][u]];for(int v:e[u])if(v!=f)dfs(v,u);}
    void build(int root=1){dfs(root,0);}
    int lca(int u,int v){if(dep[u]<dep[v])swap(u,v);int d=dep[u]-dep[v];for(int j=0;j<LOG;j++)if(d>>j&1)u=fa[j][u];if(u==v)return u;for(int j=LOG-1;j>=0;j--)if(fa[j][u]!=fa[j][v]){u=fa[j][u];v=fa[j][v];}return fa[0][u];}
    int distance(int u,int v){int p=lca(u,v);return dep[u]+dep[v]-2*dep[p];}
};
''','有根树最近公共祖先与边数距离；1-based，0为虚祖先。','预处理O(n log n)，查询O(log n)，空间O(n log n)。',[('init(n)','按n选择倍增层数'),('build(root)','树上递归预处理'),('lca(u,v)','最近公共祖先'),('distance(u,v)','无权树距离')],['仅在树上使用；图中环会导致递归失控。','LOG包括足够层数；深链最大n=5e5存在栈风险。'],['图论/倍增求lca.cpp'],[
example('P3379','最近公共祖先','https://www.luogu.com.cn/problem/P3379','指定根，回答LCA。','读入树并按指定根预处理倍增表。','init、addedge、build(s)、lca。','O((n+q)log n)时间、O(n log n)空间。',r'''void solve(){int n,q,s;cin>>n>>q>>s;LCA tr;tr.init(n);for(int i=1,u,v;i<n;i++){cin>>u>>v;tr.addedge(u,v);}tr.build(s);while(q--){int u,v;cin>>u>>v;cout<<tr.lca(u,v)<<'\n';}}'''),
example('CF1328E','Tree Queries','https://codeforces.com/problemset/problem/1328/E','若干点各自至多向父移动一次，能否落在同一条根到某点路径上。','把点移到父后，所有点需成为最深点的祖先；用LCA判祖先。','根的父替换为自身；取最深点v，检查lca(u,v)==u。','O(n log n+总查询点数log n)时间、O(n log n)空间。',r'''void solve(){int n,q;cin>>n>>q;LCA tr;tr.init(n);for(int i=1,u,v;i<n;i++){cin>>u>>v;tr.addedge(u,v);}tr.build();while(q--){int k;cin>>k;vector<int>a(k);int v=1;for(int&u:a){cin>>u;if(tr.dep[u]>tr.dep[v])v=u;}bool ok=true;for(int u:a){u=u==1?1:tr.fa[0][u];if(tr.lca(u,v)!=u)ok=false;}cout<<(ok?"YES":"NO")<<'\n';}}''')])

add('图论','Kruskal重构树','KruskalTree',r'''
struct KruskalTree {
    struct edge{int u,v,w;};
    int n,tot,LOG;vector<int>fa,val,dep,bel;vector<vector<int>>tr,up;vector<edge>e;
    void init(int n_){n=n_;tot=n;e.clear();fa.resize(2*n+1);iota(fa.begin(),fa.end(),0);val.assign(2*n+1,0);tr.assign(2*n+1,{});dep.assign(2*n+1,0);bel.assign(2*n+1,0);LOG=1;while((1LL<<LOG)<=2*n)LOG++;up.assign(LOG,vector<int>(2*n+1));}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void addedge(int u,int v,int w){e.push_back({u,v,w});}
    void dfs(int u,int f,int component){up[0][u]=f;dep[u]=dep[f]+1;bel[u]=component;for(int j=1;j<LOG;j++)up[j][u]=up[j-1][up[j-1][u]];for(int v:tr[u])dfs(v,u,component);}
    void build(bool maximum=false){sort(e.begin(),e.end(),[&](edge a,edge b){return maximum?a.w>b.w:a.w<b.w;});for(auto[u,v,w]:e){int x=find(u),y=find(v);if(x==y)continue;++tot;val[tot]=w;tr[tot]={x,y};fa[x]=fa[y]=tot;}for(int u=1;u<=tot;u++)if(fa[u]==u)dfs(u,0,u);}
    int lca(int u,int v){if(bel[u]!=bel[v])return 0;if(dep[u]<dep[v])swap(u,v);int d=dep[u]-dep[v];for(int j=0;j<LOG;j++)if(d>>j&1)u=up[j][u];if(u==v)return u;for(int j=LOG-1;j>=0;j--)if(up[j][u]!=up[j][v]){u=up[j][u];v=up[j][v];}return up[0][u];}
    int qur(int u,int v){int p=lca(u,v);return p?val[p]:-1;}
};
''','按权值排序建立连通块合并历史；支持不连通森林与LCA瓶颈查询。','排序O(m log m)，建树与倍增O(n log n+m alpha(n))的通常界；当前重构树代表递归find可有长链，空间O(n log n+m)。',[('build(false)','升序：最小化路径最大边'),('build(true)','降序：最大化路径最小边'),('lca(u,v)','不连通返回0'),('qur(u,v)','LCA权值，不连通-1，同点约定0')],['森林必须逐根预处理，不能只dfs(tot)。','同点的空路径瓶颈由题目约定；本接口返回0。','归并代表形成长链，递归find/dfs有栈风险；每次新建图先init。'],['图论/Kruskal重构树.cpp','图论/Kruskal重构树板子 (1).md'],[
example('P2245','星际导航','https://www.luogu.com.cn/problem/P2245','求两点间路径最大边尽可能小的值。','升序合并首次连通的权值就是所需最大边阈值。','build(false)，qur；不连通按题面输出impossible。','O(m log m+n log n+q log n)时间、O(m+n log n)空间。',r'''void solve(){int n,m;cin>>n>>m;KruskalTree tr;tr.init(n);while(m--){int u,v,w;cin>>u>>v>>w;tr.addedge(u,v,w);}tr.build(false);int q;cin>>q;while(q--){int u,v;cin>>u>>v;int p=tr.lca(u,v);if(!p)cout<<"impossible\n";else cout<<tr.val[p]<<'\n';}}'''),
example('P1967','货车运输','https://www.luogu.com.cn/problem/P1967','求路径上最小载重尽可能大的容量。','降序合并首次连通阈值是最大最小边。','build(true)，qur，不连通-1。','O(m log m+n log n+q log n)时间、O(m+n log n)空间。',r'''void solve(){int n,m;cin>>n>>m;KruskalTree tr;tr.init(n);while(m--){int u,v,w;cin>>u>>v>>w;tr.addedge(u,v,w);}tr.build(true);int q;cin>>q;while(q--){int u,v;cin>>u>>v;cout<<tr.qur(u,v)<<'\n';}}''')])

for name,typ,path in [('Tarjan强连通分量','SCC','图/图论竞赛复习_严格课件注释版.md'),('Kosaraju强连通分量','Kosaraju','图/图论竞赛复习_严格课件注释版.md')]:
    body=source_struct(path,typ)
    add('图论',name,typ,body,'有向图强连通分量划分与缩点；支持重边、自环及不连通图。','O(n+m)时间与空间，递归栈O(n)。',[('init(n)','清空旧图'),('addedge(u,v)','有向边'),('run()','求SCC，每次建图仅运行一次'),('bel[u]/cnt/scc','归属编号、数量与分量成员')],['Tarjan只使用仍在栈中的点更新low；Kosaraju第二遍走反图。','两算法分量编号顺序不同，不把编号当统一拓扑序；应用显式拓扑排序。','深链递归有RE风险。'],[path,'图论/SCC.md'],[
    example('P2341','受欢迎的牛','https://www.luogu.com.cn/problem/P2341','找被所有点可达的点数。','缩点DAG唯一出度0分量中的所有点满足；多于一个则无解。','run后枚举原边计算分量出度，检查唯一汇分量。','O(n+m)时间与空间。',r'''void solve(){int n,m;cin>>n>>m;TYPE scc;scc.init(n);vector<pair<int,int>>e(m);for(auto&[u,v]:e){cin>>u>>v;scc.addedge(u,v);}scc.run();vector<int>out(scc.cnt+1),sz(scc.cnt+1);for(int u=1;u<=n;u++)sz[scc.bel[u]]++;for(auto[u,v]:e)if(scc.bel[u]!=scc.bel[v])out[scc.bel[u]]++;int ans=0,count=0;for(int c=1;c<=scc.cnt;c++)if(!out[c]){count++;ans=sz[c];}cout<<(count==1?ans:0)<<'\n';}'''.replace('TYPE',typ)),
    example('P3387','缩点','https://www.luogu.com.cn/problem/P3387','有向图走一条路线，点权最多可取得多少；每点只计一次。','正权SCC内可遍历全部点，缩为DAG做最长路。','run、汇总点权、建立分量边，用Kahn顺序转移dp。','O(n+m)时间与空间。',r'''void solve(){int n,m;cin>>n>>m;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];TYPE scc;scc.init(n);vector<pair<int,int>>e(m);for(auto&[u,v]:e){cin>>u>>v;scc.addedge(u,v);}scc.run();int k=scc.cnt;vector<int>w(k+1),deg(k+1);vector<vector<int>>g(k+1);for(int i=1;i<=n;i++)w[scc.bel[i]]+=a[i];for(auto[u,v]:e){u=scc.bel[u];v=scc.bel[v];if(u!=v){g[u].push_back(v);deg[v]++;}}queue<int>q;vector<int>dp=w;for(int c=1;c<=k;c++)if(!deg[c])q.push(c);int ans=0;while(!q.empty()){int u=q.front();q.pop();ans=max(ans,dp[u]);for(int v:g[u]){dp[v]=max(dp[v],dp[u]+w[v]);if(!--deg[v])q.push(v);}}cout<<ans<<'\n';}'''.replace('TYPE',typ))])
