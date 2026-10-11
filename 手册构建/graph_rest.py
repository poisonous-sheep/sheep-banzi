from common import *

direct=r'''
struct Euler {
    int n,m;vector<vector<int>>adj;vector<int>in,out,path;
    void init(int n_){n=n_;m=0;adj.assign(n+1,{});in.assign(n+1,0);out=in;path.clear();}
    void addedge(int u,int v){adj[u].push_back(v);out[u]++;in[v]++;m++;}
    void dfs(int u){while(!adj[u].empty()){int v=adj[u].back();adj[u].pop_back();dfs(v);}path.push_back(u);}
    bool run(bool lex=true){int st=0,en=0;for(int u=1;u<=n;u++){int d=out[u]-in[u];if(d==1){if(st)return false;st=u;}else if(d==-1){if(en)return false;en=u;}else if(d)return false;}if(bool(st)!=bool(en))return false;if(!st)for(int u=1;u<=n;u++)if(out[u]){st=u;break;}if(!st)st=1;if(lex)for(int u=1;u<=n;u++)sort(adj[u].begin(),adj[u].end(),greater<int>());path.clear();dfs(st);reverse(path.begin(),path.end());return (int)path.size()==m+1;}
};
'''
add('图论','有向欧拉路径','Euler',direct,'Hierholzer递归删边与逆序；验证度条件和全边覆盖。','不排序O(n+m)，字典序排序O(m log m)，空间O(n+m)。',[('addedge(u,v)','允许重复边与自环'),('run(lex)','破坏邻接表，得到path；失败不可使用'),('path','顺序路径点数m+1')],['只判断出入度不足够，还要检查path.size()==m+1。','每边只pop一次；递归深度最坏m，有RE风险。'],['图论/欧拉路径.md'],[
example('P7771','欧拉路径','https://www.luogu.com.cn/problem/P7771','输出字典序最小有向欧拉路，没有则No。','度数唯一决定非回路起点；降序邻接pop_back优先小点。','run(true)后输出path。','O(m log m+n)时间、O(n+m)空间。',r'''void solve(){int n,m;cin>>n>>m;Euler g;g.init(n);while(m--){int u,v;cin>>u>>v;g.addedge(u,v);}if(!g.run()){cout<<"No\n";return;}for(int u:g.path)cout<<u<<' ';cout<<'\n';}'''),
example('CF508D','Tanya and Password','https://codeforces.com/contest/508/problem/D','用三字符子串多重集还原原字符串。','每个两字符串是节点，三字符串是前两位到后两位的有向边；所有子串恰用一次。','字母数字映射62进制节点；run(false)；输出首节点两位，再输出后续节点末位。','O(n+62^2)时间与空间。',r'''void solve(){int n;cin>>n;string ch="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";auto cv=[&](char c){return ch.find(c);};Euler g;g.init(62*62);while(n--){string s;cin>>s;int u=cv(s[0])*62+cv(s[1])+1,v=cv(s[1])*62+cv(s[2])+1;g.addedge(u,v);}if(!g.run(false)){cout<<"NO\n";return;}cout<<"YES\n";int first=g.path[0]-1;cout<<ch[first/62]<<ch[first%62];for(int i=1;i<(int)g.path.size();i++)cout<<ch[(g.path[i]-1)%62];cout<<'\n';}''')])

undirected=r'''
struct Euler {
    struct edge{int v,id;};int n,m;vector<vector<edge>>adj;vector<int>deg,cur,vis,path;
    void init(int n_){n=n_;m=0;adj.assign(n+1,{});deg.assign(n+1,0);cur=deg;vis.clear();path.clear();}
    void addedge(int u,int v){adj[u].push_back({v,m});adj[v].push_back({u,m});deg[u]++;deg[v]++;vis.push_back(0);m++;}
    void dfs(int u){for(int&i=cur[u];i<(int)adj[u].size();){auto[v,id]=adj[u][i++];if(vis[id])continue;vis[id]=1;dfs(v);}path.push_back(u);}
    bool run(){int st=0,odd=0;for(int u=1;u<=n;u++)if(deg[u]%2){odd++;if(!st)st=u;}if(odd!=0&&odd!=2)return false;if(!st)for(int u=1;u<=n;u++)if(deg[u]){st=u;break;}if(!st)st=1;for(int u=1;u<=n;u++)sort(adj[u].begin(),adj[u].end(),[](edge a,edge b){return a.v<b.v;});fill(cur.begin(),cur.end(),0);fill(vis.begin(),vis.end(),0);path.clear();dfs(st);reverse(path.begin(),path.end());return (int)path.size()==m+1;}
};
'''
add('图论','无向欧拉路径','Euler',undirected,'唯一边号标记、当前弧DFS，返回字典序最小无向欧拉路径。','O(m log m+n)时间、O(n+m)空间。',[('addedge(u,v)','同一无向边的两向共享id'),('run()','检查奇度数量及全边覆盖'),('path','从最小可行起点出发')],['不能仅标记某一方向。','有边点须在同一个连通块；用路径长度验证。','深度可达m，保留递归并明确栈限制。'],['图论/欧拉路径.md'],[
example('P2731','Riding the Fences','https://www.luogu.com.cn/problem/P2731','按字典序输出经过每条栅栏一次的路线。','栅栏是无向多重边，选择最小奇度点或最小有边点出发。','init(500)、addedge、run，按点逐行输出。','O(m log m+500)时间、O(m+500)空间。',r'''void solve(){int m;cin>>m;Euler g;g.init(500);while(m--){int u,v;cin>>u>>v;g.addedge(u,v);}g.run();for(int u:g.path)cout<<u<<'\n';}'''),
example('P1341','无序字母对','https://www.luogu.com.cn/problem/P1341','把无序字母对拼成字典序最小字符串，每对用一次。','字母是节点，字母对是无向边；字符ASCII顺序就是要求的字典序。','字符号加1避免节点0，run后逐点输出字符。','O(m log m+128)时间、O(m+128)空间。',r'''void solve(){int m;cin>>m;Euler g;g.init(128);while(m--){string s;cin>>s;g.addedge((unsigned char)s[0]+1,(unsigned char)s[1]+1);}if(!g.run()){cout<<"No Solution\n";return;}for(int u:g.path)cout<<char(u-1);cout<<'\n';}''')])

scc=source_struct('图/图论竞赛复习_严格课件注释版.md','SCC')
diff=r'''
struct Difference {
    struct edge{int u,v,w;};int n;vector<edge>e;vector<int>x;
    void init(int n_){n=n_;e.clear();x.assign(n+1,0);}
    // 加入x[v]-x[u]<=w，未知数1..n。
    void add_constraint(int u,int v,int w){e.push_back({u,v,w});}
    bool solve(){fill(x.begin(),x.end(),0);for(int i=1;i<=n;i++){bool changed=false;for(auto[u,v,w]:e)if(x[v]>x[u]+w){x[v]=x[u]+w;changed=true;if(i==n)return false;}if(!changed)return true;}return true;}
    // 特例：所有w<=0；求a[i]>=1且a[v]>=a[u]-w的最小解，x=-a。
    bool minimum_positive(){SCC scc;scc.init(n);for(auto[u,v,w]:e){assert(w<=0);scc.addedge(u,v);}scc.run();int k=scc.cnt;vector<vector<pair<int,int>>>g(k+1);vector<int>d(k+1),ans(k+1,1);for(auto[u,v,w]:e){u=scc.bel[u];v=scc.bel[v];if(u==v){if(w<0)return false;}else{g[u].push_back({v,-w});d[v]++;}}queue<int>q;for(int u=1;u<=k;u++)if(!d[u])q.push(u);while(!q.empty()){int u=q.front();q.pop();for(auto[v,w]:g[u]){ans[v]=max(ans[v],ans[u]+w);if(!--d[v])q.push(v);}}for(int u=1;u<=n;u++)x[u]=-ans[scc.bel[u]];return true;}
};
'''
add('图论','差分约束','Difference',scc+'\n'+diff,'一般上界差分约束用Bellman-Ford判负环；非正权上界特例提供SCC+DAG最小正值变体。','solve为O(nm)时间；minimum_positive为O(n+m)时间；空间O(n+m)。',[('add_constraint(u,v,w)','x[v]-x[u]<=w'),('solve()','任意可行x或false'),('minimum_positive()','仅w<=0；返回x=-a且a[i]>=1的最小解')],['先写不等式再确定边方向；严格整数差用1而非浮点epsilon。','一般有正/负权时不能用SCC特例；大规模一般图Bellman-Ford会TLE。'],['图论/差分约束.cpp','图/图论竞赛复习_严格课件注释版.md'],[
example('P5960','差分约束','https://www.luogu.com.cn/problem/P5960','求形如x[c]-x[c2]<=y的不等式组可行解。','边c2->c权y，用全零初值等价于超级源连到全部点。','add_constraint(c2,c,y)，solve后输出x。','O(nm)时间、O(n+m)空间。',r'''void solve(){int n,m;cin>>n>>m;Difference g;g.init(n);while(m--){int c,d,y;cin>>c>>d>>y;g.add_constraint(d,c,y);}if(!g.solve()){cout<<"NO\n";return;}for(int i=1;i<=n;i++)cout<<g.x[i]<<(i==n?'\n':' ');}'''),
example('P3275','糖果','https://www.luogu.com.cn/problem/P3275','每人至少1颗糖，满足五类大小关系，最少糖果总数。','取x=-糖果数后全部边权0或-1；同SCC负边意味着矛盾，缩点最长路求最小糖果。','映射五类约束后minimum_positive；输出-sum(x)。','O(n+m)时间与空间。',r'''void solve(){int n,m;cin>>n>>m;Difference g;g.init(n);while(m--){int op,a,b;cin>>op>>a>>b;if(op==1){g.add_constraint(a,b,0);g.add_constraint(b,a,0);}else if(op==2)g.add_constraint(a,b,-1);else if(op==3)g.add_constraint(b,a,0);else if(op==4)g.add_constraint(b,a,-1);else g.add_constraint(a,b,0);}if(!g.minimum_positive()){cout<<-1<<'\n';return;}int ans=0;for(int i=1;i<=n;i++)ans-=g.x[i];cout<<ans<<'\n';}''')])
