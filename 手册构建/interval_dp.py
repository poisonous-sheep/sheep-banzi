from common import *
src=['dp/区间动态规划进阶_比赛板子.md']
stone=r'''
struct StoneMerge {
    static constexpr int INF=4000000000000000000LL;
    int binary(const vector<int>&a,bool circle=false,bool maximum=false){
        int n=a.size(),N=circle?2*n:n;vector<int>s(N+1);for(int i=1;i<=N;i++)s[i]=s[i-1]+a[(i-1)%n];
        vector<vector<int>>dp(N+2,vector<int>(N+2));
        for(int len=2;len<=n;len++)for(int l=1;l+len-1<=N;l++){int r=l+len-1;dp[l][r]=maximum?-INF:INF;
            for(int k=l;k<r;k++){int val=dp[l][k]+dp[k+1][r]+s[r]-s[l-1];if(maximum)dp[l][r]=max(dp[l][r],val);else dp[l][r]=min(dp[l][r],val);}}
        int ans=maximum?-INF:INF;for(int l=1;l<=(circle?n:1);l++)if(maximum)ans=max(ans,dp[l][l+n-1]);else ans=min(ans,dp[l][l+n-1]);return ans;
    }
    int arity(const vector<int>&a,int L,int R){assert(2<=L&&L<=R);int n=a.size();vector<int>s(n+1);for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i-1];
        vector<vector<vector<int>>>dp(n+2,vector<vector<int>>(n+2,vector<int>(n+1,INF)));
        for(int i=1;i<=n;i++)dp[i][i][1]=0;
        for(int len=2;len<=n;len++)for(int l=1;l+len-1<=n;l++){int r=l+len-1;
            for(int k=2;k<=min(R,len);k++)for(int mid=l;mid<r;mid++)if(dp[l][mid][1]<INF&&dp[mid+1][r][k-1]<INF)dp[l][r][k]=min(dp[l][r][k],dp[l][mid][1]+dp[mid+1][r][k-1]);
            for(int k=L;k<=min(R,len);k++)if(dp[l][r][k]<INF)dp[l][r][1]=min(dp[l][r][1],dp[l][r][k]+s[r]-s[l-1]);}
        return n?dp[1][n][1]:0;
    }
};
'''
add('dp','区间石子合并','StoneMerge',stone,'相邻堆合并的区间DP；保留一次合并L..R堆三维状态，并提供二元合并与环形最大/最小版本。','binary O(n³)时间/O(n²)空间；arity O(n³R)时间/O(n³)空间，n<=100。',
 [('binary(a,circle,maximum)','a无1基占位；circle复制一圈，maximum求最大费用'),('arity(a,L,R)','每次合并L..R堆，返回INF表示无法合成一堆')],
 ['单堆费用0；三维k不能超过区间长度。','DP_N n=400必须用binary，不可使用O(n⁴)的课堂多元版本。','INF状态不要直接相加；费用和须小于INF。'],src,[
 example('DP_N','Slimes','https://atcoder.jp/contests/dp/tasks/dp_n','相邻两堆合并，总代价最小。','最后一次合并将区间分为左右两堆，枚举最后断点。','读a后binary(a)。','O(n³)时间、O(n²)空间。',r'''
 void solve(){int n;cin>>n;vector<int>a(n);for(int &x:a)cin>>x;StoneMerge t;cout<<t.binary(a)<<'\n';}
 ''',tests=[dict(input='4\n10 20 30 40\n',output='190\n'),dict(input='3\n1000000000 1000000000 1000000000\n',output='5000000000\n')]),
 example('P1880','石子合并','https://www.luogu.com.cn/problem/P1880','圆周相邻两堆合并，求最小和最大总代价。','复制数组后枚举长度n区间，覆盖全部断环位置；状态合并改min/max。','binary(a,true,false)与binary(a,true,true)。','O(n³)时间、O(n²)空间。',r'''
 void solve(){int n;cin>>n;vector<int>a(n);for(int &x:a)cin>>x;StoneMerge t;cout<<t.binary(a,true)<<'\n'<<t.binary(a,true,true)<<'\n';}
 ''')])

paint=r'''
struct SequencePaint {
    vector<int>a,nxt;vector<vector<int>>dp;
    void init(const vector<int>&v){a={0};for(int x:v)if(a.size()==1||a.back()!=x)a.push_back(x);int n=a.size()-1;nxt.assign(n+2,n+1);map<int,int>pos;
        for(int i=n;i>=1;i--){if(pos.count(a[i]))nxt[i]=pos[a[i]];pos[a[i]]=i;}
        dp.assign(n+2,vector<int>(n+2));
        for(int l=n;l>=1;l--)for(int r=l;r<=n;r++){dp[l][r]=dp[l+1][r];for(int x=nxt[l];x<=r;x=nxt[x])dp[l][r]=max(dp[l][r],dp[l+1][x-1]+dp[x][r]+1);}
    }
    int clear_min(){int n=a.size()-1;return n-dp[1][n];}
    int uniform_min(){return max(0LL,clear_min()-1);}
};
'''
add('dp','区间同色配对与涂色','SequencePaint',paint,'压缩相邻同色后，配对相同端点节省操作；收录原Cities最大节省状态与清空/涂色的次数接口。','O(n³)最坏时间、O(n²)空间；每色最多f次时O(fn²)。',
 [('init(a)','整数色序列，压缩相邻相同并计算最大节省dp'),('clear_min()','删除同色连续块直到空，等价从空白涂目标序列的最小次数'),('uniform_min()','允许任意同色连续块改色、使整串同色的最小次数；Cities模型')],
 ['配对后右子区间必须从x开始，而非x+1，因为x仍能继续配对。','原读入循环缺读n并改写n导致易错，整理版先读后压缩。','固定一个起点的Flood Fill是另一模型，不能直接假定uniform_min适用。'],src,[
 example('CF1132F','Clear the String','https://codeforces.com/contest/1132/problem/F','每次删除一段相同字符，求清空字符串最少次数。','先清空两个同色位置中间内容，使两端可共同删除，节省一次。','字符转整数，init后clear_min。','O(n³)时间、O(n²)空间。',r'''
 void solve(){int n;string s;cin>>n>>s;SequencePaint t;t.init(vector<int>(s.begin(),s.end()));cout<<t.clear_min()<<'\n';}
 '''),
 example('P4170','涂色','https://www.luogu.com.cn/problem/P4170','每次将连续区间涂同一颜色，可覆盖旧颜色，形成目标串最少次数。','一次同色涂色可先跨过中间区间，再补涂中间；与端点同色配对的省操作转移一致。','目标颜色串转整数，init后clear_min。','O(n³)时间、O(n²)空间。',r'''
 void solve(){string s;cin>>s;SequencePaint t;t.init(vector<int>(s.begin(),s.end()));cout<<t.clear_min()<<'\n';}
 ''')])

bracket=r'''
struct BracketDP {
    int mod;BracketDP(int mod=1000000007):mod(mod){}
    int normal(string s){int n=s.size();vector<int>f(n+2),g(n+2);f[0]=1;
        for(char c:s){fill(g.begin(),g.end(),0);for(int d=0;d<=n;d++)if(f[d]){if(c=='('||c=='?')g[d+1]=(g[d+1]+f[d])%mod;if(d&&(c==')'||c=='?'))g[d-1]=(g[d-1]+f[d])%mod;}f.swap(g);}return f[0];}
    int super(string s,int k){int n=s.size();s=" "+s;
        vector<vector<int>>f(n+2,vector<int>(n+2)),wrap=f,left=f,right=f,star=f;
        for(int l=1;l<=n;l++)for(int r=l;r<=min(n,l+k-1);r++){if(s[r]!='*'&&s[r]!='?')break;star[l][r]=1;}
        auto add=[&](int &x,int y){x=(x+y)%mod;};
        for(int len=1;len<=n;len++)for(int l=1;l+len-1<=n;l++){int r=l+len-1;
            if(len>=2&&(s[l]=='('||s[l]=='?')&&(s[r]==')'||s[r]=='?')){
                int val=len==2?1:star[l+1][r-1];if(len>2){add(val,f[l+1][r-1]);add(val,left[l+1][r-1]);add(val,right[l+1][r-1]);}wrap[l][r]=val;}
            f[l][r]=wrap[l][r];
            for(int mid=l+1;mid<r;mid++)add(f[l][r],wrap[l][mid]*(f[mid+1][r]+left[mid+1][r])%mod);
            for(int mid=l;mid<r&&mid-l+1<=k;mid++)if(star[l][mid])add(left[l][r],f[mid+1][r]);
            for(int mid=r-1;mid>=l&&r-mid<=k;mid--)if(star[mid+1][r])add(right[l][r],f[l][mid]);
        }return n?f[1][n]:0;
    }
};
'''
add('dp','括号计数与无歧义区间DP','BracketDP',bracket,'普通通配括号用余额状态；超级括号用首个完整括号块唯一分解，避免拼接计数重复。','normal O(n²)时间/O(n)空间；super O(n³)时间/O(n²)空间。',
 [('normal(s)','普通括号与?替换计数'),('super(s,k)','超级括号规范：括号内可有单侧星段，完整块之间可有星段，每段长度<=k')],
 ['超级序列不接受空串、外侧星号或(SAS)；不能只看括号余额。','以第一个原始括号块wrap分解，不能任意枚举两个合法块拼接，否则重复计数。','原两状态笔记遗漏嵌套单侧星段；整理版显式维护left/right。'],src,[
 example('P7914','括号序列','https://www.luogu.com.cn/problem/P7914','将?替换为括号或星号，使超级括号序列符合规范。','规则是嵌套加合法块拼接，需区间计数与无歧义分解，不能套普通括号余额。','BracketDP(1e9+7).super(s,k)。','O(n³)时间、O(n²)空间。',r'''
 void solve(){int n,k;string s;cin>>n>>k>>s;BracketDP t;cout<<t.super(s,k)<<'\n';}
 '''),
 example('ABC312D','Count Bracket Sequences','https://atcoder.jp/contests/abc312/tasks/abc312_d','无星号情况下，将?替换成括号并计数。','无星号退化为普通平衡括号，n=3000必须用余额滚动DP。','BracketDP(998244353).normal(s)。','O(n²)时间、O(n)空间。',r'''
 void solve(){string s;cin>>s;BracketDP t(998244353);cout<<t.normal(s)<<'\n';}
 ''',tests=[dict(input='(???(?\n',output='2\n'),dict(input=')))))\n',output='0\n')])])
