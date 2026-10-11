from common import *
src=['图/图论竞赛复习_严格课件注释版.md','图/图论竞赛复习_按课件整理.md']
flow='template<typename T>\n'+source_struct('图论/整理版/Dinic最大流/模板.cpp','FlowGraph')
bounded=flow+r'''
struct BoundedFlow {
    static constexpr int INF=4000000000000000000LL;
    struct edge{int u,v,l,r,id;};
    int n,S,T;vector<int>balance;vector<edge>edges;FlowGraph<int>g;vector<int>aux;
    BoundedFlow(int n=0){init(n);}
    void init(int n_){n=n_;S=n+1;T=n+2;balance.assign(n+1,0);edges.clear();aux.clear();g.init(S,T,T);}
    int add_edge(int u,int v,int l,int r){assert(0<=l&&l<=r);int id=g.etot;g.addedge(u,v,r-l);balance[u]-=l;balance[v]+=l;edges.push_back({u,v,l,r,id});return edges.size()-1;}
    bool feasible(){int need=0;for(int u=1;u<=n;u++){if(balance[u]>0){aux.push_back(g.etot);g.addedge(S,u,balance[u]);need+=balance[u];}if(balance[u]<0){aux.push_back(g.etot);g.addedge(u,T,-balance[u]);}}
        return g.dinic()==need;}
    int value(int k){auto z=edges[k];return z.r-g.e[z.id].f;}
    optional<int> maxflow(int s,int t){int back=g.etot;g.addedge(t,s,INF);if(!feasible())return nullopt;int base=g.e[back^1].f;
        g.e[back].f=g.e[back^1].f=0;for(int id:aux)g.e[id].f=g.e[id^1].f=0;g.s=s;g.t=t;return base+g.dinic();}
};
'''
add('图论','有上下界可行流与最大流','BoundedFlow',bounded,'先强制下界并记录节点净流入差，超级源汇补平衡；有源汇加t->s并在可行残量上继续增广。','一般Dinic O(V²E)时间、O(V+E)空间。',
 [('add_edge(u,v,l,r)','记录0<=l<=流量<=r，返回原边序号'),('feasible()','无源汇环流判可行，只调用一次'),('maxflow(s,t)','有源汇非负最大流，nullopt表示不可行'),('value(k)','可行之后读取原第k条边实际流量')],
 ['balance正值接S->u，负值接u->T；容易接反。','第二次增广前必须同时清空所有辅助边的正反残量。','INF需超过需求与可行总流，不能使用LLONG_MAX参与加法。'],src,[
 example('CF510E','Fox And Dinner','https://codeforces.com/contest/510/problem/E','将年龄数排成若干长度至少3的圆桌，相邻和为素数。','年龄>=2使素数边只可能连接奇偶；每点恰好两条选择边，转为上下界为2的二分图度约束。','源到奇点[2,2]，素数边[0,1]，偶点到汇[2,2]，汇到源[0,2n]，feasible后value恢复环。','建边O(n² sqrt A)，最大流一般O(V²E)，O(n²)空间。',r'''
 void solve(){int n;cin>>n;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];int s=n+1,t=n+2;BoundedFlow g(t);vector<array<int,3>>choice;
 auto prime=[](int x){if(x<2)return false;for(int p=2;p<=x/p;p++)if(x%p==0)return false;return true;};
 for(int i=1;i<=n;i++)if(a[i]&1)g.add_edge(s,i,2,2);else g.add_edge(i,t,2,2);
 for(int i=1;i<=n;i++)if(a[i]&1)for(int j=1;j<=n;j++)if(!(a[j]&1)&&prime(a[i]+a[j]))choice.push_back({i,j,g.add_edge(i,j,0,1)});
 g.add_edge(t,s,0,2*n);if(!g.feasible()){cout<<"Impossible\n";return;}vector<vector<int>>adj(n+1),cycles;for(auto[u,v,k]:choice)if(g.value(k))adj[u].push_back(v),adj[v].push_back(u);
 vector<int>vis(n+1);for(int i=1;i<=n;i++)if(!vis[i]){vector<int>cyc;int u=i,p=0;do{cyc.push_back(u);vis[u]=1;int v=adj[u][0]==p?adj[u][1]:adj[u][0];p=u;u=v;}while(u!=i);cycles.push_back(cyc);}
 cout<<cycles.size()<<'\n';for(auto c:cycles){cout<<c.size();for(int u:c)cout<<' '<<u;cout<<'\n';}}
 '''),
 example('P5192','Shoot the Bullet','https://www.luogu.com.cn/problem/P5192','每天拍摄总量上限、每次对象数量区间、每位少女总需求下限，最大拍摄量。','每项区间对应一天到少女的上下界边，少女到汇的下界代表需求，属于有源汇上下界最大流。','S->天[0,D]，天->少女[L,R]，少女->T[G,INF]，maxflow。重复少女边分别保留。','一般O(V²E)时间、O(V+E)空间。',r'''
 void solve(){int n,m;while(cin>>n>>m){int s=n+m+1,t=s+1;BoundedFlow g(t);for(int j=0;j<m;j++){int G;cin>>G;g.add_edge(n+j+1,t,G,1000000000);}
 for(int i=1;i<=n;i++){int C,D;cin>>C>>D;g.add_edge(s,i,0,D);while(C--){int j,L,R;cin>>j>>L>>R;g.add_edge(i,n+j+1,L,R);}}
 auto ans=g.maxflow(s,t);cout<<(ans?*ans:-1)<<"\n\n";}}
 ''')])

mcf=r'''
struct MinCostFlow {
    static constexpr int INF=4000000000000000000LL;
    struct edge{int v,f,c;};int n;vector<edge>e;vector<vector<int>>g;vector<int>h,dis,pre;
    MinCostFlow(int n=0){init(n);}
    void init(int n_){n=n_;e.clear();g.assign(n+1,{});h.assign(n+1,0);dis=pre=h;}
    void add_edge(int u,int v,int f,int c){int id=e.size();g[u].push_back(id);g[v].push_back(id^1);e.push_back({v,f,c});e.push_back({u,0,-c});}
    pair<int,int> run(int s,int t,int limit=INF){assert(s!=t);
        // 零势若已可行，无需Bellman-Ford；负费用时先建立全局可行势。
        fill(h.begin(),h.end(),0);bool negative=false;for(auto z:e)if(z.f>0&&z.c<0)negative=true;
        if(negative)for(int k=1;k<=n;k++){bool changed=false;for(int u=1;u<=n;u++)for(int id:g[u]){auto z=e[id];if(z.f>0&&h[z.v]>h[u]+z.c)h[z.v]=h[u]+z.c,changed=true;}
            if(!changed)break;assert(k<n);}
        int flow=0,cost=0;
        while(flow<limit){fill(dis.begin(),dis.end(),INF);dis[s]=0;priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;q.push({0,s});
            while(!q.empty()){auto[d,u]=q.top();q.pop();if(d!=dis[u])continue;for(int id:g[u]){auto z=e[id];if(z.f>0&&dis[z.v]>d+z.c+h[u]-h[z.v]){dis[z.v]=d+z.c+h[u]-h[z.v];pre[z.v]=id;q.push({dis[z.v],z.v});}}}
            if(dis[t]==INF)break;for(int u=1;u<=n;u++)if(dis[u]<INF)h[u]+=dis[u];
            int f=limit-flow;for(int v=t;v!=s;v=e[pre[v]^1].v)f=min(f,e[pre[v]].f);
            for(int v=t;v!=s;v=e[pre[v]^1].v){int id=pre[v];e[id].f-=f;e[id^1].f+=f;cost+=f*e[id].c;}flow+=f;}
        return {flow,cost};
    }
};
'''
add('图论','最小费用最大流','MinCostFlow',mcf,'逐次最短增广；费用势使残量边非负，用Dijkstra取最便宜增广路，支持无负环的负费用初始网络。','初始非负费用免预处理；有负费用时O(VE)建势，之后O(A*E log V)，A为增广次数；O(V+E)空间。',
 [('add_edge(u,v,f,c)','容量f非负，费用c；自动配反向边'),('run(s,t,limit)','返回新增流量及新增最小费用，默认最大流')],
 ['初始正容量子图不允许负费用环；需要消负环的环流问题须另写算法。','最大费用可取相反费用重建网络，不能在同一已流过的网络直接换号。','容量*费用及累计费用必须在long long内。'],src,[
 example('P3381','最小费用最大流','https://www.luogu.com.cn/problem/P3381','有向容量费用网络求最小费用最大流。','费用最短的残量增广路保证每个流量阶段费用最小。','add_edge(u,v,w,c)，run(s,t)。','O(AE log V)时间，O(V+E)空间；此题初始c>=0。',r'''
 void solve(){int n,m,s,t;cin>>n>>m>>s>>t;MinCostFlow g(n);while(m--){int u,v,w,c;cin>>u>>v>>w>>c;g.add_edge(u,v,w,c);}auto[f,c]=g.run(s,t);cout<<f<<' '<<c<<'\n';}
 '''),
 example('P4015','运输问题','https://www.luogu.com.cn/problem/P4015','运输供需平衡的货物，求最小和最大费用。','仓库到商店边的流量代表货运量，负费用后最小值对应最大费用。','分别重建正费用、负费用网络；输出run的费用及负号恢复。','O(VE+AE log V)时间、O(V+E)空间。',r'''
 void solve(){int m,n;cin>>m>>n;vector<int>a(m+1),b(n+1);int total=0;for(int i=1;i<=m;i++)cin>>a[i],total+=a[i];for(int j=1;j<=n;j++)cin>>b[j];vector<vector<int>>c(m+1,vector<int>(n+1));for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)cin>>c[i][j];
 for(int sign:{1,-1}){int s=m+n+1,t=s+1;MinCostFlow g(t);for(int i=1;i<=m;i++){g.add_edge(s,i,a[i],0);for(int j=1;j<=n;j++)g.add_edge(i,m+j,total,c[i][j]*sign);}for(int j=1;j<=n;j++)g.add_edge(m+j,t,b[j],0);cout<<g.run(s,t).second*sign<<'\n';}}
 ''')])

# 最小割高级用法作为已有知识点的第3例，依赖SCC完整放入模板。
topics=json.loads(CATALOG.read_text(encoding='utf-8'))
t=next(x for x in topics if x['name']=='最小割建模')
scc=source_struct('图论/整理版/Tarjan强连通分量/模板.cpp','SCC')
e=example('P4126','最小割边判定','https://www.luogu.com.cn/problem/P4126','判断每条边是否可出现在某个或所有最小割中。','最大流后残量SCC：饱和且两端不同SCC可属于某割；起点在源SCC且终点在汇SCC属于所有割。','dinic后将正残量边加入SCC；按保存原边号检查f=0和col条件。','最大流一般O(V²E)，SCC O(V+E)，O(V+E)空间。',r'''
void solve(){int n,m,s,t;cin>>n>>m>>s>>t;FlowGraph<int>g;g.init(s,t,n);vector<array<int,3>>a(m);for(auto &z:a){int c;cin>>z[0]>>z[1]>>c;z[2]=g.etot;g.addedge(z[0],z[1],c);}g.dinic();SCC sc;sc.init(n);
for(int u=1;u<=n;u++)for(int i=g.head[u];i!=-1;i=g.e[i].nxt)if(g.e[i].f>0)sc.addedge(u,g.e[i].v);sc.run();
for(auto[u,v,id]:a){bool possible=g.e[id].f==0&&sc.bel[u]!=sc.bel[v];bool necessary=possible&&sc.bel[u]==sc.bel[s]&&sc.bel[v]==sc.bel[t];cout<<possible<<' '<<necessary<<'\n';}}
''')
add(t['category'],t['name'],t['struct'],flow+'\n'+scc,t['intro'],t['complexity'],t['api'],t['pitfalls']+['最小割边分类须在最大流完成后，以正残量图求SCC。'],t['sources'],t['examples'][:2]+[e])
