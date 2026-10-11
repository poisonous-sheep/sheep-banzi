from common import *
thue=r'''
struct SelfSimilar {
    map<pair<int,string>,int>memo;
    void init(){memo.clear();}
    int calc(int L,const string&s){if(L<0)return 0;if(s.empty())return L+1;
        if(L==0){for(int i=0;i<(int)s.size();i++)if((__builtin_popcountll((unsigned long long)i)&1)!=s[i]-'0')return 0;return 1;}
        if(s.size()==1){int len=L+1,half=len/2;return half+(len%2&&(__builtin_popcountll((unsigned long long)L)&1)==s[0]-'0');}
        auto key=make_pair(L,s);if(memo.count(key))return memo[key];int n=s.size(),res=0;bool ok=true;
        for(int i=0;i+1<n;i+=2)if(s[i]==s[i+1])ok=false;
        if(ok){string t;for(int i=0;i<n;i+=2)t.push_back(s[i]);res+=calc(L/2,t);}
        ok=true;for(int i=1;i+1<n;i+=2)if(s[i]==s[i+1])ok=false;
        if(ok&&L>=1){string t;t.push_back(s[0]=='0'?'1':'0');for(int i=1;i<n;i+=2)t.push_back(s[i]);res+=calc((L-1)/2,t);}
        return memo[key]=res;
    }
    int transform(const string&s,int t,int k){if(t==0)return s[k]-'A';if(k==0)return (s[0]-'A'+t%3)%3;return (transform(s,t-1,k/2)+1+k%2)%3;}
};
'''
add('dp','自相似序列奇偶分治','SelfSimilar',thue,'利用f(2x)、f(2x+1)与f(x)的关系缩小下标；包含Thue-Morse模式计数与三字符替换查询变体。','calc的上界与模式不断折半，记忆化状态约O(log² L)，每状态O(m)；transform O(min(t,log k))时间/栈空间。',
 [('init/calc(L,s)','0..L内Thue-Morse序列匹配模式字符串s的起点数'),('transform(s,t,k)','ABC->BC/CA/AB替换t次后的0基位置k')],
 ['原calc在L=0或模式长1时可能无限递归，显式加入终止情形。','奇数起点的补位必须转换字符0/1；不要对ASCII直接产生非数字字符。','transform是三字符变体，不能把mod2的翻转直接换成同一题输入。'],['dp/数位动态规划进阶_比赛板子.md'],[
 example('QOJ12409','Bit Sequence','https://qoj.ac/problem/12409','统计0..L中，popcount(x+i)奇偶序列与给定模式相符的x个数。','Thue-Morse的偶数位置继承，奇数位置取反；起点奇偶两类各自将模式压半。','每组init清memo，整数数组转01字符串，calc(L,s)。','记忆化约O(m log² L)时间，上界状态空间同阶。',r'''
 void solve(){int T;cin>>T;SelfSimilar t;while(T--){int m,L;cin>>m>>L;string s;while(m--){int x;cin>>x;s.push_back('0'+x);}t.init();cout<<t.calc(L,s)<<'\n';}}
 ''',tests=[dict(input='3\n3 10\n0 1 0\n1 1000\n0\n9 1000000\n1 0 1 1 0 1 0 0 1\n',output='2\n501\n41667\n')]),
 example('ABC242D','ABC Transform','https://atcoder.jp/contests/abc242/tasks/abc242_d','ABC字符同时替换t轮后，查询第k个字符，t可能很大。','每个字符生成左右两子字符，0基位置的奇偶决定对子字符编号增加1或2；逆向回父位置。','将k转0基，transform(S,t,k-1)，返回值+A。','每询问O(min(t,log k))时间与递归空间。',r'''
 void solve(){string s;int q;cin>>s>>q;SelfSimilar t;while(q--){int time,k;cin>>time>>k;cout<<char('A'+t.transform(s,time,k-1))<<'\n';}}
 ''')])
