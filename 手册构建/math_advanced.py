from common import *

ex=source_struct('数论/整理版/扩展欧几里得/模板.cpp','Exgcd')
exlucas=r'''
struct ExLucas {
    struct node{int p,pe;vector<int>fac;};int mod;vector<node>parts;Exgcd ex;
    int powmod(int a,int b,int m){int ans=1%m;for(a%=m;b;b>>=1,a=(__int128)a*a%m)if(b&1)ans=(__int128)ans*a%m;return ans;}
    void init(int m){assert(m>=1);mod=m;parts.clear();int q=m;for(int p=2;p<=q/p;p++)if(q%p==0){int pe=1;while(q%p==0){q/=p;pe*=p;}parts.push_back({p,pe,{}});}if(q>1)parts.push_back({q,q,{}});for(auto&v:parts){assert(v.pe<=2000000);v.fac.assign(v.pe+1,1);for(int i=1;i<=v.pe;i++)v.fac[i]=v.fac[i-1]*(i%v.p?i:1)%v.pe;}}
    int valuation(int n,int p){int ans=0;while(n){n/=p;ans+=n;}return ans;}
    int fact(int n,const node&v){if(!n)return 1;return powmod(v.fac[v.pe],n/v.pe,v.pe)*v.fac[n%v.pe]%v.pe*fact(n/v.p,v)%v.pe;}
    int binom(int n,int m){if(m<0||m>n||mod==1)return 0;int ans=0;for(auto&v:parts){int exp=valuation(n,v.p)-valuation(m,v.p)-valuation(n-m,v.p);int a=fact(n,v),b=fact(m,v)*fact(n-m,v)%v.pe;int val=a*ex.inverse(b,v.pe)%v.pe*powmod(v.p,exp,v.pe)%v.pe;int M=mod/v.pe;ans=(ans+(__int128)val*M*ex.inverse(M,v.pe))%mod;}return ans;}
};
'''
add('数论','扩展Lucas','ExLucas',ex+'\n'+exlucas,'合数模组合数，按质数幂去除阶乘质因子后CRT；单质数幂<=2e6。','预处理O(sqrt M+Σp^e)，每问O(Σlog_p n*log(p^e))，空间O(Σp^e)。',[('init(M)','允许M=1；分解并预处理非p因子阶乘'),('binom(n,m)','合数模组合数')],['阶乘单位部分才能求逆；质因子指数单独乘p^exp。','大质数幂不能直接开fac；明确O(p^e)限制。','重建时parts清空，修复固定大数组与负指数处理风险。'],['数论/数论6_ACM板子.md','数论/数论6_课程复习.md'],[
example('P4720','扩展Lucas','https://www.luogu.com.cn/problem/P4720','求C(n,m)模给定合数p。','普通逆阶乘不适用；分解为质数幂计算后CRT。','init(p)，binom(n,m)。','按模板复杂度。',r'''void solve(){int n,m,p;cin>>n>>m>>p;ExLucas c;c.init(p);cout<<c.binom(n,m)<<'\n';}'''),
example('P2183','礼物','https://www.luogu.com.cn/problem/P2183','n件不同礼物分给m人，每人指定件数，模合数p求方案。','多项式系数可写成依次选人的组合数连乘；同一个模数复用预处理。','先判断需求总和<=n；逐人binom(remaining,wi)后扣减。','预处理一次，加m次组合数查询；空间Σp^e。',r'''void solve(){int p,n,m;cin>>p>>n>>m;vector<int>w(m);int sum=0;for(int&x:w){cin>>x;sum+=x;}if(sum>n){cout<<"Impossible\n";return;}ExLucas c;c.init(p);int ans=1%p;for(int x:w){ans=(__int128)ans*c.binom(n,x)%p;n-=x;}cout<<ans<<'\n';}''')])

tower=r'''
struct PowerTower {
    vector<int>a;map<int,int>phi_cache;
    int phi(int m){if(phi_cache.count(m))return phi_cache[m];int ans=m,q=m;for(int p=2;p<=q/p;p++)if(q%p==0){ans=ans/p*(p-1);while(q%p==0)q/=p;}if(q>1)ans=ans/q*(q-1);return phi_cache[m]=ans;}
    int powmod(int x,int e,int m){int ans=1%m;for(x%=m;e;e>>=1,x=(__int128)x*x%m)if(e&1)ans=(__int128)ans*x%m;return ans;}
    int calc(int m){if(m==1)return 0;int p=phi(m);return powmod(2,calc(p)+p,m);}
    void init(const vector<int>&v){a=v;for(int i=1;i<(int)a.size();i++)assert(a[i]>=1);}
    // 返回min(真实幂塔,limit)，只用于阈值判断；避免用已取模指数判断大小。
    int cap(int l,int r,int limit){if(limit<=1)return limit;if(l==r)return min(a[l],limit);if(a[l]==1)return 1;int need=0;__int128 val=1;while(val<limit){val*=a[l];need++;}int e=cap(l+1,r,need);val=1;while(e--&&val<limit)val*=a[l];return val>=limit?limit:(int)val;}
    int qur(int l,int r,int m){if(m==1)return 0;if(l==r)return a[l]%m;int p=phi(m);int e=qur(l+1,r,p);if(cap(l+1,r,p)>=p)e+=p;return powmod(a[l],e,m);}
};
'''
add('数论','扩展欧拉与指数塔','PowerTower',tower,'固定2的无限幂塔，以及正整数数组区间幂塔模m；通过phi链与真实阈值判定。','phi试除按链各层求和；缓存后每问按O(log m)级链深递归及截断幂比较，空间为链深。',[('calc(m)','无限2指数塔'),('init(a)','1-based且a[i]>=1'),('qur(l,r,m)','右结合a[l]^(a[l+1]^...)'),('cap(l,r,limit)','判断真实值是否达到limit')],['非互质时只有指数足够大才加phi，不能无条件加。','不要从取模后的指数推断真实大小；cap独立判断。','本版约定m<=1e9，正底数，0^0不属于适用范围。'],['数论/数论7_ACM板子.md','数论/数论7_课程复习.md'],[
example('P4139','上帝与集合的正确用法','https://www.luogu.com.cn/problem/P4139','多组无限2幂塔模p。','固定2的无限塔沿phi链递归，指数足够大可加phi。','每组calc(p)，缓存phi可复用。','各phi链试除与快速幂之和。',r'''void solve(){int T;cin>>T;PowerTower tr;while(T--){int p;cin>>p;cout<<tr.calc(p)<<'\n';}}''',tests=[['3\n2\n3\n6\n','0 1 4']]),
example('CF906D','Power Tower','https://codeforces.com/problemset/problem/906/D','数组上给区间，求该区间指数塔模固定m。','区间长度可大，但phi链很短；底数为1时cap直接结束。','init(a)，每问qur(l,r,m)。','预处理phi链，查询沿短链与阈值递归；空间O(n+log m)。',r'''void solve(){int n,m;cin>>n>>m;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];PowerTower tr;tr.init(a);int q;cin>>q;while(q--){int l,r;cin>>l>>r;cout<<tr.qur(l,r,m)<<'\n';}}''')])

root=r'''
struct PrimitiveRoot {
    int phi(int n){int ans=n;for(int p=2;p<=n/p;p++)if(n%p==0){ans=ans/p*(p-1);while(n%p==0)n/=p;}if(n>1)ans=ans/n*(n-1);return ans;}
    int powmod(int a,int b,int m){int ans=1%m;for(a%=m;b;b>>=1,a=(__int128)a*a%m)if(b&1)ans=(__int128)ans*a%m;return ans;}
    bool exists(int m){if(m==2||m==4)return true;if(m<2)return false;if(m%2==0)m/=2;if(m%2==0)return false;int p=0;for(int i=3;i<=m/i;i+=2)if(m%i==0){p=i;break;}if(!p)p=m;while(m%p==0)m/=p;return m==1;}
    int find(int m){if(!exists(m))return -1;int ph=phi(m),q=ph;vector<int>pf;for(int p=2;p<=q/p;p++)if(q%p==0){pf.push_back(p);while(q%p==0)q/=p;}if(q>1)pf.push_back(q);for(int g=1;g<m;g++){if(gcd(g,m)!=1)continue;bool ok=true;for(int p:pf)if(powmod(g,ph/p,m)==1){ok=false;break;}if(ok)return g;}return -1;}
    vector<int>all(int m){int g=find(m);if(g==-1)return {};int ph=phi(m),x=1;vector<int>ans;for(int k=1;k<=ph;k++){x=(__int128)x*g%m;if(gcd(k,ph)==1)ans.push_back(x);}sort(ans.begin(),ans.end());return ans;}
};
'''
add('数论','原根','PrimitiveRoot',root,'寻找最小原根并列举全部原根；从原素数版扩展至2、4、p^k、2p^k。','试除O(sqrt m)，找根O(G*omega(phi)*log m)，枚举O(phi(m)log phi(m))及排序，空间O(phi(m))。',[('find(m)','不存在返回-1'),('all(m)','升序全部原根'),('exists(m)','按原根存在条件判断')],['非所有模数都有原根。','原根个数是phi(phi(m))；枚举需数据规模允许。'],['数论/数论8_ACM板子.md','数论/数论8_课程复习.md'],[
example('P6091','原根','https://www.luogu.com.cn/problem/P6091','求全部原根数量，并输出排序后每第d个原根。','求一原根后，互质指数生成全部原根。','all(n)，输出size与下标d-1,2d-1,...。','按模板找根与枚举复杂度。',r'''void solve(){int T;cin>>T;PrimitiveRoot p;while(T--){int n,d;cin>>n>>d;auto a=p.all(n);cout<<a.size()<<'\n';for(int i=d-1;i<(int)a.size();i+=d)cout<<a[i]<<' ';cout<<'\n';}}'''),
example('CF284A','Cows and Primitive Roots','https://codeforces.com/problemset/problem/284/A','素数p下有多少个原根。','枚举所有原根并计数；p小，能展示判定与构造接口。','all(p).size()；也可用phi(phi(p))验证数量。','O(p log p+找根耗时)时间、O(p)空间。',r'''void solve(){int p;cin>>p;PrimitiveRoot g;cout<<g.all(p).size()<<'\n';}''')])

bsgs=r'''
struct BSGS {
    Exgcd ex;
    int powmod(int a,int b,int m){int ans=1%m;for(a%=m;b;b>>=1,a=(__int128)a*a%m)if(b&1)ans=(__int128)ans*a%m;return ans;}
    int unit(int a,int b,int m){if(m==1)return 0;int t=sqrtl((long double)m)+1;map<int,int>hs;int v=1%m;for(int j=0;j<t;j++){if(!hs.count(v))hs[v]=j;v=(__int128)v*a%m;}int factor=ex.inverse(powmod(a,t,m),m),cur=b;for(int q=0;q<=t;q++){if(hs.count(cur))return q*t+hs[cur];cur=(__int128)cur*factor%m;}return -1;}
    int solve(int a,int b,int m){assert(m>0);a=ex.norm(a,m);b=ex.norm(b,m);if(m==1)return 0;int k=1%m,count=0;for(int g=gcd(a,m);g>1;g=gcd(a,m)){if(b==k)return count;if(b%g)return -1;b/=g;m/=g;k=(__int128)k*(a/g)%m;count++;}int x=unit(a%m,(__int128)b*ex.inverse(k,m)%m,m);return x<0?-1:x+count;}
};
'''
add('数论','BSGS离散对数','BSGS',ex+'\n'+bsgs,'求a^x=b mod m的最小非负x；保留map大步小步思路，并扩展非互质约除。','O(sqrt m log m)时间、O(sqrt m)空间。',[('solve(a,b,m)','最小非负解；不存在-1'),('unit(a,b,m)','内部仅用于gcd(a,m)=1')],['先处理x=0与m=1；普通BSGS不能裸用于非互质。','重复baby值保留最小指数以保证最小解。'],['数论/数论8_ACM板子.md','数论/数论8_课程复习.md'],[
example('P3846','可爱的质数','https://www.luogu.com.cn/problem/P3846','输入p,b,n，求b^x=n mod p。','素数模下通常互质，直接用BSGS。','solve(b,n,p)，无解输出no solution。','O(sqrt p log p)时间、O(sqrt p)空间。',r'''void solve(){int p,b,n;cin>>p>>b>>n;BSGS g;int ans=g.solve(b,n,p);if(ans<0)cout<<"no solution\n";else cout<<ans<<'\n';}'''),
example('P2485','计算器','https://www.luogu.com.cn/problem/P2485','三类操作分别为快速幂、线性同余、离散对数。','对模式3用BSGS；其他模式调用板子内的powmod和Exgcd。','按k选择powmod、ex.linear、solve；无解按题面字符串输出。','模式3每组O(sqrt p log p)，其他O(log p)。',r'''void solve(){int T,k;cin>>T>>k;BSGS g;while(T--){int y,z,p;cin>>y>>z>>p;int ans=k==1?g.powmod(y,z,p):k==2?g.ex.linear(y,z,p):g.solve(y,z,p);if(ans<0)cout<<"Orz, I cannot find x!\n";else cout<<ans<<'\n';}}''')])
