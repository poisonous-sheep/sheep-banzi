from common import *
binary=r'''
struct BinaryTreeKnapsack {
    static constexpr int INF=4000000000000000000LL;
    int n;vector<vector<int>>son;vector<array<int,2>>cost;vector<array<array<int,2>,2>>edge_cost;vector<vector<array<int,2>>>dp;
    BinaryTreeKnapsack(int n=0){init(n);}
    void init(int n_){n=n_;son.assign(n+1,{});cost.assign(n+1,{0,0});edge_cost.resize(n+1);for(auto &a:edge_cost)for(auto &b:a)b={0,0};dp.assign(n+1,{});}
    void add_edge(int u,int v){son[u].push_back(v);}
    void dfs(int u){dp[u]={{cost[u][0],INF},{INF,cost[u][1]}};
        for(int v:son[u]){dfs(v);int A=dp[u].size()-1,B=dp[v].size()-1;vector<array<int,2>>tmp(A+B+1,{INF,INF});
            for(int i=0;i<=A;i++)for(int j=0;j<=B;j++)for(int a=0;a<2;a++)for(int b=0;b<2;b++)if(dp[u][i][a]<INF&&dp[v][j][b]<INF&&edge_cost[v][a][b]<INF)
                tmp[i+j][a]=min(tmp[i+j][a],dp[u][i][a]+dp[v][j][b]+edge_cost[v][a][b]);
            dp[u].swap(tmp);}
    }
    vector<int>run(int root=1){dfs(root);vector<int>ans(n+1,INF);for(int k=0;k<(int)dp[root].size();k++)ans[k]=min(dp[root][k][0],dp[root][k][1]);return ans;}
};
'''
add('dp','二状态树形背包','BinaryTreeKnapsack',binary,'每点选0/1状态，价值来自点费用和父子状态费用；背包维记录状态1点数，覆盖原Monster Hunter模型。','按真实子树规模合并O(n²)时间；保存全部节点DP最坏O(n²)空间。',
 [('cost[u][state]','点选择两状态的费用'),('edge_cost[v][父状态][子状态]','父子费用，INF禁止组合'),('run(root)','返回恰好k个状态1点的最小费用数组')],
 ['原Monster Hunter已把hp[v]包含在子DP中，父状态0子状态0只额外加hp[v]，不能再加2hp[v]。','所有边和点费用累计须远小于INF；不可达先判断再相加。','边费用依赖父子状态，不能把状态维省略。'],['dp/树形动态规划进阶_比赛板子.md'],[
 example('Gym102992M','Monster Hunter','https://codeforces.com/gym/102992/problem/M','有限魔法可无成本杀任意怪，普通杀怪受父亲和存活孩子血量影响，求每个魔法次数的最小总力量。','先施放所有魔法；普通点自己的hp付一次，只有父子均普通时，子hp还会在父亲被杀时再付一次。','普通cost=hp、魔法cost=0；edge_cost[v][0][0]=hp[v]，run后输出全部k。','O(n²)时间/空间。',r'''
 void solve(){int T;cin>>T;while(T--){int n;cin>>n;BinaryTreeKnapsack t(n);for(int i=2;i<=n;i++){int p;cin>>p;t.add_edge(p,i);}for(int i=1;i<=n;i++){int hp;cin>>hp;t.cost[i]={hp,0};t.edge_cost[i][0][0]=hp;}auto ans=t.run();for(int k=0;k<=n;k++)cout<<ans[k]<<" \n"[k==n];}}
 ''',tests=[dict(input='1\n5\n1 2 3 4\n1 2 3 4 5\n',output='29 16 9 4 1 0\n')]),
 example('P2016','战略游戏','https://www.luogu.com.cn/problem/P2016','树上选最少士兵，使每条边至少一个端点被选。','每点0/1表示放不放，费用0/1；父子都不放的边状态禁止，就是树最小点覆盖。','建立有根输入树，cost={0,1}，edge_cost[v][0][0]=INF；run后取最小费用。','此统一背包版O(n²)时间/空间；只求最小值可去背包维得到O(n)专用DP。',r'''
 void solve(){int n;cin>>n;BinaryTreeKnapsack t(n);vector<vector<int>>e(n+1);for(int z=0;z<n;z++){int u,k;cin>>u>>k;u++;while(k--){int v;cin>>v;v++;e[u].push_back(v);e[v].push_back(u);}}for(int u=1;u<=n;u++)t.cost[u]={0,1};function<void(int,int)>dfs=[&](int u,int p){for(int v:e[u])if(v!=p){t.add_edge(u,v);t.edge_cost[v][0][0]=t.INF;dfs(v,u);}};dfs(1,0);auto ans=t.run(1);cout<<*min_element(ans.begin(),ans.end())<<'\n';}
 ''')])
