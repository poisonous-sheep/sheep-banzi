from common import *
kmp=r'''
struct KMP {
    vector<int>nxt,pat;
    void init(const vector<int>&a){pat=a;int n=a.size();nxt.assign(n,0);for(int i=1,j=0;i<n;i++){while(j&&a[i]!=a[j])j=nxt[j-1];if(a[i]==a[j])j++;nxt[i]=j;}}
    void init(const string&s){init(vector<int>(s.begin(),s.end()));}
    vector<int>find(const vector<int>&a){vector<int>ans;int m=pat.size();if(!m){for(int i=0;i<=(int)a.size();i++)ans.push_back(i+1);return ans;}
        for(int i=0,j=0;i<(int)a.size();i++){while(j&&a[i]!=pat[j])j=nxt[j-1];if(a[i]==pat[j])j++;if(j==m)ans.push_back(i-m+2),j=nxt[j-1];}return ans;}
    vector<int>find(const string&s){return find(vector<int>(s.begin(),s.end()));}
};
'''
add('杂','KMP字符串匹配','KMP',kmp,'前缀函数失配跳转在线性时间查找全部匹配；数字序列与字符串共用接口。','O(n+m)时间、O(m+匹配数)空间。',
 [('init(pattern)','建立模式前缀函数nxt，0基数组'),('find(text)','返回全部1基匹配起点，支持重叠匹配')],
 ['匹配后回退到nxt[m-1]，不能直接置0，否则漏重叠。','空模式按接口定义匹配n+1个边界；实际竞赛例题模式非空。','差分会出现负数，不能用char保存数字模式。'],['杂/kmp.cpp'],[
 example('P3375','KMP','https://www.luogu.com.cn/problem/P3375','输出模式串所有出现位置及每个前缀的最长border。','重复扫描通过前缀函数复用已知匹配长度。','init(s2)，find(s1)，依次输出nxt。','O(|s1|+|s2|)时间、O(|s2|+匹配数)空间。',r'''
 void solve(){string s,p;cin>>s>>p;KMP t;t.init(p);for(int x:t.find(s))cout<<x<<'\n';for(int i=0;i<(int)p.size();i++)cout<<t.nxt[i]<<" \n"[i+1==(int)p.size()];}
 '''),
 example('CF471D','MUH and Cube Walls','https://codeforces.com/contest/471/problem/D','允许整体上下平移，统计目标高度序列出现次数。','两序列可整体平移等价相邻差相同，转成整数序列匹配。','w=1直接答n；否则差分后init和find。','O(n+w)时间与O(n+w)空间。',r'''
 void solve(){int n,w;cin>>n>>w;vector<int>a(n),b(w);for(int &x:a)cin>>x;for(int &x:b)cin>>x;if(w==1){cout<<n<<'\n';return;}
 vector<int>x,y;for(int i=1;i<n;i++)x.push_back(a[i]-a[i-1]);for(int i=1;i<w;i++)y.push_back(b[i]-b[i-1]);KMP t;t.init(y);cout<<t.find(x).size()<<'\n';}
 ''',tests=[dict(input='13 5\n2 4 5 5 4 3 2 2 2 3 3 2 1\n3 4 4 3 2\n',output='2\n')])])

lb=r'''
struct LinearBasis {
    static const int B=62;array<int,B+1>p{};bool zero=false;
    void init(){p.fill(0);zero=false;}
    bool insert(int x){assert(x>=0);for(int i=B;i>=0;i--)if((x>>i)&1){if(!p[i]){p[i]=x;return true;}x^=p[i];}zero=true;return false;}
    bool exist(int x){for(int i=B;i>=0;i--)if((x>>i)&1)x^=p[i];return x==0;}
    int qur(int x=0){for(int i=B;i>=0;i--)x=max(x,x^p[i]);return x;}
    int rank(){int ans=0;for(int x:p)ans+=x!=0;return ans;}
    optional<int> kth(uint64_t k,bool nonempty=true){
        auto b=p;for(int i=0;i<=B;i++)if(b[i])for(int j=i+1;j<=B;j++)if((b[j]>>i)&1)b[j]^=b[i];
        vector<int>a;for(int x:b)if(x)a.push_back(x);
        // nonempty: k为1基；有非空零组合时，第1小为0。
        if(nonempty){if(!k)return nullopt;if(zero)--k;}
        if(k>=(1ULL<<a.size()))return nullopt;
        int ans=0;for(int i=0;i<(int)a.size();i++)if((k>>i)&1)ans^=a[i];return ans;
    }
};
'''
add('杂','线性基','LinearBasis',lb,'GF(2)消元维护可达异或空间，支持最大值、可表示判定、第k小及最大权线性无关集。','insert/exist/qur O(B)，kth O(B²)，空间O(B)，B=63。',
 [('insert(x)','独立时加入并返回true；相关时记录非空零组合'),('exist/qur(x)','判可表示；在x基础上求最大异或'),('kth(k,nonempty)','默认非空子集的1基第k小；nonempty=false则含空集且k为0基')],
 ['输入限制0<=x<2^63，位移用1ULL避免第63位符号溢出。','相关向量使0可由非空子集构成；空集与非空的排名含义必须分清。','第k小先消成低位无干扰的基，原按低位组合但未消元的写法不保证顺序。'],['杂/线性基.md'],[
 example('P3812','线性基','https://www.luogu.com.cn/problem/P3812','从给定整数中选任意子集，使异或和最大。','所有子集异或构成向量空间，逐位贪心最大化。','逐个insert，输出qur()。','O(nB)时间、O(B)空间。',r'''
 void solve(){int n;cin>>n;LinearBasis t;while(n--){int x;cin>>x;t.insert(x);}cout<<t.qur()<<'\n';}
 '''),
 example('P4151','最大XOR和路径','https://www.luogu.com.cn/problem/P4151','无向连通图求1到n的最大异或权路径，可重复边点。','任意路径异或为一条树路径值加环空间组合；每条非树边产生环异或。','DFS计算dis并insert(dis[u]^dis[v]^w)，最后qur(dis[n])。','O((n+m)B)时间、O(n+m+B)空间。',r'''
 void solve(){int n,m;cin>>n>>m;vector<vector<pair<int,int>>>g(n+1);while(m--){int u,v,w;cin>>u>>v>>w;g[u].push_back({v,w});g[v].push_back({u,w});}
 vector<int>vis(n+1),dis(n+1);LinearBasis t;function<void(int)>dfs=[&](int u){vis[u]=1;for(auto[v,w]:g[u])if(!vis[v]){dis[v]=dis[u]^w;dfs(v);}else t.insert(dis[u]^dis[v]^w);};dfs(1);cout<<t.qur(dis[n])<<'\n';}
 '''),
 example('P4570','元素','https://www.luogu.com.cn/problem/P4570','选择异或线性无关的矿石，使魔力总和最大。','向量独立集构成拟阵；按魔力降序贪心，insert返回是否保持独立。','按Magic排序，只有insert成功才累加Magic。','O(n log n+nB)时间、O(n+B)空间。',r'''
 void solve(){int n;cin>>n;vector<pair<int,int>>a(n);for(auto &[v,x]:a)cin>>x>>v;sort(a.rbegin(),a.rend());LinearBasis t;int ans=0;for(auto[v,x]:a)if(t.insert(x))ans+=v;cout<<ans<<'\n';}
 ''')])

geo=r'''
using db=long double;
const db EPS=1e-9L;
int sign(db x){return x<-EPS?-1:x>EPS?1:0;}
struct P {
    db x=0,y=0;P(){}P(db x,db y):x(x),y(y){}
    P operator+(P p)const{return {x+p.x,y+p.y};}P operator-(P p)const{return {x-p.x,y-p.y};}
    P operator*(db k)const{return {x*k,y*k};}P operator/(db k)const{return {x/k,y/k};}
    bool operator<(P p)const{return x!=p.x?x<p.x:y<p.y;}
    db dot(P p)const{return x*p.x+y*p.y;}db det(P p)const{return x*p.y-y*p.x;}
    db abs2()const{return dot(*this);}db abs()const{return sqrtl(abs2());}db distTo(P p)const{return (*this-p).abs();}
    db alpha()const{return atan2l(y,x);}P rot90()const{return {-y,x};}
    P rot(db a)const{return {x*cosl(a)-y*sinl(a),x*sinl(a)+y*cosl(a)};}
    P unit()const{assert(abs2()>0);return *this/abs();}
    int quad()const{return y>0||(y==0&&x>=0);}
    void read(){cin>>x>>y;}
};
struct Geometry {
    db cross(P a,P b,P c){return (b-a).det(c-a);}
    bool intersect(db a,db b,db c,db d){if(a>b)swap(a,b);if(c>d)swap(c,d);return sign(b-c)>=0&&sign(d-a)>=0;}
    bool onSeg(P a,P b,P p){return !sign(cross(a,b,p))&&sign((p-a).dot(p-b))<=0;}
    bool onSeg_strict(P a,P b,P p){return !sign(cross(a,b,p))&&sign((p-a).dot(p-b))<0;}
    bool isSS(P a,P b,P c,P d){return intersect(a.x,b.x,c.x,d.x)&&intersect(a.y,b.y,c.y,d.y)&&sign(cross(a,b,c))*sign(cross(a,b,d))<=0&&sign(cross(c,d,a))*sign(cross(c,d,b))<=0;}
    bool isSS_strict(P a,P b,P c,P d){return sign(cross(a,b,c))*sign(cross(a,b,d))<0&&sign(cross(c,d,a))*sign(cross(c,d,b))<0;}
    bool chkLL(P a,P b,P c,P d){return sign((b-a).det(d-c))!=0;}
    P isLL(P a,P b,P c,P d){assert(chkLL(a,b,c,d));return a+(b-a)*((c-a).det(d-c)/(b-a).det(d-c));}
    P proj(P a,P b,P p){P v=b-a;assert(v.abs2()>0);return a+v*(v.dot(p-a)/v.abs2());}
    P reflect(P a,P b,P p){return proj(a,b,p)*2-p;}
    db nearest(P a,P b,P p){if((b-a).abs2()==0)return p.distTo(a);P v=b-a;db t=clamp(v.dot(p-a)/v.abs2(),0.0L,1.0L);return p.distTo(a+v*t);}
    db disSS(P a,P b,P c,P d){if(isSS(a,b,c,d))return 0;return min({nearest(a,b,c),nearest(a,b,d),nearest(c,d,a),nearest(c,d,b)});}
};
'''
add('杂','点直线与线段几何','Geometry',geo,'保留P向量运算与相交、投影、反射、距离等接口，使用long double并处理退化线段。','单次运算O(1)时间/空间。',
 [('P::dot/det/rot/unit','点积叉积、旋转和单位向量'),('isSS/isSS_strict/onSeg','含边界与严格相交/在线段判定'),('chkLL/isLL/proj/reflect','非平行直线交点、投影、反射'),('nearest/disSS','点段或段段距离，支持点状线段')],
 ['sort用精确字典序；EPS比较不满足严格弱序，不能用于排序。','proj要求a!=b，isLL要求非平行；nearest单独处理a==b。','EPS按数据尺度调整；整数精确几何可改用__int128叉积。'],['杂/点线.cpp'],[
 example('CGL_1_A','Projection','https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A','求多点到给定直线的垂足。','点在直线方向上的正交分量由点积给出。','读取a,b，每点proj后输出x,y。','O(q)时间、O(1)额外空间。',r'''
 void solve(){P a,b;a.read();b.read();Geometry t;int q;cin>>q;cout<<fixed<<setprecision(10);while(q--){P p;p.read();P h=t.proj(a,b,p);cout<<h.x<<' '<<h.y<<'\n';}}
 '''),
 example('CGL_1_B','Reflection','https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B','求点关于直线的镜像。','垂足是点与镜像的中点，镜像=2*投影-原点。','调用reflect(a,b,p)。','O(q)时间、O(1)额外空间。',r'''
 void solve(){P a,b;a.read();b.read();Geometry t;int q;cin>>q;cout<<fixed<<setprecision(10);while(q--){P p;p.read();P h=t.reflect(a,b,p);cout<<h.x<<' '<<h.y<<'\n';}}
 ''')])

polar=geo+r'''
struct PolarSort {
    static bool cmp(P a,P b){if(a.quad()!=b.quad())return a.quad()>b.quad();db z=a.det(b);if(z!=0)return z>0;return a.abs2()<b.abs2();}
    void run(vector<P>&a){sort(a.begin(),a.end(),cmp);}
};
'''
add('杂','极角排序','PolarSort',polar,'按半平面再叉积排序非零向量，使圆周相邻关系和连续方向区间可枚举。','O(n log n)排序时间、O(log n)排序辅助栈。',
 [('run(a)/cmp','从正x轴逆时针排序；同方向按长度排序')],
 ['零向量应预先过滤；对任意浮点数叉积仍有精度风险，整数大坐标用__int128。','圆周相邻还需考虑最后和第一个的跨0夹角。'],['杂/点线.cpp'],[
 example('CF598C','Nearest vectors','https://codeforces.com/contest/598/problem/C','寻找最小夹角的一对非零向量。','最小夹角一定来自极角序的相邻向量；包含首尾圆周相邻。','按cmp排序带原编号向量，逐对用atan2(abs(det),dot)取夹角。','O(n log n)时间、O(n)空间。',r'''
 void solve(){int n;cin>>n;vector<pair<P,int>>a(n);for(int i=0;i<n;i++)a[i].first.read(),a[i].second=i+1;sort(a.begin(),a.end(),[](auto a,auto b){return PolarSort::cmp(a.first,b.first);});
 db best=10;pair<int,int>ans;for(int i=0;i<n;i++){int j=(i+1)%n;db ang=atan2l(fabsl(a[i].first.det(a[j].first)),a[i].first.dot(a[j].first));if(ang<best)best=ang,ans={a[i].second,a[j].second};}cout<<ans.first<<' '<<ans.second<<'\n';}
 '''),
 example('ABC139F','Engines','https://atcoder.jp/contests/abc139/tasks/abc139_f','选择若干向量，使和的长度最大。','最优向量集合可取为沿某个方向点积非负的半平面；极角序中是连续区间。枚举所有圆周连续区间必覆盖最优。','过滤零向量，run排序，枚举起点并累加最多n个向量。','O(n²+n log n)时间、O(n)空间。',r'''
 void solve(){int n;cin>>n;vector<P>a;while(n--){P p;p.read();if(p.abs2()>0)a.push_back(p);}PolarSort t;t.run(a);n=a.size();db ans=0;for(int i=0;i<n;i++){P s;for(int k=0;k<n;k++){s=s+a[(i+k)%n];ans=max(ans,s.abs2());}}cout<<fixed<<setprecision(12)<<sqrtl(ans)<<'\n';}
 ''')])

degree=r'''
struct DegreeDivide {
    int n,stamp=0,B;vector<vector<int>>g,heavy;vector<int>big,col,tim,lazy,ltim;
    DegreeDivide(int n=0){init(n);}
    void init(int n_){n=n_;stamp=0;g.assign(n+1,{});heavy=g;big.assign(n+1,0);col=tim=lazy=ltim=big;}
    void add_edge(int u,int v){g[u].push_back(v);g[v].push_back(u);}
    void build(const vector<int>&a){col=a;int m=0;for(int i=1;i<=n;i++)m+=g[i].size();B=sqrt(max(1LL,m))+1;
        for(int i=1;i<=n;i++)big[i]=(int)g[i].size()>=B;
        for(int i=1;i<=n;i++)for(int v:g[i])if(big[v])heavy[i].push_back(v);}
    int qur(int u){for(int v:heavy[u])if(ltim[v]>tim[u])col[u]=lazy[v],tim[u]=ltim[v];return col[u];}
    void change(int u,int c,bool self=false){++stamp;if(self)col[u]=c,tim[u]=stamp;
        if(big[u])lazy[u]=c,ltim[u]=stamp;else for(int v:g[u])col[v]=c,tim[v]=stamp;}
};
'''
add('杂','度数根号分治','DegreeDivide',degree,'小度点广播直接修改邻居，大度点广播记录时间戳；查询从相邻大点恢复最后一次颜色。','预处理O(n+m)，每次O(B+m/B)，B约sqrt(m)；空间O(n+m)。',
 [('add_edge/build(a)','静态无向图，a为1基初始颜色'),('qur(u)','读取含懒广播影响的当前颜色'),('change(u,c,self)','向所有邻居广播c；self=true也更新自己')],
 ['qur必须先于广播读取当前颜色，懒标记比较时间戳。','建图后build一次，动态增边不适用。','大点只有O(m/B)个，因此查询扫描的大点邻居有上界。'],['杂/根号分治.md'],[
 example('ABC219G','Propagation','https://atcoder.jp/contests/abc219/tasks/abc219_g','查询点将自身数字复制给所有邻居，最终输出所有点数字。','高次数邻居更新用重度懒广播规避星形图退化。','build初始col[i]=i；每次x先qur(x)，再change(x,c,false)。','O(n+m+q sqrt m)时间、O(n+m)空间。',r'''
 void solve(){int n,m,q;cin>>n>>m>>q;DegreeDivide t(n);while(m--){int u,v;cin>>u>>v;t.add_edge(u,v);}vector<int>a(n+1);iota(a.begin(),a.end(),0);t.build(a);while(q--){int x;cin>>x;int c=t.qur(x);t.change(x,c);}for(int i=1;i<=n;i++)cout<<t.qur(i)<<" \n"[i==n];}
 '''),
 example('Typical90-083','Colorful Graph','https://atcoder.jp/contests/typical90/tasks/typical90_ce','输出指定点当前颜色后，将它及全部邻居改成新颜色。','邻居广播与前题同模型，区别是本点也赋值。','初始全1；qur(x)输出后change(x,y,true)。','O(n+m+q sqrt m)时间、O(n+m)空间。',r'''
 void solve(){int n,m;cin>>n>>m;DegreeDivide t(n);while(m--){int u,v;cin>>u>>v;t.add_edge(u,v);}t.build(vector<int>(n+1,1));int q;cin>>q;while(q--){int x,y;cin>>x>>y;cout<<t.qur(x)<<'\n';t.change(x,y,true);}}
 ''')])
