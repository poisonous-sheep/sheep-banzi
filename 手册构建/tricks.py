from common import *

xor=r'''
struct XorCompare {
    int subsequence(const vector<int>&a,int B=8){int n=a.size(),ans=0,lim=1LL<<B;vector<int>dp(n,1);
        for(int i=0;i<n;i++){assert(0<=a[i]&&a[i]<lim);for(int j=max(0LL,i-lim+1);j<i;j++)if((a[j]^i)<(a[i]^j))dp[i]=max(dp[i],dp[j]+1);ans=max(ans,dp[i]);}return ans;}
    int max_xor(int l,int r){assert(0<=l&&l<=r);int x=l^r,ans=0;while(x){ans=(ans<<1)|1;x>>=1;}return ans;}
};
'''
add('tirick','异或比较与最高不同位','XorCompare',xor,'非负数满足|x-y|≤x xor y≤x+y；异或比较由最高不同位决定，低位值域可截断DP转移。','subsequence O(n*2^B)时间/O(n)空间；max_xor O(log r)时间/O(1)空间。',
 [('subsequence(a,B)','0-based下标；每个a[i]<2^B，最长符合交叉异或比较的子序列'),('max_xor(l,r)','区间内任意两个数的最大异或')],
 ['下标差≥2^B时，高位大小已经使CF1720条件不可能成立；只能在值域小于2^B时截断。','D2没有D1的ai≤200限制，不能照用窗口256。','max_xor由l xor r最高位确定，l=r时答案0。'],['tirick/总结.md'],[
 example('CF1720D1','Xor-Subsequence (easy version)','https://codeforces.com/problemset/problem/1720/D1','ai≤200，选最长子序列，使相邻所选下标i<j满足ai xor j < aj xor i，下标从0起。','高于第7位只有下标贡献，间距≥256必然失败；仅枚举最近255个前驱。','读T、a，subsequence(a,8)。','O(256n)时间/O(n)空间。',r'''
 void solve(){int T;cin>>T;XorCompare t;while(T--){int n;cin>>n;vector<int>a(n);for(int &x:a)cin>>x;cout<<t.subsequence(a)<<'\n';}}
 '''),
 example('CF276D','Little Girl and Maximum XOR','https://codeforces.com/problemset/problem/276/D','从整数区间[l,r]选两数使异或最大。','l,r最高不同位以下可以构造全1；最高不同位以上必须一致。','max_xor(l,r)。','O(log r)时间/O(1)空间。',r'''
 void solve(){int l,r;cin>>l>>r;XorCompare t;cout<<t.max_xor(l,r)<<'\n';}
 ''')])

man=r'''
struct Manhattan {
    int mn1=LLONG_MAX,mx1=LLONG_MIN,mn2=LLONG_MAX,mx2=LLONG_MIN;
    void init(){mn1=mn2=LLONG_MAX;mx1=mx2=LLONG_MIN;}
    void add(int x,int y){int u=x+y,v=x-y;mn1=min(mn1,u);mx1=max(mx1,u);mn2=min(mn2,v);mx2=max(mx2,v);}
    int diameter(){assert(mn1!=LLONG_MAX);return max(mx1-mn1,mx2-mn2);}
    int qur(int x,int y){assert(mn1!=LLONG_MAX);int u=x+y,v=x-y;return max({llabs(u-mn1),llabs(u-mx1),llabs(v-mn2),llabs(v-mx2)});}
};
'''
add('tirick','曼哈顿距离坐标旋转','Manhattan',man,'用u=x+y,v=x-y把平面曼哈顿距离变为旋转坐标的切比雪夫距离；最大距离只需两维极值。','add/qur/diameter O(1)；建n点O(n)时间/O(1)额外空间。',
 [('add(x,y)','加入点，维护两维极值'),('diameter()','已有点中最大曼哈顿距离'),('qur(x,y)','询问到已有点的最大曼哈顿距离')],
 ['坐标和、差、最终距离均须在long long内。','旋转后的整数坐标满足奇偶约束，若反求点或统计格点必须检查；本最大值问题不需要。','仅维护極值无法回答最小距离。'],['tirick/总结.md'],[
 example('ABC178E','Dist Max','https://atcoder.jp/contests/abc178/tasks/abc178_e','求平面n点两两曼哈顿距离的最大值。','max(|Δu|,|Δv|)的最大值由每一维最大减最小得到。','add所有点，diameter。','O(n)时间/O(1)额外空间。',r'''
 void solve(){int n;cin>>n;Manhattan t;while(n--){int x,y;cin>>x>>y;t.add(x,y);}cout<<t.diameter()<<'\n';}
 '''),
 example('Typical90036','Max Manhattan Distance','https://atcoder.jp/contests/typical90/tasks/typical90_aj','多次指定一个已有点，询问到所有点的最大曼哈顿距离。','两维极值由全部点共享，每问只比较到四个端点。','保留点数组；add预处理，qur(a[q])。','O(n+q)时间/O(n)空间（保存输入点）。',r'''
 void solve(){int n,q;cin>>n>>q;vector<pair<int,int>>a(n+1);Manhattan t;for(int i=1;i<=n;i++){cin>>a[i].first>>a[i].second;t.add(a[i].first,a[i].second);}while(q--){int k;cin>>k;cout<<t.qur(a[k].first,a[k].second)<<'\n';}}
 ''')])

perm=r'''
struct Permutation {
    int n;vector<int>a,pos;vector<vector<int>>cycle;
    void init(vector<int>p){a=p;n=a.size()-1;pos.assign(n+1,0);for(int i=1;i<=n;i++){assert(1<=a[i]&&a[i]<=n&&!pos[a[i]]);pos[a[i]]=i;}}
    void build(){cycle.clear();vector<int>vis(n+1);for(int u=1;u<=n;u++)if(!vis[u]){vector<int>c;int v=u;while(!vis[v]){vis[v]=1;c.push_back(v);v=a[v];}cycle.push_back(c);}}
    int min_swaps(){build();return n-cycle.size();}
    vector<pair<int,int>>sort_swaps(){vector<pair<int,int>>ans;for(int i=1;i<=n;i++)if(a[i]!=i){int j=pos[i];ans.push_back({i,j});swap(a[i],a[j]);pos[a[i]]=i;pos[a[j]]=j;}return ans;}
    int cover_ways(int mod=998244353){build();vector<int>f(n+2);f[1]=1;for(int i=2;i<=n+1;i++)f[i]=(f[i-1]+f[i-2])%mod;int ans=1;
        for(auto &c:cycle){int L=c.size();int ways=L==1?1:(f[L-1]+f[L+1])%mod;ans=ans*ways%mod;}return ans;}
};
'''
add('tirick','置换环分解','Permutation',perm,'排列分解为互不相交的环；任意交换最小次数n-环数。环上的局部选择可独立计数。','build/min_swaps/sort_swaps O(n)时间与空间；cover_ways O(n)时间与空间。',
 [('init(1-based排列)','校验1..n各出现一次'),('build()/cycle','遍历所有置换环'),('sort_swaps()','返回排序所需最少交换，修改a/pos'),('cover_ways(mod)','每个环选点覆盖全部相邻环边的方案乘积')],
 ['任意交换和相邻交换不同；相邻交换应计算逆序对。','一个长度L环最少L-1次交换。','ABC247F长度1的自环只有选此卡一种；长度2允许平行边，方案数3。'],['tirick/总结.md'],[
 example('ABC350C','Sort','https://atcoder.jp/contests/abc350/tasks/abc350_c','将排列用最多n-1次任意交换排好，并输出交换。','每次把位置i正确值换入，拆分置换环，总次数正好n-环数。','init，sort_swaps，输出操作列表。','O(n)时间/O(n)空间。',r'''
 void solve(){int n;cin>>n;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];Permutation t;t.init(a);auto ans=t.sort_swaps();cout<<ans.size()<<'\n';for(auto [u,v]:ans)cout<<u<<' '<<v<<'\n';}
 '''),
 example('ABC247F','Cards','https://atcoder.jp/contests/abc247/tasks/abc247_f','每张卡两面分别来自两个排列，选卡使1..n每个数至少出现在一张所选卡的任一面上，计数。','用排列p的逆位置把卡映射成i→pos[q[i]]的置换。每个数是相邻两卡共享的环边，选卡等价于环顶点覆盖。长度L方案F[L-1]+F[L+1]。','构造a，init，cover_ways；自环专门处理。','O(n)时间/O(n)空间。',r'''
 void solve(){int n;cin>>n;vector<int>p(n+1),pos(n+1),a(n+1);for(int i=1;i<=n;i++){cin>>p[i];pos[p[i]]=i;}for(int i=1,q;i<=n;i++){cin>>q;a[i]=pos[q];}Permutation t;t.init(a);cout<<t.cover_ways()<<'\n';}
 ''')])

prefix=r'''
struct PrefixPairs {
    unordered_map<int,int>cnt;int ans=0;
    void init(int reserve_n=0){cnt.clear();cnt.reserve(reserve_n*2+1);ans=0;}
    int add(int key){int old=cnt[key];ans+=old;cnt[key]++;return old;}
};
'''
add('tirick','前缀关系计数','PrefixPairs',prefix,'把满足条件的区间转为两个前缀的相同键值，按顺序统计此前相同前缀数。','n次add期望O(n)时间/O(n)空间；unordered_map最坏可O(n²)。',
 [('init(n)','清空并预留容量'),('add(key)','累计此前等key前缀数量，返回这次新增对数'),('ans','当前前缀对数，即合法区间数')],
 ['先加入空前缀，再逐点加入，才能统计从位置1开始的区间。','区间计数最高n(n+1)/2，需要64位。','使用模前缀时负余数要归一化；对恶意哈希可改map获得O(n log n)最坏界。'],['tirick/总结.md'],[
 example('CF1398C','Good Subarrays','https://codeforces.com/problemset/problem/1398/C','数字字符串中求元素和等于长度的子区间数。','s[r]-s[l]=r-l转为s[r]-r=s[l]-l，键为前缀和减前缀长度。','init(n+1)，add(0)，逐位计算sum-i并add，输出ans。','期望O(n)时间/O(n)空间。',r'''
 void solve(){int T;cin>>T;while(T--){int n;string s;cin>>n>>s;PrefixPairs t;t.init(n+1);t.add(0);int sum=0;for(int i=1;i<=n;i++){sum+=s[i-1]-'0';t.add(sum-i);}cout<<t.ans<<'\n';}}
 '''),
 example('ABC105D','Candy Distribution','https://atcoder.jp/contests/abc105/tasks/abc105_d','求数组区间和能被m整除的区间数。','两前缀和同余，键为前缀和模m。','add空前缀0，逐个取模加入，输出ans。','期望O(n)时间/O(min(n,m))空间。',r'''
 void solve(){int n,m;cin>>n>>m;PrefixPairs t;t.init(n+1);t.add(0);int s=0;while(n--){int x;cin>>x;s=(s+x)%m;t.add(s);}cout<<t.ans<<'\n';}
 ''')])

gcd=r'''
struct GcdDifference {
    int stride(const vector<int>&a,int k){int g=0;for(int i=k;i<(int)a.size();i++)g=std::gcd(g,llabs(a[i]-a[i-k]));return g;}
    int partitions(const vector<int>&a){int n=a.size(),ans=0;for(int k=1;k<=n;k++)if(n%k==0&&stride(a,k)!=1)ans++;return ans;}
    int from(const vector<int>&a,int x){int g=0;for(int y:a)g=std::gcd(g,llabs(y-x));return g;}
};
'''
add('tirick','同余差与GCD','GcdDifference',gcd,'所有数同余模m当且仅当m整除全部差；最大可行模或步长来自差值GCD。','stride/from O(n log A)时间/O(1)额外空间；partitions O(n*tau(n)*log A)时间。',
 [('stride(a,k)','相距k元素差值的GCD'),('partitions(a)','CF1920C的可行分段长度数'),('from(a,x)','所有点到x差值GCD')],
 ['GCD=0表示所有差为0，任意正模均可，不是无解。','CF1920C需要存在m≥2，因此g!=1，0也可行。','llabs(a-b)先相减可能溢出，本例限定差值在long long内。'],['tirick/总结.md'],[
 example('CF1920C','Partitioning the Array','https://codeforces.com/problemset/problem/1920/C','对n的每个因数k将数组分成长度k块，存在m≥2使各块对应位置模m相同则计数。','对应位置的相邻块差为a[i]-a[i-k]；它们的GCD不为1正是存在合法模数。','partitions(a)，枚举因数并调用stride。','O(n*tau(n)*log A)时间/O(n)空间。',r'''
 void solve(){int T;cin>>T;GcdDifference t;while(T--){int n;cin>>n;vector<int>a(n);for(int &x:a)cin>>x;cout<<t.partitions(a)<<'\n';}}
 '''),
 example('ABC109C','Skip','https://atcoder.jp/contests/abc109/tasks/abc109_c','从X出发每次左右移动固定D，访问所有给定城市，求最大的正D。','每个城市与X的差必须是D整数倍，最大D是这些差的GCD。','from(a,X)。','O(n log A)时间/O(n)空间（保存输入）。',r'''
 void solve(){int n,x;cin>>n>>x;vector<int>a(n);for(int &y:a)cin>>y;GcdDifference t;cout<<t.from(a,x)<<'\n';}
 ''')])
