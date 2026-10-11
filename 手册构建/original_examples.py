from common import *

def extend(name,e,extra_body=''):
    topics=json.loads(CATALOG.read_text(encoding='utf-8'));t=next(t for t in topics if t['name']==name)
    ex=[x for x in t['examples'] if x['id']!=e['id']]+[e]
    body=t['body']
    if extra_body and 'struct ManhattanSeg' not in body:body+=extra_body
    add(t['category'],name,t['struct'],body,t['intro'],t['complexity'],t['api'],t['pitfalls'],t['sources'],ex,gap=t.get('gap',''))

extend('置换环分解',example('ABC436E','Minimum Swap','https://atcoder.jp/contests/abc436/tasks/abc436_e','计数能作为最少交换排序方案第一步的交换。','最优步骤必须令环数加1，因此两点必须在同一个原置换环内；任意同环两点都能拆成两个环。','init、build，对每个cycle长度L累加L(L-1)/2。','O(n)时间/O(n)空间。',r'''
void solve(){int n;cin>>n;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];Permutation t;t.init(a);t.build();int ans=0;for(auto &c:t.cycle){int L=c.size();ans+=L*(L-1)/2;}cout<<ans<<'\n';}
''',tests=[dict(input='5\n3 1 4 2 5\n',output='6\n')]))

seg=r'''
struct ManhattanSeg {
    int n;vector<Manhattan>seg;
    ManhattanSeg(int n=0):n(n),seg(4*n+4){}
    Manhattan merge(Manhattan a,Manhattan b){a.mn1=min(a.mn1,b.mn1);a.mx1=max(a.mx1,b.mx1);a.mn2=min(a.mn2,b.mn2);a.mx2=max(a.mx2,b.mx2);return a;}
    void change(int u,int l,int r,int p,int x,int y){if(l==r){seg[u].init();seg[u].add(x,y);return;}int m=(l+r)>>1;if(p<=m)change(u<<1,l,m,p,x,y);else change(u<<1|1,m+1,r,p,x,y);seg[u]=merge(seg[u<<1],seg[u<<1|1]);}
    Manhattan qur(int u,int l,int r,int L,int R){if(L<=l&&r<=R)return seg[u];int m=(l+r)>>1;Manhattan ans;if(L<=m)ans=merge(ans,qur(u<<1,l,m,L,R));if(R>m)ans=merge(ans,qur(u<<1|1,m+1,r,L,R));return ans;}
    void change(int p,int x,int y){change(1,1,n,p,x,y);}
    Manhattan qur(int l,int r){return qur(1,1,n,l,r);}
};
'''
extend('曼哈顿距离坐标旋转',example('ABC437F','Manhattan Christmas Tree 2','https://atcoder.jp/contests/abc437/tasks/abc437_f','支持修改一个点坐标，查询下标区间内到指定坐标最远的曼哈顿距离。','将Manhattan四个极值作为线段树合并信息，区间极值仍满足旋转距离公式。','完整板子附ManhattanSeg；每点change初值；修改change，查询qur(L,R).qur(x,y)。','O((n+q)log n)时间/O(n)空间。',r'''
void solve(){int n,q;cin>>n>>q;ManhattanSeg t(n);for(int i=1;i<=n;i++){int x,y;cin>>x>>y;t.change(i,x,y);}while(q--){int op;cin>>op;if(op==1){int i,x,y;cin>>i>>x>>y;t.change(i,x,y);}else{int l,r,x,y;cin>>l>>r>>x>>y;cout<<t.qur(l,r).qur(x,y)<<'\n';}}}
''',tests=[dict(input='3 4\n-1 -1\n1 2\n-2 1\n2 1 2 0 0\n2 1 3 -1 2\n1 1 0 1\n2 1 3 -1 2\n',output='3\n3\n2\n')]),seg)

extend('对顶堆与中位数',example('LeetCode480','滑动窗口中位数','https://leetcode.cn/problems/sliding-window-median/description/','返回每个长度k窗口的中位数；偶数窗口取中间两数平均。','滑窗加入新值、删除旧值，multiset可删任意一个重复值，无需额外惰性删除；偶数窗口组合L最大与R最小。','原平台提交Solution::medianSlidingWindow，签名使用int32_t避免宏改变平台int类型；solve是本地n,k和数组适配器。','O(n log k)时间/O(k)维护空间，输出另需O(n)。',r'''
struct Solution {
    vector<double> medianSlidingWindow(vector<int32_t>& nums,int32_t k){Mid t;vector<double>ans;for(int i=0;i<(int)nums.size();i++){t.add(nums[i]);if(i>=k)t.del(nums[i-k]);if(i+1>=k){double z=t.mid();if(k%2==0)z=(z+(double)*t.R.begin())/2;ans.push_back(z);}}return ans;}
};
void solve(){int n;int32_t k;cin>>n>>k;vector<int32_t>a(n);for(auto &x:a)cin>>x;Solution s;auto ans=s.medianSlidingWindow(a,k);for(double x:ans)cout<<setprecision(10)<<x<<' ';cout<<'\n';}
''',tests=[dict(input='8 3\n1 3 -1 -3 5 3 6 7\n',output='1 -1 -1 3 5 6\n')]))
