from common import *
src=['dp/树形动态规划进阶_比赛板子.md']
mx=r'''
struct TreeMaxSum {
    int n;vector<vector<int>>son;vector<int>a,f,ans;
    TreeMaxSum(int n=0){init(n);}
    void init(int n_){n=n_;son.assign(n+1,{});a.assign(n+1,0);f=ans=a;}
    void add_edge(int u,int v){son[u].push_back(v);son[v].push_back(u);}
    void dfs(int u,int p){f[u]=a[u];for(int v:son[u])if(v!=p){dfs(v,u);f[u]+=max(0LL,f[v]);}}
    void dfs2(int u,int p,int up){ans[u]=f[u]+max(0LL,up);for(int v:son[u])if(v!=p)dfs2(v,u,ans[u]-max(0LL,f[v]));}
    void run(int root=1){dfs(root,0);dfs2(root,0,0);}
};
'''
add('dp','树上最大连通块权和','TreeMaxSum',mx,'含根的最优连通块权和为自身加所有正的子树贡献；二次DFS给每点换根答案。','O(n)时间与空间。',
 [('init/add_edge/a','初始化树、无向边、1基点权'),('run(root)','f是固定根视图的子树答案；ans是整棵树中含该点的最优权和')],
 ['不能把全负树答案初始化成0，题目要求非空。','换根必须扣去当前孩子的正贡献，再传给该孩子。','链树递归O(n)深度，注意评测栈限制。'],src,[
 example('P1122','最大子树和','https://www.luogu.com.cn/problem/P1122','修剪树后保留非空连通子树使权和最大。','任何连通块在固定根下有唯一最高点；取所有f的最大值。','写入a、add_edge、run，然后max f[1..n]。','O(n)时间/空间。',r'''
 void solve(){int n;cin>>n;TreeMaxSum t(n);for(int i=1;i<=n;i++)cin>>t.a[i];for(int i=1;i<n;i++){int u,v;cin>>u>>v;t.add_edge(u,v);}t.run();cout<<*max_element(t.f.begin()+1,t.f.end())<<'\n';}
 '''),
 example('CF1324F','Maximum White Subtree','https://codeforces.com/contest/1324/problem/F','对每点求包含它的连通块中白数减黑数的最大值。','白点权+1，黑点权-1；换根把子树答案扩展为整树答案。','把输入颜色转为2*a-1，run后输出ans。','O(n)时间/空间。',r'''
 void solve(){int n;cin>>n;TreeMaxSum t(n);for(int i=1;i<=n;i++){int x;cin>>x;t.a[i]=2*x-1;}for(int i=1;i<n;i++){int u,v;cin>>u>>v;t.add_edge(u,v);}t.run();for(int i=1;i<=n;i++)cout<<t.ans[i]<<" \n"[i==n];}
 ''',tests=[dict(input='4\n0 0 1 0\n1 2\n1 3\n1 4\n',output='0 -1 1 -1\n')])])

kn=r'''
struct TreeKnapsack {
    static constexpr int INF=4000000000000000000LL;
    int n,M;vector<vector<pair<int,int>>>son;vector<int>a,w;vector<vector<int>>dp;
    TreeKnapsack(int n=0,int M=0){init(n,M);}
    void init(int n_,int m){n=n_;M=m;son.assign(n+1,{});a.assign(n+1,0);w.assign(n+1,1);dp.assign(n+1,{});}
    void add_edge(int u,int v,int cost=0){son[u].push_back({v,cost});}
    void dfs(int u){dp[u].assign(min(M,w[u])+1,-INF);if(w[u]<=M)dp[u][w[u]]=a[u];
        for(auto[v,cost]:son[u]){dfs(v);int A=dp[u].size()-1,B=dp[v].size()-1;vector<int>tmp(min(M,A+B)+1,-INF);
            for(int i=0;i<=A;i++)if(dp[u][i]>-INF){tmp[i]=max(tmp[i],dp[u][i]);for(int j=1;j<=B&&i+j<=M;j++)if(dp[v][j]>-INF)tmp[i+j]=max(tmp[i+j],dp[u][i]+dp[v][j]-cost);}
            dp[u].swap(tmp);}
        dp[u][0]=max(dp[u][0],0LL);
    }
    void run(int root){dfs(root);}
    int qur(int u,int k){return k<(int)dp[u].size()?dp[u][k]:-INF;}
};
'''
course=r'''
void solve(){int n,m;cin>>n>>m;TreeKnapsack t(n,m);t.w[0]=0;for(int i=1;i<=n;i++){int p;cin>>p>>t.a[i];t.add_edge(p,i);}t.run(0);cout<<t.qur(0,m)<<'\n';}
'''
tv=r'''
void solve(){int n,m;cin>>n>>m;TreeKnapsack t(n,m);for(int u=1;u<=n-m;u++){t.w[u]=0;int k;cin>>k;while(k--){int v,c;cin>>v>>c;t.add_edge(u,v,c);}}
for(int u=n-m+1;u<=n;u++)cin>>t.a[u];t.run(1);for(int k=m;k>=0;k--)if(t.qur(1,k)>=0){cout<<k<<'\n';break;}}
'''
add('dp','子树合并背包','TreeKnapsack',kn,'孩子背包卷积合并，固定点数连通选点；用户计数变体可把内部节点权重置0并扣启用边费用。','单位点数或叶子计数模型，限制循环到实际子树规模，总O(nM)，完整M=n时O(n²)；空间O(nM)。',
 [('init(n,M)/a/w','默认每点计数1；点价值可负；用户模型仅内部节点w=0且a=0'),('add_edge(u,v,cost)','有向父到子，选孩子非空时扣费用'),('run(root)/qur(u,k)','恰好选k个计数单位、连通且含u的最优值；k=0表示可不选')],
 ['不可达初始化-INF，不能用0假装可达。','有先修关系必须使父节点被选才能合并孩子；最后提供空集0状态供父亲跳过。','任意非单位w不再有O(nM)规模证明，应改用DFS序依赖背包。'],src,[
 example('P2014','选课','https://www.luogu.com.cn/problem/P2014','恰好选m门课并满足先修依赖，使学分最大。','无先修课程挂在虚根0，虚根w=0不计课程数；每个真实课程w=1。','add_edge(先修,i)，run(0)，qur(0,m)。','O(nm)时间/空间。',course),
 example('P1273','有线电视网','https://www.luogu.com.cn/problem/P1273','选择尽量多用户，在用户收益扣转播边费用后不亏本。','只有叶子计用户数；某孩子子树接入了至少一个用户时才支付该边费用。','内部节点w=0，叶子w=1且a=收益，add_edge含费用；从大到小找dp根[k]>=0。','O(nm)时间/空间。',tv)])

scc=source_struct('图论/整理版/Tarjan强连通分量/模板.cpp','SCC')
dep=scc+r'''
struct DependencyKnapsack {
    static constexpr int INF=4000000000000000000LL;
    int n,M,tot;vector<vector<int>>son;vector<int>id,r,w,a;vector<vector<int>>dp;
    DependencyKnapsack(int n=0,int M=0){init(n,M);}
    void init(int n_,int m){n=n_;M=m;tot=0;son.assign(n+1,{});id.assign(n+2,0);r=w=a=id;dp.clear();}
    void add_edge(int u,int v){son[u].push_back(v);}
    void dfs(int u){id[++tot]=u;for(int v:son[u])dfs(v);r[u]=tot+1;}
    int run(int root,bool exact=false){tot=0;dfs(root);dp.assign(tot+2,vector<int>(M+1,exact?-INF:0));dp[tot+1][0]=0;
        for(int i=tot;i>=1;i--){int u=id[i];for(int j=0;j<=M;j++){
            dp[i][j]=dp[r[u]][j];if(j>=w[u]&&dp[i+1][j-w[u]]>-INF)dp[i][j]=max(dp[i][j],dp[i+1][j-w[u]]+a[u]);}}
        return dp[1][M];}
};
'''
software=r'''
void solve(){int n,M;cin>>n>>M;vector<int>w(n+1),a(n+1),p(n+1);for(int i=1;i<=n;i++)cin>>w[i];for(int i=1;i<=n;i++)cin>>a[i];SCC s;s.init(n);
for(int i=1;i<=n;i++){cin>>p[i];if(p[i])s.addedge(p[i],i);}s.run();DependencyKnapsack t(s.cnt,M);vector<int>in(s.cnt+1);
for(int i=1;i<=n;i++){t.w[s.bel[i]]+=w[i];t.a[s.bel[i]]+=a[i];if(p[i]&&s.bel[p[i]]!=s.bel[i])t.add_edge(s.bel[p[i]],s.bel[i]),in[s.bel[i]]=1;}
for(int i=1;i<=s.cnt;i++)if(!in[i])t.add_edge(0,i);cout<<t.run(0)<<'\n';}
'''
add('dp','DFS序依赖背包','DependencyKnapsack',dep,'选节点则继续DFS下一点，不选则跳过其整个子树；依赖环先缩点为共同选择的软件包。','O(nM)时间/空间；SCC另加O(n+m)。',
 [('add_edge/a/w','依赖森林：父为前提，子为依赖项；允许w=0'),('run(root,exact)','默认容量不超过M；exact=true为恰好M'),('id/r','id是DFS序节点，r[u]是子树末尾后一位置')],
 ['图必须是依赖森林，一般多前提DAG不能直接套。','虚根0的w=a=0，SCC缩点后每包最多一个外部先修。','原课堂固定规模数组省略了tot+1行；整理版显式分配结束状态。'],src,[
 example('P2014','选课 DFS序版','https://www.luogu.com.cn/problem/P2014','按先修条件恰好选m门课。','先修树的合法点集在DFS序中只能“选当前”或“跳整子树”。','真实课w=1、虚根w=0，run(0,true)。','O(nm)时间/空间。',r'''
 void solve(){int n,m;cin>>n>>m;DependencyKnapsack t(n,m);for(int i=1;i<=n;i++){int p;cin>>p>>t.a[i];t.w[i]=1;t.add_edge(p,i);}cout<<t.run(0,true)<<'\n';}
 '''),
 example('P2515','软件安装','https://www.luogu.com.cn/problem/P2515','有最多一个依赖的软件选择，可能存在依赖环，限定容量求最大价值。','环中软件必须全选或全不选；SCC缩点后依赖变森林，再DFS序背包。','SCC.scc取得col，合计包w/a；无前提包接虚根；run(0)。','O(nM+n)时间、O(nM)空间。',software)])

count=r'''
struct RerootCount {
    int n,mod;vector<vector<int>>son;vector<int>dp,pd,ans;
    RerootCount(int n=0,int m=1000000007){init(n,m);}
    void init(int n_,int m){n=n_;mod=m;son.assign(n+1,{});dp.assign(n+1,0);pd=ans=dp;}
    void add_edge(int u,int v){son[u].push_back(v);son[v].push_back(u);}
    void dfs(int u,int p){dp[u]=1%mod;for(int v:son[u])if(v!=p){dfs(v,u);dp[u]=dp[u]*(dp[v]+1)%mod;}}
    void dfs2(int u,int p){vector<int>a;for(int v:son[u])if(v!=p)a.push_back(v);int m=a.size();vector<int>pre(m+1,1%mod),suf(m+1,1%mod);
        for(int i=0;i<m;i++)pre[i+1]=pre[i]*(dp[a[i]]+1)%mod;
        for(int i=m-1;i>=0;i--)suf[i]=suf[i+1]*(dp[a[i]]+1)%mod;
        ans[u]=dp[u]*(pd[u]+1)%mod;
        for(int i=0;i<m;i++){int v=a[i];pd[v]=pre[i]*suf[i+1]%mod*(pd[u]+1)%mod;dfs2(v,u);}}
    void run(int root=1){dfs(root,0);pd[root]=0;dfs2(root,0);}
};
'''
add('dp','换根连通块计数','RerootCount',count,'计算每点被包含的连通点集数量；前后缀乘积移除一个孩子，支持非素数模。','O(n)时间与空间，mod<=1e9+7。',
 [('init/add_edge','无向树与正模数'),('run(root)','dp为含u子树块数，pd为父侧块数，ans为整树含u块数')],
 ['不能用逆元除去孩子贡献，非素数模或零贡献时不成立。','局部前后缀数组不会被递归覆盖；原共享数组需先算所有孩子再递归。','乘法两次取模，避免三个因子直接相乘溢出。'],src,[
 example('DP_V','Subtree','https://atcoder.jp/contests/dp/tasks/dp_v','给每点求该点为黑且全部黑点连通的染色数。','黑点集合就是包含指定点的连通点集，每个孩子选或不选。','读mod和树，run，逐行输出ans。','O(n)时间与空间。',r'''
 void solve(){int n,m;cin>>n>>m;RerootCount t(n,m);for(int i=1;i<n;i++){int u,v;cin>>u>>v;t.add_edge(u,v);}t.run();for(int i=1;i<=n;i++)cout<<t.ans[i]<<'\n';}
 ''',tests=[dict(input='3 100\n1 2\n2 3\n',output='3\n4\n3\n')]),
 example('CF543D','Road Improvement','https://codeforces.com/contest/543/problem/D','对每个首都，统计满足各路径最多一条未修路的道路修复方式。','以首都为根时，若父边未修，整棵子树内所有边必须修；否则子树继续有dp种选择，所以同样是(dp[v]+1)乘积。','输入2..n父节点，add_edge，run；输出ans。','O(n)时间与空间。',r'''
 void solve(){int n;cin>>n;RerootCount t(n);for(int i=2;i<=n;i++){int p;cin>>p;t.add_edge(p,i);}t.run();for(int i=1;i<=n;i++)cout<<t.ans[i]<<" \n"[i==n];}
 ''')])

distance=r'''
struct TreeDistanceDP {
    int n,mod=1000000007;vector<vector<int>>g;
    TreeDistanceDP(int n=0){init(n);}
    void init(int n_){n=n_;g.assign(n+1,{});}
    void add_edge(int u,int v){g[u].push_back(v);g[v].push_back(u);}
    void dfs(int u,int p,int d,vector<int>&cnt){if(d>=(int)cnt.size())return;cnt[d]++;for(int v:g[u])if(v!=p)dfs(v,u,d+1,cnt);}
    int equidistant(int k){if(k==1)return n;if(k==2)return n*(n-1)/2%mod;int ans=0;
        for(int u=1;u<=n;u++){vector<vector<int>>dp(n+1,vector<int>(k+1));for(auto &z:dp)z[0]=1;
            for(int v:g[u]){vector<int>cnt(n+1);dfs(v,u,1,cnt);for(int d=1;d<=n;d++)if(cnt[d])for(int j=k;j>=1;j--)dp[d][j]=(dp[d][j]+dp[d][j-1]*cnt[d])%mod;}
            for(int d=1;d<=n;d++)ans=(ans+dp[d][k])%mod;}return ans;
    }
    int pairs(int K){vector<vector<int32_t>>f(n+1,vector<int32_t>(K+1));int ans=0;
        function<void(int,int)>work=[&](int u,int p){f[u][0]=1;for(int v:g[u])if(v!=p){work(v,u);for(int d=0;d<K;d++)ans+=(int)f[u][d]*f[v][K-d-1];for(int d=1;d<=K;d++)f[u][d]+=f[v][d-1];}};
        work(1,0);return ans;
    }
};
'''
add('dp','树上距离分层计数','TreeDistanceDP',distance,'用深度层节点数合并统计；原等距点集按中心各分支选点，固定距离数对用子树深度卷积。','equidistant O(n²k)时间/O(nk)空间，适用n<=100；pairs O(nK)时间/空间。',
 [('equidistant(k)','所有大小k、两两等距的点集数模1e9+7'),('pairs(K)','无序不同点对距离恰好K的精确个数')],
 ['k=2任意点对均等距，必须单独处理；k>=3才有唯一顶点中心。','同中心不同分支才能选同距离点；每个分支至多选一个。','pairs深度计数int32_t减少nK内存，乘法显式转long long。'],src,[
 example('CF1551F','Equidistant Vertices','https://codeforces.com/contest/1551/problem/F','计数树上大小k的两两等距点集。','k>=3时必有唯一中心，所有选点距中心相同且来自不同分支。','多测，每组建树后equidistant(k)。','O(n²k)时间、O(nk)空间。',r'''
 void solve(){int T;cin>>T;while(T--){int n,k;cin>>n>>k;TreeDistanceDP t(n);for(int i=1;i<n;i++){int u,v;cin>>u>>v;t.add_edge(u,v);}cout<<t.equidistant(k)<<'\n';}}
 '''),
 example('CF161D','Distance in Tree','https://codeforces.com/contest/161/problem/D','统计距离恰好K的无序点对。','每对在LCA合并两条不同子树深度时唯一计入，深度和+1=K。','建树后pairs(K)。','O(nK)时间、O(nK)空间。',r'''
 void solve(){int n,K;cin>>n>>K;TreeDistanceDP t(n);for(int i=1;i<n;i++){int u,v;cin>>u>>v;t.add_edge(u,v);}cout<<t.pairs(K)<<'\n';}
 ''')])
