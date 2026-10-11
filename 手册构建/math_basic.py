from common import *

exgcd=r'''
struct Exgcd {
    int exgcd(int a,int b,int &x,int &y){if(!b){x=1;y=0;return a;}int g=exgcd(b,a%b,y,x);y-=a/b*x;return g;}
    int norm(int a,int m){a%=m;return a<0?a+m:a;}
    int inverse(int a,int m){int x,y;int g=exgcd(norm(a,m),m,x,y);return g==1?norm(x,m):-1;}
    int linear(int a,int b,int m){assert(m>0);a=norm(a,m);b=norm(b,m);int x,y,g=exgcd(a,m,x,y);if(b%g)return -1;return norm((__int128)x*(b/g)%(m/g),m/g);}
};
'''
add('数论','扩展欧几里得','Exgcd',exgcd,'求Bezout系数、模逆元与线性同余最小非负解；模数为正。','O(log m)时间与递归空间。',[('exgcd(a,b,x,y)','非负a,b，返回gcd并使ax+by=gcd'),('inverse(a,m)','不存在返回-1'),('linear(a,b,m)','ax=b mod m，返回最小非负解或-1')],['取模后需归一化负余数。','系数递推与模数合并需评估溢出；乘积取模用__int128。'],['数论/exgcd.md'],[
example('P1082','同余方程','https://www.luogu.com.cn/problem/P1082','求ax=1 mod b的最小正整数解。','题目互质，扩展欧几里得系数给逆元。','inverse(a,b)，将0按正解约定改成b。','O(log b)时间与空间。',r'''void solve(){int a,b;cin>>a>>b;Exgcd ex;int x=ex.inverse(a,b);cout<<(x==0?b:x)<<'\n';}'''),
example('ABC186E','Throne','https://atcoder.jp/contests/abc186/tasks/abc186_e','从位置S每次走K，最少几次回到模N的0点。','K*x=-S mod N，gcd整除目标才有解。','每组linear(K,-S,N)。','O(T log N)时间、O(log N)空间。',r'''void solve(){int T;cin>>T;Exgcd ex;while(T--){int n,s,k;cin>>n>>s>>k;cout<<ex.linear(k,-s,n)<<'\n';}}''')])

crt=r'''
struct CRT {
    Exgcd ex;int ans=0,mod=1;
    void init(){ans=0;mod=1;}
    bool merge(int r,int m){assert(m>0);r=ex.norm(r,m);int x,y,g=ex.exgcd(mod,m,x,y);int delta=r-ans;if(delta%g)return false;int q=m/g;int k=ex.norm((__int128)(delta/g)*x%q,q);__int128 nm=(__int128)mod*q;assert(nm<=LLONG_MAX);ans=((__int128)ans+(__int128)mod*k)%nm;mod=nm;return true;}
};
'''
add('数论','中国剩余定理','CRT',exgcd+'\n'+crt,'逐式合并同余，兼容两两互质CRT与非互质扩展CRT。','n条同余约O(n log M)时间，额外O(log M)递归空间。',[('init()','初始x=0 mod1'),('merge(r,m)','合并x=r mod m，矛盾返回false'),('ans/mod','最小非负解与合并模数')],['最小公倍数须在long long内；中间乘积用__int128。','原CRT仅互质，本版merge增加gcd整除判断，保留exgcd解法。'],['数论/CRT（中国剩余定理）.cpp'],[
example('P1495','曹冲养猪','https://www.luogu.com.cn/problem/P1495','给若干除数和余数，求满足条件的最小猪数。','各同余两两互质，是普通CRT。','读入m,r后merge(r,m)，输出ans。','O(n log M)时间。',r'''void solve(){int n;cin>>n;CRT crt;while(n--){int m,r;cin>>m>>r;crt.merge(r,m);}cout<<crt.ans<<'\n';}'''),
example('P4777','扩展中国剩余定理','https://www.luogu.com.cn/problem/P4777','合并不保证互质的同余方程。','差值必须被gcd整除；新模数取lcm而非乘积。','逐式merge，按题面存在解约定输出ans。','O(n log M)时间。',r'''void solve(){int n;cin>>n;CRT crt;bool ok=true;while(n--){int m,r;cin>>m>>r;if(ok)ok=crt.merge(r,m);}cout<<(ok?crt.ans:-1)<<'\n';}''')])

comb=r'''
struct Comb {
    int mod;vector<int>fac,fnv;
    int powmod(int a,int b){int ans=1%mod;for(a%=mod;b;b>>=1,a=(__int128)a*a%mod)if(b&1)ans=(__int128)ans*a%mod;return ans;}
    void init(int n,int p=1000000007){assert(p>1&&n<p);mod=p;fac.assign(n+1,1);fnv.assign(n+1,1);for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;fnv[n]=powmod(fac[n],mod-2);for(int i=n;i>=1;i--)fnv[i-1]=fnv[i]*i%mod;}
    int binom(int n,int m){if(m<0||m>n)return 0;assert(n<(int)fac.size());return fac[n]*fnv[m]%mod*fnv[n-m]%mod;}
};
'''
add('数论','素数模组合数','Comb',comb,'阶乘与逆阶乘计算组合数；p为素数，预处理范围n<p。','预处理O(n+log p)，每问O(1)，空间O(n)。',[('init(n,p)','要求素数p且n<p'),('binom(n,m)','非法m返回0'),('powmod(a,b)','b非负')],['跨过模数后阶乘为0，不能求逆，应使用Lucas。','普通乘积在本例mod1e9+7内安全；powmod宽整数支持。'],['数论/组合数.cpp'],[
example('ABC034C','経路','https://atcoder.jp/contests/abc034/tasks/abc034_c','W乘H网格从左上向右下仅向右或下走，求路径数。','总步数W+H-2，选W-1步向右。','init(W+H-2)，binom(total,W-1)。','O(W+H)时间与空间。',r'''void solve(){int w,h;cin>>w>>h;Comb c;c.init(w+h-2);cout<<c.binom(w+h-2,w-1)<<'\n';}'''),
example('ABC145D','Knight','https://atcoder.jp/contests/abc145/tasks/abc145_d','每步(1,2)或(2,1)，求走到(X,Y)方案数。','求两种步数a=(2Y-X)/3、b=(2X-Y)/3，非负整数时组合数计排列。','检查整除与非负；init(a+b)，binom(a+b,a)。','O(X+Y)时间与空间上界。',r'''void solve(){int x,y;cin>>x>>y;int a=2*y-x,b=2*x-y;if(a<0||b<0||a%3||b%3){cout<<0<<'\n';return;}a/=3;b/=3;Comb c;c.init(a+b);cout<<c.binom(a+b,a)<<'\n';}''')])

lucas=r'''
struct Lucas {
    int p;Comb c;
    void init(int p_){p=p_;c.init(p-1,p);}
    int binom(int n,int m){if(m<0||m>n)return 0;int ans=1;while(n||m){ans=ans*c.binom(n%p,m%p)%p;n/=p;m/=p;}return ans;}
    int powmod(int a,int b){return c.powmod(a,b);}
};
'''
add('数论','Lucas定理','Lucas',comb+'\n'+lucas,'大n、小素数p的组合数模p；保留逐p进制位乘binom。','预处理O(p)，单问O(log_p n)，空间O(p)。',[('init(p)','素数p，按p实际分配'),('binom(n,m)','按p进制分解'),('powmod(a,b)','同模数快速幂')],['p必须素数；p很大时O(p)预处理会MLE/TLE。','n+m不得溢出long long。'],['数论/数论6_ACM板子.md','数论/数论6_课程复习.md'],[
example('P3807','Lucas定理','https://www.luogu.com.cn/problem/P3807','多组求C(n+m,n) mod p。','n可大于p，逐位Lucas降为小组合数。','每个p重新init，binom(n+m,n)。','每组O(p+log_p(n+m))时间、O(p)空间。',r'''void solve(){int T;cin>>T;while(T--){int n,m,p;cin>>n>>m>>p;Lucas c;c.init(p);cout<<c.binom(n+m,n)<<'\n';}}'''),
example('P1313','计算系数','https://www.luogu.com.cn/problem/P1313','求(ax+by)^k中x^n*y^m的系数模10007。','二项式定理给C(k,n)*a^n*b^m；Lucas负责组合数部分。','init(10007)，binom与powmod组合。','O(10007+log k)时间、O(10007)空间。',r'''void solve(){int a,b,k,n,m;cin>>a>>b>>k>>n>>m;Lucas c;c.init(10007);int ans=c.binom(k,n)*c.powmod(a,n)%10007*c.powmod(b,m)%10007;cout<<ans<<'\n';}''')])

add('数论','整除分块','FloorBlock',r'''
struct FloorBlock {
    template<class F>void run(int n,F calc){for(int l=1,r;l<=n;l=r+1){int q=n/l;r=n/q;calc(l,r,q);}}
    template<class F>void run(int n,int m,F calc){for(int l=1,r;l<=min(n,m);l=r+1){int a=n/l,b=m/l;r=min(n/a,m/b);calc(l,r,a,b);}}
    int count_divisors_sum(int n){int ans=0;run(n,[&](int l,int r,int q){ans+=(r-l+1)*q;});return ans;}
    __int128 divisor_sum(int n){__int128 ans=0;if(n<=0)return 0;run(n,[&](int l,int r,int q){ans+=(__int128)(l+r)*(r-l+1)/2*q;});return ans;}
    void print(__int128 x){if(x<0){cout<<'-';x=-x;}if(x>=10)print(x/10);cout<<char('0'+x%10);}
};
''','相同floor(n/i)的连续区间合并；同时支持两个商不变的分块。','单商/双商分块O(sqrt n+sqrt m)，额外O(1)空间。',[('run(n,calc)','回调(l,r,n/l)'),('run(n,m,calc)','同时商值不变'),('divisor_sum(n)','1..n的约数和总和，返回宽整数')],['右端点n/(n/l)，循环更新到r+1。','n接近LLONG_MAX时r+1溢出；本题使用n<=2e9。'],['数论/数论分块.cpp','数论/数论分块.md'],[
example('P1403','约数研究','https://www.luogu.com.cn/problem/P1403','求1..n每个数的约数个数之和。','交换求和得到sum floor(n/d)，按相同商合并。','count_divisors_sum(n)。','O(sqrt n)时间、O(1)空间。',r'''void solve(){int n;cin>>n;FloorBlock f;cout<<f.count_divisors_sum(n)<<'\n';}'''),
example('P2424','约数和','https://www.luogu.com.cn/problem/P2424','求区间[x,y]每个数的约数和之和。','前缀=Σ d*floor(n/d)，块内d的和用等差数列。','divisor_sum(y)-divisor_sum(x-1)，print宽整数。','O(sqrt y)时间、O(1)额外空间。',r'''void solve(){int x,y;cin>>x>>y;FloorBlock f;f.print(f.divisor_sum(y)-f.divisor_sum(x-1));cout<<'\n';}''')])
