from common import *
mob=r'''
struct Mobius {
    int n;vector<int>p,pr,mu,smu,phi;
    Mobius(int n=0){init(n);}
    void init(int n_){n=n_;p.assign(n+1,0);mu=smu=phi=p;pr.clear();if(n)mu[1]=phi[1]=1;
        for(int i=2;i<=n;i++){if(!p[i])p[i]=i,pr.push_back(i),mu[i]=-1,phi[i]=i-1;
            for(int x:pr){if(x>n/i)break;p[i*x]=x;if(i%x==0){phi[i*x]=phi[i]*x;break;}mu[i*x]=-mu[i];phi[i*x]=phi[i]*(x-1);}}
        for(int i=1;i<=n;i++)smu[i]=smu[i-1]+mu[i];}
    int coprime(int a,int b){if(a>b)swap(a,b);assert(a<=n);int ans=0;
        for(int l=1,r;l<=a;l=r+1){int x=a/l,y=b/l;r=min(a/x,b/y);ans+=(smu[r]-smu[l-1])*x*y;}return ans;}
    vector<uint32_t> invert32(const vector<uint32_t>&f){
        assert((int)f.size()==n+1);vector<uint32_t>g(n+1);
        for(int d=1;d<=n;d++)for(int k=1;k<=n/d;k++)g[d*k]+=f[d]*(uint32_t)mu[k];return g;
    }
};
'''
add('数论','莫比乌斯反演与线性筛','Mobius',mob,'线性筛mu与phi；利用互质指示函数和整除分块统计数对；保留原稿模2^32反演接口。','筛O(N)时间/空间；coprime O(sqrt(min(a,b)))；invert32 O(N log N)。',
 [('init(N)','筛1..N的最小素因子、mu、phi及mu前缀和'),('coprime(a,b)','1<=x<=a、1<=y<=b且gcd=1的有序数对'),('invert32(f)','已知f(n)=Σg(d)，在模2^32环内反演g')],
 ['mu用有符号整数，原rng题unsigned运算用uint32_t保留32位溢出语义。','数对结果要求a*b不超long long；任一边为0返回0。','分块取两个商共同右端点。'],['数论/求mo函数.cpp','数论/数论9_ACM板子.md'],[
 example('P2522','ZAP-Queries','https://www.luogu.com.cn/problem/P2522','统计1..a和1..b中gcd(x,y)=d的数对。','同时除以d，转为互质矩形计数。','离线读多组以求最大min(a/d,b/d)，init后coprime。','O(N+T sqrt N)时间、O(N+T)空间。',r'''
 void solve(){int T;cin>>T;vector<array<int,3>>q(T);int N=0;for(auto &z:q){cin>>z[0]>>z[1]>>z[2];N=max(N,min(z[0]/z[2],z[1]/z[2]));}Mobius t(N);for(auto z:q)cout<<t.coprime(z[0]/z[2],z[1]/z[2])<<'\n';}
 '''),
 example('P3455','Problem b','https://www.luogu.com.cn/problem/P3455','统计两个闭区间内gcd=k的数对。','将区间容斥为四个前缀矩形，再缩放为互质计数。','读取a,b,c,d,k，计算F(b,d)-F(a-1,d)-F(b,c-1)+F(a-1,c-1)。','O(N+T sqrt N)时间、O(N+T)空间。',r'''
 void solve(){int T;cin>>T;vector<array<int,5>>q(T);int N=0;for(auto &z:q){for(int &x:z)cin>>x;N=max(N,min(z[1]/z[4],z[3]/z[4]));}Mobius t(N);
 for(auto z:q){auto F=[&](int a,int b){return t.coprime(a/z[4],b/z[4]);};cout<<F(z[1],z[3])-F(z[0]-1,z[3])-F(z[1],z[2]-1)+F(z[0]-1,z[2]-1)<<'\n';}}
 ''')])

sub=mob+r'''
struct CoprimeSet {
    int n,mod;vector<int>cnt,pw,exact;Mobius sieve;
    CoprimeSet(const vector<int>&a,int mod_=1000000007){init(a,mod_);}
    void init(const vector<int>&a,int mod_=1000000007){mod=mod_;n=a.empty()?0:*max_element(a.begin(),a.end());sieve.init(n);
        vector<int>freq(n+1);for(int x:a){assert(x>0);freq[x]++;}cnt.assign(n+1,0);
        for(int d=1;d<=n;d++)for(int j=d;j<=n;j+=d)cnt[d]+=freq[j];
        pw.assign(a.size()+1,1);for(int i=1;i<(int)pw.size();i++)pw[i]=pw[i-1]*2%mod;}
    int qur(){int ans=0;for(int d=1;d<=n;d++)ans=(ans+sieve.mu[d]*(pw[cnt[d]]-1))%mod;return (ans+mod)%mod;}
    int weighted(){exact.assign(n+1,0);int ans=0;
        for(int d=n;d>=1;d--){int c=cnt[d];exact[d]=c?c*pw[c-1]%mod:0;
            for(int j=d+d;j<=n;j+=d)exact[d]=(exact[d]-exact[j]+mod)%mod;
            if(d>1)ans=(ans+d*exact[d])%mod;}return ans;}
};
'''
add('数论','互质集合与GCD分类计数','CoprimeSet',sub,'统计非空下标子集的gcd；按倍数统计与反演恢复恰好gcd=d的子集权重。','O(V log V+n)时间、O(V+n)空间，V=max(a)。',
 [('init(a,mod)','a是无前导占位的正整数数组，预处理倍数个数和2幂'),('qur()','gcd=1的非空下标子集数'),('weighted()','gcd>1子集的size*gcd之和')],
 ['不同下标视为不同选择，重复值不可去重。','减法取模需归一化；空集必须扣掉。','不是两两互质，而是整个子集gcd为1。'],['数论/数论10_ACM板子.md'],[
 example('CF803F','Coprime Subsequences','https://codeforces.com/contest/803/problem/F','求gcd为1的非空子序列数。','选择下标后顺序唯一，因此子序列数等于下标子集数。每个d的候选有2^cnt[d]-1个。','读数组构造CoprimeSet，输出qur。','O(V log V+n)时间、O(V+n)空间。',r'''
 void solve(){int n;cin>>n;vector<int>a(n);for(int &x:a)cin>>x;CoprimeSet t(a);cout<<t.qur()<<'\n';}
 ''',tests=[dict(input='3\n1 2 3\n',output='5\n'),dict(input='4\n1 1 1 1\n',output='15\n')]),
 example('CF839D','Winter is here','https://codeforces.com/contest/839/problem/D','累加gcd>1子序列的长度乘gcd。','含c个候选的所有子集长度和为c*2^(c-1)；从大到小减掉更大gcd的贡献。','构造CoprimeSet后调用weighted，精确类别存exact。','O(V log V+n)时间、O(V+n)空间。',r'''
 void solve(){int n;cin>>n;vector<int>a(n);for(int &x:a)cin>>x;CoprimeSet t(a);cout<<t.weighted()<<'\n';}
 ''',tests=[dict(input='3\n3 3 1\n',output='12\n'),dict(input='4\n2 3 4 6\n',output='39\n')])])

lrow=mob+r'''
struct LCMSumRow {
    vector<int>f;
    void init(int n){Mobius t(n);f.assign(n+1,0);
        for(int d=1;d<=n;d++)for(int j=d;j<=n;j+=d)f[j]+=d*t.phi[d];}
    __int128 qur(int n){assert(1<=n&&n<(int)f.size());return (__int128)n*(f[n]+1)/2;}
    __int128 calc(int n){
        vector<pair<int,int>> fac;int x=n;for(int p=2;p<=x/p;p++)if(x%p==0){int e=0;while(x%p==0)x/=p,e++;fac.push_back({p,e});}if(x>1)fac.push_back({x,1});
        __int128 s=1;for(auto[p,e]:fac){__int128 z=1,pow=1;for(int k=1;k<=e;k++){pow*=p;z+=pow*(pow-pow/p);}s*=z;}return (__int128)n*(s+1)/2;
    }
};
void print128(__int128 x){if(!x){cout<<0;return;}string s;while(x)s.push_back('0'+x%10),x/=10;reverse(s.begin(),s.end());cout<<s;}
'''
add('数论','LCM单行求和','LCMSumRow',lrow,'求Σ(1<=i<=n)lcm(i,n)=n*(1+Σ(d|n)d*phi(d))/2。保留课堂按约数累加思路。','批量init O(N log N)、O(N)空间；单点calc试除O(sqrt n)、O(log n)空间。',
 [('init(N)/qur(n)','批量筛到N，查询精确128位结果'),('calc(n)','大n先因式分解，利用积性乘积计算')],
 ['整数式必须先保留精确分子再除2，不能在偶数模数下直接乘逆元。','返回__int128，n<=1e9时可用此范围；打印使用print128。'],['数论/数论10_课程复习.md'],[
 example('SP5971','LCMSUM - LCM Sum','https://www.luogu.com.cn/problem/SP5971','多组n求lcm(1,n)+...+lcm(n,n)。','同一筛可预处理全部约数和，适合n<=1e6的多次查询。','读全部n，init(max n)，每次qur并print128。','O(N log N+T)时间、O(N+T)空间。',r'''
 void solve(){int T;cin>>T;vector<int>a(T);for(int &x:a)cin>>x;LCMSumRow t;t.init(*max_element(a.begin(),a.end()));for(int x:a){print128(t.qur(x));cout<<'\n';}}
 ''',tests=[dict(input='3\n1\n2\n5\n',output='1\n4\n55\n')]),
 example('P1891','疯狂LCM','https://www.luogu.com.cn/problem/P1891','最多300000次查询n≤1000000的单行LCM和。','与SP5971使用同一约数和预处理；本题大量查询不可逐次试除，必须一次筛到最大n。','读全部n，init(max n)，依次qur并精确输出。','O(N log N+T)时间、O(N+T)空间。',r'''
 void solve(){int T;cin>>T;vector<int>a(T);for(int &x:a)cin>>x;LCMSumRow t;t.init(*max_element(a.begin(),a.end()));for(int x:a){print128(t.qur(x));cout<<'\n';}}
 ''')])

lrect=r'''
struct LCMSum {
    int n,mod;vector<int>h,pre,p,pr;
    LCMSum(int n=0,int mod=20101009){init(n,mod);}
    int norm(int x){return (x%mod+mod)%mod;}
    int mul(int a,int b){return (__int128)a*b%mod;}
    int S(int x){int a=x,b=x+1;if(a%2==0)a/=2;else b/=2;return mul(a%mod,b%mod);}
    void init(int n_,int m){n=n_;mod=m;assert(mod>0);h.assign(n+1,0);pre=p=h;pr.clear();if(n)h[1]=1%mod;
        for(int i=2;i<=n;i++){if(!p[i])p[i]=i,pr.push_back(i),h[i]=norm(i*(1-i));
            for(int x:pr){if(x>n/i)break;p[i*x]=x;if(i%x==0){h[i*x]=mul(h[i],x);break;}h[i*x]=mul(h[i],norm(x*(1-x)));}}
        for(int i=1;i<=n;i++)pre[i]=(pre[i-1]+h[i])%mod;}
    int qur(int a,int b){if(a>b)swap(a,b);assert(a<=n);int ans=0;
        for(int l=1,r;l<=a;l=r+1){int x=a/l,y=b/l;r=min(a/x,b/y);ans=(ans+mul(norm(pre[r]-pre[l-1]),mul(S(x),S(y))))%mod;}return ans;}
    int pairs(const vector<int>&a){vector<int>s(n+1),freq(n+1);int diag=0;for(int x:a){assert(1<=x&&x<=n);freq[x]++;diag=(diag+x)%mod;}
        for(int d=1;d<=n;d++)for(int x=d;x<=n;x+=d)s[d]=(s[d]+mul(freq[x],x/d))%mod;
        int ans=0;for(int d=1;d<=n;d++)ans=(ans+mul(h[d],mul(s[d],s[d])))%mod;
        assert(mod&1);return mul(norm(ans-diag),(mod+1)/2);
    }
};
'''
add('数论','LCM矩形与集合求和','LCMSum',lrect,'用h(t)=t*Π(p|t)(1-p)整理莫比乌斯反演；矩形中用三角数，集合中用整倍数权重和。','筛O(V)；矩形查询O(sqrt min(a,b))；集合O(V log V+n)；空间O(V+n)。',
 [('init(V,mod)','线性筛积性h及前缀和'),('qur(a,b)','Σ1<=i<=a,1<=j<=b lcm(i,j)模mod'),('pairs(a)','数组无序下标对i<j的LCM和；mod须为奇数')],
 ['h的负数需要归一化；课堂模2^60变体不能直接用有符号溢出替代。','三角数先整数除2再取模，支持偶数mod的矩形查询。','pairs扣去对角再乘2的逆元，所以限定奇数mod。'],['数论/数论10_课程复习.md'],[
 example('P1829','Crash的数字表格','https://www.luogu.com.cn/problem/P1829','求n乘m表格内全部lcm(i,j)，模20101009。','反演后仅需Σh(t)S(n/t)S(m/t)，两个商相同的区间可合并。','init(min(n,m),20101009)，输出qur(n,m)。','O(min(n,m))预处理，O(sqrt min(n,m))查询，O(min(n,m))空间。',r'''
 void solve(){int n,m;cin>>n>>m;LCMSum t(min(n,m),20101009);cout<<t.qur(n,m)<<'\n';}
 '''),
 example('AGC038C','LCMs','https://atcoder.jp/contests/agc038/tasks/agc038_c','求数组中所有i<j的lcm(ai,aj)之和，模998244353。','倍数元素的单位权重和S(d)替代矩形三角数；同一h反演后用平方统计有序对，再扣对角除2。','init(max a,998244353)，pairs(a)。','O(V log V+n)时间，O(V+n)空间。',r'''
 void solve(){int n;cin>>n;vector<int>a(n);for(int &x:a)cin>>x;LCMSum t(*max_element(a.begin(),a.end()),998244353);cout<<t.pairs(a)<<'\n';}
 ''')])

comb=source_struct('数论/整理版/素数模组合数/模板.cpp','Comb')
cat=comb+r'''
struct Catalan {
    int exact(int n){assert(0<=n&&n<=35);__int128 c=1;for(int i=1;i<=n;i++)c=c*2*(2*i-1)/(i+1);return c;}
    int ballot(int n,int m,int mod){if(n<m)return 0;Comb t;t.init(n+m,mod);return (t.binom(n+m,m)-t.binom(n+m,m-1)+mod)%mod;}
};
'''
add('数论','卡特兰数与反射原理','Catalan',cat,'计数栈出入、合法括号与不越界格路径；精确递推与反射法的组合数差。','exact O(n)时间/O(1)空间；ballot O(n+m)时间/空间。',
 [('exact(n)','0..35的卡特兰数，返回long long'),('ballot(n,m,p)','n个上步m个下步且所有前缀不低于0；p为素数且n+m<p')],
 ['Catalan(0)=1。35之后精确结果可能超long long。','组合数差公式不要求除n+1，可避免该分母模p为0的问题；本实现仍要求总长度<p。'],['卡特兰数复习资料.md'],[
 example('P1044','栈','https://www.luogu.com.cn/problem/P1044','顺序入栈的n个数有多少种合法出栈序列。','入栈和出栈分别是上步和下步，任意前缀不能出栈多于入栈。','调用exact(n)。','O(n)时间、O(1)空间。',r'''
 void solve(){int n;cin>>n;Catalan t;cout<<t.exact(n)<<'\n';}
 '''),
 example('P1641','生成字符串','https://www.luogu.com.cn/problem/P1641','由n个A和m个B组成字符串，每个前缀A数不少于B数。','将A/B映射上/下步；总数减去第一次越界后反射的非法路径数。','ballot(n,m,20100403)，不等数量也可使用。','O(n+m)时间与空间。',r'''
 void solve(){int n,m;cin>>n>>m;Catalan t;cout<<t.ballot(n,m,20100403)<<'\n';}
 ''')])
