from common import *

crystal=r'''
struct Crystalfly {
    int n;vector<vector<int>>e;vector<int>a,t,f,g,h;
    Crystalfly(int n=0){init(n);}
    void init(int n_){n=n_;e.assign(n+1,{});a.assign(n+1,0);t=a;f=a;g=a;h=a;}
    void add_edge(int u,int v){e[u].push_back(v);e[v].push_back(u);}
    void dfs(int u,int fa){int sum=0,best=0;pair<int,int>mx1={-1,0},mx2={-1,0};
        for(int v:e[u])if(v!=fa){dfs(v,u);sum+=f[v];best=max(best,a[v]);if(t[v]==3){pair<int,int>z={a[v],v};if(z>mx1){mx2=mx1;mx1=z;}else if(z>mx2)mx2=z;}}
        h[u]=a[u]+sum;f[u]=sum+best;
        for(int v:e[u])if(v!=fa){int other=(mx1.second==v?mx2.first:mx1.first);if(other>=0)f[u]=max(f[u],sum+h[v]-f[v]+other);}
        g[u]=f[u]+a[u];
    }
    int run(int root=1){dfs(root,0);return g[root];}
};
'''
add('dp','Crystalfly三状态树DP','Crystalfly',crystal,'树上抓蝴蝶，邻点第一次被惊动后t≤3秒末消失。f是不计当前点收益的最优，g=f+a，h表示抓当前点后立刻返回的收益。','O(n)时间/O(n)空间。',
 [('a[u],t[u]','填写正收益与1..3的消失延迟'),('add_edge; run(root)','无根树建边，从起点返回最大收益')],
 ['第1秒下到某子点再立即返回，该子点不要求t=3；第3秒进入的第二个子点才要求t=3。原OCR版误限制第一点，官方第二样例即反例。','不能用本板子处理t>3，状态会不足。','mx记录点编号，排除同一子点，避免相同a导致混淆。','会在之后访问已失去自身收益的子树，f仍须加到基础sum中。','长链递归须注意栈容量；64位存收益和。'],['dp/树形动态规划进阶_比赛板子.md'],[
 example('Gym103470H','Crystalfly','https://codeforces.com/gym/103470/problem/H','在树上行走抓晶蝶，邻点晶蝶被首次惊动后延迟1..3秒消失，求最大收益。','t≤3使一个父亲处最多及时取得两个子点收益；枚举立即返回的第一子点，配不同的t=3第二子点，保留深入与后续失收益遍历两种贡献。','读T、n、a、t、边，调用run(1)。','O(n)时间/O(n)空间。',r'''
 void solve(){int T;cin>>T;while(T--){int n;cin>>n;Crystalfly c(n);for(int u=1;u<=n;u++)cin>>c.a[u];for(int u=1;u<=n;u++)cin>>c.t[u];for(int i=1;i<n;i++){int u,v;cin>>u>>v;c.add_edge(u,v);}cout<<c.run()<<'\n';}}
 ''',tests=[dict(input='2\n5\n1 10 100 1000 10000\n1 2 1 1 1\n1 2\n1 3\n2 4\n2 5\n5\n1 10 100 1000 10000\n1 3 1 1 1\n1 2\n1 3\n2 4\n2 5\n',output='10101\n10111\n')])],gap='目前仅核实1道独立原题。洛谷P9847、QOJ6438为同题镜像，不计作第二道例题。')

kingdom=r'''
struct KingdomPower {
    int n;vector<int>fa,dep;vector<array<int,2>>dp;
    KingdomPower(int n=0){init(n);}
    void init(int n_){n=n_;fa.assign(n+1,0);dep=fa;dp.assign(n+1,{0,0});}
    int run(){for(int u=1;u<=n;u++){if(u>1){assert(1<=fa[u]&&fa[u]<u);dep[u]=dep[fa[u]]+1;}dp[u]={0,dep[u]};}
        for(int v=n;v>=2;v--){int u=fa[v];dp[u][1]=min({dp[u][1]+dp[v][1],dp[u][1]+dp[v][0]+2,dp[u][0]+dp[v][1]});dp[u][0]+=dp[v][0]+2;}
        return min(dp[1][0],dp[1][1]);}
};
'''
add('dp','Kingdom军队遍历树DP','KingdomPower',kingdom,'根可派任意多支军队，每次只能移动一支一步，求访问全树的最小总步数。保留原稿按父编号倒序合并的线性算法。','O(n)时间/O(n)空间。',
 [('fa[2..n]','填写父亲，需满足fa[u]<u'),('run()','最小总移动步数')],
 ['dp0是从u出发并返回u、完整访问当前已合并子树的闭合行走费用，dp1允许额外从根派兵并保留未闭合行走；原稿把0/1的返回语义写反，已按转移修正。','倒序合并依赖父编号较小；其他编号应按后序处理，不能原样调用。','原题每秒仅一支军队移动，不能改成所有军队同时移动后的完成时间。'],['dp/树形动态规划进阶_比赛板子.md'],[
 example('Gym102769K',"Kingdom’s Power",'https://codeforces.com/gym/102769/problem/K','根有无限军队，每秒指定一支沿边移动一步，最少多久访问全树。','单兵闭合分支每条边往返付2；开放分支可以接已有军队或另从根派兵，三种合并择优。','读T及每组n、父数组，run，输出Case #x: ans。','O(n)时间/O(n)空间。',r'''
 void solve(){int T;cin>>T;for(int tc=1;tc<=T;tc++){int n;cin>>n;KingdomPower t(n);for(int u=2;u<=n;u++)cin>>t.fa[u];cout<<"Case #"<<tc<<": "<<t.run()<<'\n';}}
 ''',tests=[dict(input='2\n3\n1 1\n6\n1 2 3 4 4\n',output='Case #1: 2\nCase #2: 6\n')])],gap='目前仅核实1道独立原题；未将另一种军队同时移动的题混作本板子例题。')

interval=r'''
struct IntervalSplit {
    struct info{int l,r,w;};
    static constexpr int INF=4000000000000000000LL;
    int n,mode;vector<int>x;vector<info>a;vector<vector<int>>dp;
    void init_enemies(vector<info>p){mode=0;a=p;x.clear();for(auto z:a){x.push_back(z.l);x.push_back(z.r);}sort(x.begin(),x.end());x.erase(unique(x.begin(),x.end()),x.end());n=x.size();
        for(auto &z:a){z.l=lower_bound(x.begin(),x.end(),z.l)-x.begin();z.r=lower_bound(x.begin(),x.end(),z.r)-x.begin();}dp.assign(n,vector<int>(n,-1));}
    void init_cuts(int length,vector<int>cuts){mode=1;x=cuts;sort(x.begin(),x.end());assert(adjacent_find(x.begin(),x.end())==x.end());x.insert(x.begin(),0);x.push_back(length);n=cuts.size();dp.assign(n,vector<int>(n,-1));}
    int dfs(int l,int r){if(l>r)return 0;int &ans=dp[l][r];if(ans!=-1)return ans;int L=l,R=r,cost=0;
        if(mode==0){int pos=-1;for(int i=0;i<(int)a.size();i++)if(a[i].l>=l&&a[i].r<=r&&(pos==-1||a[i].w>a[pos].w))pos=i;
            if(pos==-1)return ans=0;L=a[pos].l;R=a[pos].r;cost=a[pos].w;}
        else cost=x[r+2]-x[l];
        ans=INF;for(int k=L;k<=R;k++)ans=min(ans,dfs(l,k-1)+dfs(k+1,r)+cost);return ans;}
    int run(){return n?dfs(0,n-1):0;}
};
'''
add('dp','区间强制对象分治','IntervalSplit',interval,'选择一次事件作为区间分界，付当前费用后，左右不再互相影响。敌人模型由最远对象限定合法分界；切木棍模型由当前区间长度决定费用。','n为敌人数、K≤2n为端点数：O(K²(n+K))时间/O(K²+n)空间；切木棍q切点：O(q³)时间/O(q²)空间。',
 [('init_enemies({l,r,w}列表)','消灭期限区间内的敌人；费用为当前最远距离'),('init_cuts(length,cuts)','切木棍；正且不同的切点需严格位于(0,length)'),('run()','返回最小费用')],
 ['左右必须递归[l,k-1]和[k+1,r]。原OCR版闭区间solve(l,k)+solve(k,r)可能无限递归，且l==r仍可能存在敌人。','敌人中跨过所选k的对象全部被此最远对象所需的一击消灭，剩余仅完全位于左右的期限区间。','压缩仅保留期限端点即可，总有最优射击时刻可移动到某端点。','切木棍的费用取两侧已切边界距离，和敵人最大距离属于同一分界递推的两种初始化；接口显式区分，不能混用。'],['dp/区间动态规划进阶_比赛板子.md'],[
 example('P4766','Outer space invaders','https://www.luogu.com.cn/problem/P4766','敌人在各时间区间出现，一次半径R的冲击波可击中当前距离≤R的敌人，费用R，求全灭最小费用。','先考虑最远敌人被杀时刻k；该击可消灭所有跨k敌人，余下左右期限区间独立。','读T及期限a,b和距离d，init_enemies，run。','O(n³)时间/O(n²)空间，离散时间点≤2n。',r'''
 void solve(){int T;cin>>T;while(T--){int n;cin>>n;vector<IntervalSplit::info>a(n);for(auto &z:a)cin>>z.l>>z.r>>z.w;IntervalSplit t;t.init_enemies(a);cout<<t.run()<<'\n';}}
 ''',tests=[dict(input='3\n1\n1 1 7\n2\n1 2 4\n2 3 7\n2\n1 1 4\n2 2 7\n',output='7\n7\n11\n')]),
 example('UVA10003','Cutting Sticks','https://onlinejudge.org/external/100/10003.pdf','在给定位置切断木棍，每次费用为正在切的那段长度，选切割顺序使总费用最小。','把第一次切割k作为分界，左右后续独立。沿用相同dfs分界框架，将费用替换为两侧边界长度，允许分界为全部待切点。','循环读length直到0，读q和切点，init_cuts，run，输出指定英文句式。','O(q³)时间/O(q²)空间。',r'''
 void solve(){int length;while(cin>>length&&length){int q;cin>>q;vector<int>cuts(q);for(int &x:cuts)cin>>x;IntervalSplit t;t.init_cuts(length,cuts);cout<<"The minimum cutting is "<<t.run()<<".\n";}}
 ''',tests=[dict(input='100\n3\n25 50 75\n10\n4\n4 5 7 8\n0\n',output='The minimum cutting is 200.\nThe minimum cutting is 22.\n')])])
