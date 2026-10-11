from common import *
hd=r'''
struct HeuristicDivide {
    int n;vector<int>a,pre,nxt;
    void init(const vector<int>&v){a=v;n=a.size()-1;pre.assign(n+1,0);nxt.assign(n+1,n+1);map<int,int>last;
        for(int i=1;i<=n;i++){pre[i]=last[a[i]];if(pre[i])nxt[pre[i]]=i;last[a[i]]=i;}}
    bool dfs(int l,int r){if(l>r)return true;for(int x=l,y=r;x<=y;x++,y--){
        if(pre[x]<l&&nxt[x]>r)return dfs(l,x-1)&&dfs(x+1,r);
        if(pre[y]<l&&nxt[y]>r)return dfs(l,y-1)&&dfs(y+1,r);}return false;}
    bool non_boring(){return dfs(1,n);}
    int maximum_pairs(){vector<int>pos(n+1),lg(n+1);for(int i=1;i<=n;i++){assert(1<=a[i]&&a[i]<=n&&!pos[a[i]]);pos[a[i]]=i;}
        for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;vector<vector<int32_t>>st(lg[n]+1,vector<int32_t>(n+1));for(int i=1;i<=n;i++)st[0][i]=i;
        auto better=[&](int i,int j){return a[i]>a[j]?i:j;};for(int k=1;k<(int)st.size();k++)for(int i=1;i+(1<<k)-1<=n;i++)st[k][i]=better(st[k-1][i],st[k-1][i+(1<<(k-1))]);
        auto argmax=[&](int l,int r){int k=lg[r-l+1];return better(st[k][l],st[k][r-(1<<k)+1]);};
        function<int(int,int)>work=[&](int l,int r){if(l>=r)return 0LL;int m=argmax(l,r),ans=work(l,m-1)+work(m+1,r);
            if(m-l<r-m){for(int i=l;i<m;i++){int x=a[m]-a[i];if(x>0&&pos[x]>m&&pos[x]<=r)ans++;}}
            else for(int j=m+1;j<=r;j++){int x=a[m]-a[j];if(x>0&&pos[x]>=l&&pos[x]<m)ans++;}return ans;};
        return work(1,n);
    }
};
'''
add('数据结构','启发式分治','HeuristicDivide',hd,'允许划分不均衡，但寻找分界或统计只扫描短侧；保留双端唯一元素判定，增加最大值分界的短侧枚举。','non_boring O(n log n)时间/O(n)空间；maximum_pairs O(n log n)时间/空间（ST预处理）。',
 [('init(a)','1基数组'),('non_boring()','每个非空子区间都有唯一出现元素'),('maximum_pairs()','a必须为1..n排列；计数ai+aj=max(a[i..j])')],
 ['从单侧扫描唯一元素会退化为O(n²)。','枚举短侧并用值到位置映射查另一端，不能同时暴力枚举两侧。','递归可能是链，深度O(n)，栈风险与时间复杂度是两回事。'],['数据结构/模块一_启发式合并与启发式分治.md'],[
 example('UVA1608','Non-boring sequences','https://onlinejudge.org/external/16/1608.pdf','判定任意子区间是否都有只出现一次的值。','选当前区间唯一值为分界，含分界的所有区间已合法，只递归左右。','init后non_boring，多测输出non-boring或boring。','O(n log n)时间、O(n)空间。',r'''
 void solve(){int T;cin>>T;while(T--){int n;cin>>n;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];HeuristicDivide t;t.init(a);cout<<(t.non_boring()?"non-boring":"boring")<<'\n';}}
 '''),
 example('CF1156E','Special Segments','https://codeforces.com/contest/1156/problem/E','排列中计数两端和等于区间最大值的区间。','以区间最大值m分界，跨分界的两端只枚举短侧，另一值及位置由最大值减已知值确定。','init排列，maximum_pairs。','O(n log n)时间/空间。',r'''
 void solve(){int n;cin>>n;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];HeuristicDivide t;t.init(a);cout<<t.maximum_pairs()<<'\n';}
 ''')])

base=r'''
struct FunctionalGraph {
    int n;vector<int>p,w,val;vector<int32_t>head,nxt;vector<char>vis,on;vector<vector<int>>cycles;
    FunctionalGraph(int n=0){init(n);}
    void init(int n_){n=n_;p.assign(n+1,0);w=val=p;head.assign(n+1,-1);nxt=head;vis.assign(n+1,0);on=vis;cycles.clear();}
    void build(){fill(head.begin(),head.end(),-1);fill(vis.begin(),vis.end(),0);fill(on.begin(),on.end(),0);cycles.clear();
        for(int u=1;u<=n;u++){assert(1<=p[u]&&p[u]<=n);nxt[u]=head[p[u]];head[p[u]]=u;}
        for(int i=1;i<=n;i++)if(!vis[i]){int u=i;while(!vis[u])vis[u]=1,u=p[u];if(vis[u]==1){vector<int>c;int v=u;do{c.push_back(v);on[v]=1;v=p[v];}while(v!=u);cycles.push_back(c);}
            u=i;while(vis[u]==1)vis[u]=2,u=p[u];}
    }
    void orient(const vector<array<int,3>>&edges){
        vector<vector<array<int,3>>>g(n+1);vector<int>deg(n+1);int eid=0;for(auto[u,v,c]:edges){g[u].push_back({v,c,eid});g[v].push_back({u,c,eid++});deg[u]++;deg[v]++;}
        queue<int>q;for(int u=1;u<=n;u++)if(deg[u]==1)q.push(u);vector<char>removed(n+1);
        while(!q.empty()){int u=q.front();q.pop();removed[u]=1;for(auto[v,c,id]:g[u])if(!removed[v]){p[u]=v;w[u]=c;if(--deg[v]==1)q.push(v);break;}}
        vector<char>used(n+1);for(int i=1;i<=n;i++)if(!removed[i]&&!used[i]){int u=i,prev=-1;do{used[u]=1;array<int,3>z={0,0,-1};for(auto[v,c,id]:g[u])if(!removed[v]&&id!=prev){z={v,c,id};break;}assert(z[0]);p[u]=z[0];w[u]=z[1];prev=z[2];u=z[0];}while(u!=i);}
        build();
    }
};
'''
mis=base+r'''
struct Knight:FunctionalGraph {
    static constexpr int INF=4000000000000000000LL;
    vector<array<int,2>>dp;
    Knight(int n=0):FunctionalGraph(n){}
    void dfs(int u){dp[u]={0,val[u]};for(int v=head[u];v!=-1;v=nxt[v])if(!on[v]){dfs(v);dp[u][0]+=max(dp[v][0],dp[v][1]);dp[u][1]+=dp[v][0];}}
    int run(){build();dp.assign(n+1,{0,0});int ans=0;
        for(auto c:cycles){for(int u:c)dfs(u);if(c.size()==1){ans+=dp[c[0]][0];continue;}int best=-INF;
            for(int first=0;first<2;first++){int f=first?-INF:dp[c[0]][0],g=first?dp[c[0]][1]:-INF;
                for(int i=1;i<(int)c.size();i++){int u=c[i];int nf=max(f,g)+dp[u][0],ng=f==-INF?-INF:f+dp[u][1];f=nf;g=ng;}best=max(best,first?f:max(f,g));}ans+=best;}
        return ans;
    }
};
'''
add('图论','基环树最大权独立集','Knight',mis,'每个函数图分量一个环；外挂树选/不选DP后，环枚举首点选择并检查首尾冲突。','O(n)时间与空间。',
 [('p/val','每点唯一后继与点收益；1基'),('orient(edges)','无向基环森林转为函数图，边为{u,v,w}'),('run()','重建反向边并求全图最大独立集权和')],
 ['自环点不能选；二点互指构成重边环，也不能同时选。','压平原vector<vector<ll>>的两状态表减少百万点内存，递归树DP和环递推保持。','orient仅接受每个分量恰好一个环；树或多环图不适用。'],src if (src:= ['图/图论竞赛复习_严格课件注释版.md']) else [],[
 example('P2607','骑士','https://www.luogu.com.cn/problem/P2607','每位骑士有收益和一个不能同时选的对象，最大总收益。','每点恰好一条指向冲突对象的边，弱分量是基环树。','输入收益val及后继p，run。','O(n)时间/空间。',r'''
 void solve(){int n;cin>>n;Knight t(n);for(int u=1;u<=n;u++)cin>>t.val[u]>>t.p[u];cout<<t.run()<<'\n';}
 '''),
 example('P1453','城市环路','https://www.luogu.com.cn/problem/P1453','城市构成无向基环图，不能选相邻城市建店，求利润。','无向唯一环可定向为函数图，之后独立集模型与骑士相同。','0基城市转1基，orient(edges)，run后乘系数k，保留1位小数。','O(n)时间/空间。',r'''
 void solve(){int n;cin>>n;Knight t(n);for(int i=1;i<=n;i++)cin>>t.val[i];vector<array<int,3>>e(n);for(auto &z:e){cin>>z[0]>>z[1];z[0]++;z[1]++;z[2]=0;}long double k;cin>>k;t.orient(e);cout<<fixed<<setprecision(1)<<t.run()*k<<'\n';}
 ''')])

path=base+r'''
struct Island:FunctionalGraph {
    vector<int>d;int inside;
    Island(int n=0):FunctionalGraph(n){}
    void dfs(int u){d[u]=0;for(int v=head[u];v!=-1;v=nxt[v])if(!on[v]){dfs(v);int x=d[v]+w[v];inside=max(inside,d[u]+x);d[u]=max(d[u],x);}}
    int ring_path(const vector<int>&a,const vector<int>&b){int k=a.size();if(k<=1)return 0;vector<int>s(2*k);for(int i=1;i<2*k;i++)s[i]=s[i-1]+b[(i-1)%k];deque<int>q;int ans=0;
        for(int i=0;i<2*k;i++){while(!q.empty()&&i-q.front()>=k)q.pop_front();if(!q.empty())ans=max(ans,a[i%k]+s[i]+a[q.front()%k]-s[q.front()]);while(!q.empty()&&a[q.back()%k]-s[q.back()]<=a[i%k]-s[i])q.pop_back();q.push_back(i);}return ans;}
    int run(){build();d.assign(n+1,0);int ans=0;for(auto c:cycles){inside=0;vector<int>a,b;for(int u:c){dfs(u);a.push_back(d[u]);b.push_back(w[u]);}ans+=max(inside,ring_path(a,b));}return ans;}
    struct info{int minus,plus,best;};
    info merge(info a,info b){return {max(a.minus,b.minus),max(a.plus,b.plus),max({a.best,b.best,a.minus+b.plus})};}
    int minimum_cut_diameter(){build();assert(cycles.size()==1);auto c=cycles[0];int k=c.size();d.assign(n+1,0);inside=0;for(int u:c)dfs(u);if(k<=1)return inside;
        vector<int>s(2*k);for(int i=1;i<2*k;i++)s[i]=s[i-1]+w[c[(i-1)%k]];
        vector<pair<info,info>>in,out;auto push=[&](info z){in.push_back({z,in.empty()?z:merge(in.back().second,z)});};
        auto pop=[&](){if(out.empty())while(!in.empty()){info z=in.back().first;in.pop_back();out.push_back({z,out.empty()?z:merge(z,out.back().second)});}out.pop_back();};
        auto qur=[&](){if(in.empty())return out.back().second.best;if(out.empty())return in.back().second.best;return merge(out.back().second,in.back().second).best;};
        int ans=4000000000000000000LL;for(int i=0;i<2*k-1;i++){push({d[c[i%k]]-s[i],d[c[i%k]]+s[i],0});if(i>=k)pop();if(i>=k-1)ans=min(ans,max(inside,qur()));}return ans;
    }
};
'''
add('图论','基环树最长路径与断环直径','Island',path,'外挂树求向下最长链与内部直径；环复制后滑窗维护d[j]-前缀距离，最长简单路径可取长弧。','O(n)时间与空间；断环版本用双栈聚合队列同为O(n)。',
 [('p/w','函数图后继与该后继边非负权'),('run()','返回全部分量最长简单路径长度之和'),('orient/minimum_cut_diameter','一个无向基环图中切掉一条环边，使所得树直径最小')],
 ['最长简单路径与最短路意义的直径不同，前者可以选择较长环弧。','环滑窗严格排除两端同环点，不能绕完整一圈。','断环队列信息有方向，左右merge顺序不能交换。'],['图/图论竞赛复习_严格课件注释版.md'],[
 example('P4381','Island','https://www.luogu.com.cn/problem/P4381','多个基环分量各取最长简单路径，再把长度相加。','路径要么在一个外挂树内，要么经环连接不同树根，分别计算取最大。','输入p[u],w[u]，run。','O(n)时间与空间。',r'''
 void solve(){int n;cin>>n;Island t(n);for(int i=1;i<=n;i++)cin>>t.p[i]>>t.w[i];cout<<t.run()<<'\n';}
 '''),
 example('CF835F','Roads in the Kingdom','https://codeforces.com/contest/835/problem/F','删去基环图的一条边保持连通，使剩余图最大点距最小。','只能删环边；每种断法对应复制环的k点连续窗口，窗口内最长路径由有序聚合信息维护。','读边orient；调用minimum_cut_diameter，与树内直径取max。','O(n)时间与空间。',r'''
 void solve(){int n;cin>>n;vector<array<int,3>>e(n);for(auto &z:e)cin>>z[0]>>z[1]>>z[2];Island t(n);t.orient(e);cout<<t.minimum_cut_diameter()<<'\n';}
 ''')])
