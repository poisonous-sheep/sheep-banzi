from common import *

body=r'''
struct Frobenius {
    int maximum(int a,int b){assert(a>0&&b>0&&std::gcd(a,b)==1);__int128 z=(__int128)a*b-a-b;assert(z<=LLONG_MAX);return z;}
    int count(int a,int b){assert(a>0&&b>0&&std::gcd(a,b)==1);__int128 z=(__int128)(a-1)*(b-1)/2;assert(z<=LLONG_MAX);return z;}
};
'''
add('tirick','两互质面额不可表示数','Frobenius',body,'两个互质正面额的非负整数线性组合，最大不可表示数ab-a-b，不可表示正整数个数(a-1)(b-1)/2。','算式O(1)，断言gcd检查O(log min(a,b))；O(1)空间。',
 [('maximum(a,b)','互质正面额；任一为1时返回-1，表示无不可表示正整数'),('count(a,b)','不可表示正整数总数')],
 ['必须gcd(a,b)=1；非互质时有无限多个不可表示数，没有最大值。','非负组合和Bezout允许负系数的线性组合不同。','乘积使用__int128，返回值必须落入long long。'],['tirick/总结.md'],[
 example('P3951','小凯的疑惑','https://www.luogu.com.cn/problem/P3951','两种无限互质金币面额，求不能支付的最高价格。','每个模a余数由0..a-1个b恰好遍历；每个余数类最高空缺在其最小可表示数之前一个a，最大值ab-a-b。','maximum(a,b)，题目保证存在正数不可表示。','O(log min(a,b))时间/O(1)空间（含gcd断言）。',r'''
 void solve(){int a,b;cin>>a>>b;Frobenius t;cout<<t.maximum(a,b)<<'\n';}
 ''',tests=[dict(input='3 7\n',output='11\n')]),
 example('HDU1792','A new change problem','https://acm.hdu.edu.cn/showproblem.php?pid=1792','两种互质正面额，求最大不可表示金额及不可表示正金额个数。','最高空缺公式给最大值；每个余数类空缺求和给(a-1)(b-1)/2，补充计数应用。','循环到EOF读a,b，输出maximum和count。原站本次无法访问，输入输出格式待原站复核。','O(log min(a,b))时间/O(1)空间。',r'''
 void solve(){int a,b;Frobenius t;while(cin>>a>>b)cout<<t.maximum(a,b)<<' '<<t.count(a,b)<<'\n';}
 ''',tests=[dict(input='3 7\n',output='11 6\n')])])

topics=json.loads(CATALOG.read_text(encoding='utf-8'));t=next(t for t in topics if t['name']=='树状数组')
e=example('P1966','火柴排队','https://www.luogu.com.cn/problem/P1966','两列高度互异的火柴，可相邻交换，先最小化平方距离，再求最少交换数。','同秩配对最小化平方差；把第一列每个秩映射到第二列对应位置，最少相邻交换就是该位置排列逆序数。','排序两列(value,index)，构造位置排列，用BIT频率统计先前更大元素，结果模100000000-3。','O(n log n)时间/O(n)空间。',r'''
void solve(){int n;cin>>n;vector<pair<int,int>>a(n),b(n);for(int i=0;i<n;i++){cin>>a[i].first;a[i].second=i;}for(int i=0;i<n;i++){cin>>b[i].first;b[i].second=i+1;}sort(a.begin(),a.end());sort(b.begin(),b.end());vector<int>p(n);for(int i=0;i<n;i++)p[a[i].second]=b[i].second;BIT<int>t(n);int ans=0;for(int i=0;i<n;i++){ans=(ans+i-t.sum(p[i]))%(100000000-3);t.add(p[i],1);}cout<<ans<<'\n';}
''')
ex=[q for q in t['examples'] if q['id']!='P1966']+[e]
add(t['category'],t['name'],t['struct'],t['body'],t['intro'],t['complexity'],t['api'],t['pitfalls'],t['sources']+(['tirick/总结.md'] if 'tirick/总结.md' not in t['sources'] else []),ex)
