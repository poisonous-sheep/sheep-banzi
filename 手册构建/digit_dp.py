from common import *
src=['dp/数位动态规划进阶_比赛板子.md']
digit=r'''
struct DigitDP {
    int S,initial,mod;vector<array<int,10>>go;vector<int>accept;
    DigitDP(int S=1,int mod=1000000007){init(S,mod);}
    void init(int s,int m){S=s;mod=m;initial=0;go.assign(S,{});for(auto &a:go)a.fill(-1);accept.assign(S,0);}
    int plus(int a,int b){return mod?(a+b)%mod:a+b;}
    int qur(const string&bound){vector<array<int,2>>dp(S),tmp(S);dp[initial][1]=1;
        for(char c:bound){for(auto &z:tmp)z={0,0};for(int s=0;s<S;s++)for(int tight=0;tight<2;tight++)if(dp[s][tight]){
            int hi=tight?c-'0':9;for(int d=0;d<=hi;d++){int v=go[s][d];if(v<0)continue;int nt=tight&&d==hi;tmp[v][nt]=plus(tmp[v][nt],dp[s][tight]);}}
            dp.swap(tmp);}
        int ans=0;for(int s=0;s<S;s++)if(accept[s])ans=plus(ans,plus(dp[s][0],dp[s][1]));return ans;
    }
    int qur(int x){return x<0?0:qur(to_string(x));}
    void windy(){init(11,0);for(int d=0;d<10;d++)go[0][d]=d?d+1:0;
        for(int last=0;last<10;last++)for(int d=0;d<10;d++)if(abs(last-d)>=2)go[last+1][d]=d+1;
        for(int s=1;s<=10;s++)accept[s]=1;}
    void digit_sum(int D,int p){init(D,p);for(int s=0;s<D;s++)for(int d=0;d<10;d++)go[s][d]=(s+d)%D;accept[0]=1;}
    // 状态0是尚无有效数位；其余编码(exist,last,inc)，inc=1..3。
    void increasing_three(){init(1+2*10*3,0);auto id=[](int e,int last,int inc){return 1+e*30+last*3+inc-1;};
        go[0][0]=0;for(int d=1;d<10;d++)go[0][d]=id(0,d,1);
        for(int e=0;e<2;e++)for(int last=0;last<10;last++)for(int inc=1;inc<=3;inc++){
            int s=id(e,last,inc);accept[s]=e;for(int d=0;d<10;d++){int k=d>last?min(3LL,inc+1):1;go[s][d]=id(e||k==3,d,k);}}
    }
};
'''
add('dp','数位DP与有限状态','DigitDP',digit,'把前缀必要信息编码为自动机状态，统一处理tight、前导零和区间前缀差；包含原数数三转移。','O(L*S*10)时间、O(S)滚动空间；L是位数，S是状态数。',
 [('init(S,mod)','mod=0为精确计数；自定义go与accept，-1为禁止转移'),('windy/digit_sum/increasing_three','配置相邻差、数位和、连续三位递增状态'),('qur(bound)','统计0..bound，包括是否接受0由状态配置决定')],
 ['数数三不把前导0当有效位；digit_sum接受0，例题需减去。','mod=0仅在总计数不会溢出long long时使用。','原框架的x+1与当前含上界API不同，区间统一qur(R)-qur(L-1)。'],src,[
 example('P2657','windy数','https://www.luogu.com.cn/problem/P2657','统计区间内相邻十进制数位之差至少2的正整数。','状态仅需前一有效数位，前导零有独立状态。','windy配置，然后qur(R)-qur(L-1)。','O(位数*110)时间、O(11)空间。',r'''
 void solve(){int L,R;cin>>L>>R;DigitDP t;t.windy();cout<<t.qur(R)-t.qur(L-1)<<'\n';}
 '''),
 example('DP_S','Digit Sum','https://atcoder.jp/contests/dp/tasks/dp_s','1..K中数位和能被D整除的数字个数，K可达10000位。','数位和只需模D的余数，滚动状态避免把巨大上界转整数。','digit_sum(D,1e9+7)，qur(K)后减去0。','O(|K|*D*10)时间、O(D)空间。',r'''
 void solve(){string K;int D;cin>>K>>D;DigitDP t;t.digit_sum(D,1000000007);cout<<(t.qur(K)-1+1000000007)%1000000007<<'\n';}
 ''')])

construct=r'''
struct DigitConstruct {
    string bound,ans;int k;array<int,10>vis{};
    bool dfs(int pos,bool larger,int cnt){if(pos==(int)bound.size())return true;
        int low=larger?0:bound[pos]-'0';if(!pos)low=max(1LL,low);
        for(int d=low;d<=9;d++){int nc=cnt+(vis[d]==0);if(nc>k)continue;vis[d]++;ans.push_back('0'+d);
            if(dfs(pos+1,larger||d>bound[pos]-'0',nc))return true;
            ans.pop_back();vis[d]--;}
        return false;
    }
    string at_most(string n,int k_){assert(1<=k_&&k_<=10);k=k_;bound=n;ans.clear();vis.fill(0);bool ok=dfs(0,false,0);assert(ok);return ans;}
    string at_least(string n,int k_){assert(1<=k_&&k_<=10);k=k_;
        for(int len=n.size();len<=max((int)n.size(),k);len++){
            bound=len==(int)n.size()?n:"1"+string(len-1,'0');ans.clear();
            vector<vector<array<int32_t,2>>>memo(len+1,vector<array<int32_t,2>>(1024,{-1,-1}));
            function<bool(int,int,bool)>can=[&](int pos,int mask,bool larger)->bool{
                if(pos==len)return __builtin_popcount((unsigned)mask)>=k;
                auto &res=memo[pos][mask][larger];if(res!=-1)return res!=0;
                int low=larger?0:bound[pos]-'0';if(!pos)low=max(1LL,low);
                for(int d=low;d<=9;d++)if(can(pos+1,mask|(1<<d),larger||d>bound[pos]-'0'))return res=1;return res=0;
            };
            if(!can(0,0,false))continue;int mask=0;bool larger=false;
            for(int pos=0;pos<len;pos++){int low=larger?0:bound[pos]-'0';if(!pos)low=max(1LL,low);
                for(int d=low;d<=9;d++)if(can(pos+1,mask|(1<<d),larger||d>bound[pos]-'0')){ans.push_back('0'+d);mask|=1<<d;larger|=d>bound[pos]-'0';break;}}
            return ans;
        }return "";
    }
};
'''
add('dp','数位构造与不同数位限制','DigitConstruct',construct,'按字典序DFS构造>=n的最小数；收录至多k种与至少k种数位两个原资料变体。','at_most O(L*10)；at_least最多O(L²*1024*10)时间、O(L*1024)空间。',
 [('at_most(n,k)','正整数n字符串，至多k种数位的最小>=n'),('at_least(n,k)','至少k种，返回字符串避免答案超过long long')],
 ['vis必须用计数整数，bool++/--错误且C++17禁止bool++。','至少k种不保证只增加一位，要一直尝试到max(原长度,k)。','至多k种的非tight合法前缀总可填已有数字，因此只在tight路径回溯。'],src,[
 example('CF1560F1','Nearest Beautiful Number easy','https://codeforces.com/contest/1560/problem/F1','k<=2时构造不小于n的最近美丽数。','按数位升序找第一个可完成方案就是最小合法数。','每组at_most(to_string(n),k)。','每组O(L*10)时间、O(L+10)空间。',r'''
 void solve(){int T;cin>>T;DigitConstruct t;while(T--){string n;int k;cin>>n>>k;cout<<t.at_most(n,k)<<'\n';}}
 '''),
 example('CF1560F2','Nearest Beautiful Number hard','https://codeforces.com/contest/1560/problem/F2','推广为k<=10的最小合法数。','同一剪枝仍成立，无需枚举10位数字集合全部1024种。','沿用at_most；这是原题的困难版，注明与F1为同题两档。','每组O(L*10)时间、O(L+10)空间。',r'''
 void solve(){int T;cin>>T;DigitConstruct t;while(T--){string n;int k;cin>>n>>k;cout<<t.at_most(n,k)<<'\n';}}
 ''')])

knap=r'''
struct DigitKnapsack {
    static constexpr int INF=4000000000000000000LL;
    vector<pair<int,int>>a;
    void init(){a.clear();}void add(int w,int v){assert(w>0);a.push_back({w,v});}
    int qur(int W){assert(W>=0);vector<vector<pair<int,int>>>item(63);int lim=0;
        for(auto[w,v]:a){int b=__builtin_ctzll((unsigned long long)w);int odd=w>>b;item[b].push_back({odd,v});lim+=odd;}
        lim=min(lim,W);vector<int>f(lim+1,-INF),g(lim+1,-INF);f[0]=0;
        for(int b=62;b>=0;b--){fill(g.begin(),g.end(),-INF);int bit=(W>>b)&1;
            for(int j=0;j<=lim;j++)if(f[j]>-INF)g[min(lim,2*j+bit)]=max(g[min(lim,2*j+bit)],f[j]);
            for(auto[w,v]:item[b])for(int j=0;j+w<=lim;j++)if(g[j+w]>-INF)g[j]=max(g[j],g[j+w]+v);
            f.swap(g);}
        return *max_element(f.begin(),f.end());
    }
};
'''
add('dp','数位背包','DigitKnapsack',knap,'体积拆成奇数*2^b，高位到低位下放剩余容量，用奇数部分总和截断状态。','O((63+n)*LIM)时间、O(n+LIM)空间；LIM=min(W,Σ奇数部分)。',
 [('init/add(w,v)','0/1物品，w>0'),('qur(W)','最大价值，允许不装满')],
 ['剩余容量语义的0/1转移必须j从小到大，反向会重复选同一物品。','只有奇数部分和小才适合大容量；普通采药例题展示可用但传统背包更直接。','不能对0重量调用ctzll；价值和须在long long内。'],src,[
 example('P3188','梦幻岛宝珠','https://www.luogu.com.cn/problem/P3188','重量很大但w=a*2^b且a<=10的0/1背包。','Σ奇数部分<=10n，使容量与2^30脱钩。','每组建立对象add全部物品，qur(W)，读到-1 -1终止。','O((63+n)*10n)时间、O(n)量级状态空间。',r'''
 void solve(){int n,W;while(cin>>n>>W&&n!=-1){DigitKnapsack t;while(n--){int w,v;cin>>w>>v;t.add(w,v);}cout<<t.qur(W)<<'\n';}}
 '''),
 example('P1048','采药','https://www.luogu.com.cn/problem/P1048','每株草药只能采一次，限定时间内最大收益。','普通0/1背包也可按体积幂分组；容量小会把LIM进一步截到W。','输入先T后M；逐个add(时间,价值)，qur(T)。','O((63+M)*min(T,Σodd(w)))时间、O(T+M)空间。',r'''
 void solve(){int T,M;cin>>T>>M;DigitKnapsack t;while(M--){int w,v;cin>>w>>v;t.add(w,v);}cout<<t.qur(T)<<'\n';}
 ''')])

pay=r'''
struct CarryDP {
    vector<int>a;map<pair<int,int>,int>memo;
    int dfs(int i,int x){if(i+1==(int)a.size())return x;auto key=make_pair(i,x);if(memo.count(key))return memo[key];
        int base=a[i+1]/a[i],r=x%base,q=x/base;
        int ans=r+dfs(i+1,q);if(r)ans=min(ans,base-r+dfs(i+1,q+1));return memo[key]=ans;}
    int qur(const vector<int>&coins,int x){a=coins;assert(!a.empty()&&a[0]==1);for(int i=1;i<(int)a.size();i++)assert(a[i]>a[i-1]&&a[i]%a[i-1]==0);memo.clear();return dfs(0,x);}
    int digits(string s,int base){int f=0,g=1;for(char c:s){int d=c-'0';int nf=min(f+d,g+base-d),ng=min(f+d+1,g+base-1-d);f=nf;g=ng;}return f;}
};
'''
add('dp','进位支付与有符号数位','CarryDP',pay,'每位选择直接支付或向更高币值进位并找零；二进制base=2就是原资料最少±2^k。','幂倍币制O(n)个实际金额状态、map查找O(log n)；固定进制O(L)时间/O(1)空间。',
 [('qur(coins,x)','coins[0]=1且每个是前一个的整数倍'),('digits(s,base)','s为高位到低位的0..9数字串，返回最少加减进制幂项数')],
 ['二进制由题目不限制最高幂时可以进到额外一位，末态允许一次大币找零。','原作业仅有口述伪代码，整理版明确了进位状态和收尾。','一般币制不满足整倍数时不能套此贪心转移。'],src,[
 example('ABC231E','Minimal payments','https://atcoder.jp/contests/abc231/tasks/abc231_e','币值组成整倍数链，买X元物品时支付和找零总币数最少。','低位余数只有向下支付和向上进位两种有效选择。','读升序币值调用qur(a,X)。','O(n log n)时间、O(n)状态空间。',r'''
 void solve(){int n,X;cin>>n>>X;vector<int>a(n);for(int &x:a)cin>>x;CarryDP t;cout<<t.qur(a,X)<<'\n';}
 '''),
 example('ABC155E','Payment','https://atcoder.jp/contests/abc155/tasks/abc155_e','币值为10的幂，巨大十进制金额最少支付及找零币数。','不能转long long，直接滚动“当前前缀付精确值/付前缀+1”的两个状态。','调用digits(N,10)。','O(|N|)时间、O(1)空间。',r'''
 void solve(){string N;cin>>N;CarryDP t;cout<<t.digits(N,10)<<'\n';}
 ''')])

weight=r'''
struct PopcountDP {
    int mod;PopcountDP(int mod=1000000007):mod(mod){}
    int weighted(string s,int c){int n=s.size();c%=mod;vector<int>pw(n+1,1);for(int i=1;i<=n;i++)pw[i]=pw[i-1]*(c+1)%mod;int pre=1,ans=0;
        for(int i=0;i<n;i++)if(s[i]=='1'){ans=(ans+pre*pw[n-i-1])%mod;pre=pre*c%mod;}return (ans+pre)%mod;}
    int masked(int n,int mask){int ans=0;for(int b=0;b<=60;b++)if((mask>>b)&1){__int128 bit=(__int128)1<<b,period=bit*2,len=(__int128)n+1;
        __int128 c=(len/period)*bit+max((__int128)0,len%period-bit);ans=(ans+c%mod)%mod;}return ans;}
    vector<int>distribution(int n){string s;do{s.push_back('0'+(n&1));n>>=1;}while(n);reverse(s.begin(),s.end());int L=s.size();
        vector<vector<int>>C(L+1,vector<int>(L+1));C[0][0]=1;for(int i=1;i<=L;i++){C[i][0]=C[i][i]=1;for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];}
        vector<int>ans(L+1);int ones=0;for(int i=0;i<L;i++)if(s[i]=='1'){for(int k=0;k<=L-i-1;k++)ans[ones+k]+=C[L-i-1][k];ones++;}ans[ones]++;return ans;}
    int powmod(int a,int b){int r=1;while(b){if(b&1)r=(__int128)r*a%mod;a=(__int128)a*a%mod;b>>=1;}return r;}
};
'''
add('dp','二进制位贡献与Popcount计数','PopcountDP',weight,'位独立贡献的乘法原理：原Meaningless Sequence加权和、按掩码统计1位次数、按popcount分类。','weighted O(L)时间/空间；masked O(log n)时间/O(1)空间；distribution O(log² n)时间/空间。',
 [('weighted(s,c)','二进制上界s，Σ0..N c^popcount(x)模mod'),('masked(n,mask)','Σ0..n popcount(x&mask)'),('distribution(n)','0..n按popcount计数，要求n<=1e18以保计数不溢出')],
 ['前导0在二进制统计中不改变popcount。','c=0时0^0按序列a0=1处理，weighted仍正确。','distribution输出精确指数，不对mod取模；指数模数也不能随意用答案模数。'],src,[
 example('Gym102832D','Meaningless Sequence','https://codeforces.com/gym/102832/problem/D','按原递推定义序列，求0..N的项和，N用二进制给出。','递推可化为c^popcount；首次低于上界后，剩余自由位贡献(1+c)^剩余位。','PopcountDP(1e9+7).weighted(N,c)。','O(|N|)时间与空间。',r'''
 void solve(){string N;int c;cin>>N>>c;PopcountDP t;cout<<t.weighted(N,c)<<'\n';}
 ''',tests=[dict(input='1000 3\n',output='67\n')]),
 example('ABC356D','Masked Popcount','https://atcoder.jp/contests/abc356/tasks/abc356_d','求0..N每个数与M按位与后的popcount总和。','拆成M中每个1位出现次数；该位0/1按周期交替。','PopcountDP(998244353).masked(N,M)。','O(log N)时间、O(1)空间。',r'''
 void solve(){int N,M;cin>>N>>M;PopcountDP t(998244353);cout<<t.masked(N,M)<<'\n';}
 '''),
 example('P4317','花神的数论题','https://www.luogu.com.cn/problem/P4317','将1..N每个数的二进制1的个数相乘，模10000007。','按popcount=k分组，每类贡献k^计数；需要精确计数作为指数。','distribution(N)，从k=1累乘powmod(k,cnt[k])。','O(log² N)时间/空间。',r'''
 void solve(){int N;cin>>N;PopcountDP t(10000007);auto cnt=t.distribution(N);int ans=1;for(int k=1;k<(int)cnt.size();k++)ans=(__int128)ans*t.powmod(k,cnt[k])%t.mod;cout<<ans<<'\n';}
 ''')])
