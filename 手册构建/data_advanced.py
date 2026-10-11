from common import *

w=source_struct('数据结构/线段树/权值线段树（动态开点基础版）.cpp','WeightSegTree')
examples=[]
for id,name,filename,url,desc,why,calls,comp in [
('ABC253C','Max-Min Query','ABC253C-Max-Min-Query.cpp','https://atcoder.jp/contests/abc253/tasks/abc253_c','增删元素，查询最大值与最小值之差。','次数叶子可批量删除，最值是排名端点。','先查次数再change；kth(1)、kth_max(1)。','O(Q log V)时间、O(D log V)空间。'),
('P3369','普通平衡树','P3369-普通平衡树.cpp','https://www.luogu.com.cn/problem/P3369','可重集合的六种有序操作。','次数前缀可转化为排名和严格前驱后继。','change增删；qur计数；kth输出排名值。','O(Q log V)时间、O(D log V)空间。'),
('ABC241D','Sequence Query','ABC241D-Sequence-Query.cpp','https://atcoder.jp/contests/abc241/tasks/abc241_d','查询<=x的第k大或>=x的第k小。','离散化1e18值域，将限制排名映射到全局排名。','离线收集阈值；按原顺序change/qur/kth并映射回原值。','O(Q log Q)时间、O(Q)空间。')]:
    s=(ROOT/'数据结构/线段树/例题'/filename).read_text(encoding='utf-8');examples.append(example(id,name,url,desc,why,calls,comp,s[s.index('void solve()'):]))
add('数据结构','动态开点权值线段树','WeightSegTree',w,'值域可重集合增删、区间次数、第k小/大；支持负值域。','操作O(1+log V)，空间O(1+D log V)，删除不回收节点。',[('init(L,R)','清空旧树'),('change(x,{c})','修改出现次数'),('qur(l,r).cnt','值域闭区间次数'),('kth(k)/kth_max(k)','1-based排名，非法返回-1')],['删除前保证足够数量。','-1可能是合法值，先验证排名。','中点使用__int128；节点编号32位，计数64位。'],['数据结构/线段树/权值线段树（动态开点基础版）.cpp'],examples)

s=(ROOT/'数据结构/线段树/权值线段树（合并与分裂）.cpp').read_text(encoding='utf-8')
body=s[s.index('struct info {'):s.index('void solve()')]
body=body.replace('vector<node> seg(1);','vector<node> seg = vector<node>(1);').replace('int mid = (l + r) >> 1;','int mid = l + ((__int128)r-l)/2;').replace('info operator+','friend info operator+')
body='struct WeightSegForest {\n'+body+'''\nint L,R;
    WeightSegForest(int l=1,int r=1000000000){L=l;R=r;init();}
    int change(int root,int pos,int v){return change(root,L,R,pos,v);}
    int qur(int root,int l,int r){return l>r?0:qur(root,L,R,l,r);}
    int size(int root){return seg[root].val.cnt;}
    int kth(int root,int k){return k<=0||k>size(root)?-1:kth(root,L,R,k);}
    int merge(int x,int y){return merge(x,y,L,R);}
    pair<int,int> split(int root,int k){return split(root,L,R,k);}
};
'''
dsu=source_struct('数据结构/整理版/并查集/模板.cpp','DSU')
add('数据结构','权值线段树合并与分裂','WeightSegForest',body+'\n'+dsu,'同值域多棵可重集合树；破坏性合并、分裂出最大的k个。','插入/排名/分裂O(log V)，合并O(实际同时非空访问节点数)；空间O(累计新建节点)。',[('change(root,pos,c)','返回新根，必须接收'),('merge(x,y)','返回合并根，旧y不能继续独立使用'),('split(root,k)','返回{剩余,最大的k个}'),('kth(root,k)','原接口第k大，非法返回-1')],['根之间不能共享节点；merge(x,x)非法。','第k小要转换为第size-k+1大。','按值域分裂由两次排名分裂实现；移走树之后及时清空旧根。'],['数据结构/线段树/权值线段树（合并与分裂）.cpp'],[
example('P5494','线段树分裂','https://www.luogu.com.cn/problem/P5494','维护多个集合，按值域拆分、合并、加频率和排名查询。','按<x和>y的次数切排名，将中间值域移到新根。','两次split；merge两侧；所有变根操作接收返回值。','分裂/更新/查询O(log n)，合并按节点交叠计；空间O((n+m)log n)。',r'''void solve(){int n,m;cin>>n>>m;WeightSegForest seg(1,n);vector<int>root(m+2);int tot=1;for(int i=1,c;i<=n;i++){cin>>c;if(c)root[1]=seg.change(root[1],i,c);}while(m--){int op,p;cin>>op>>p;if(op==0){int x,y;cin>>x>>y;int c=seg.qur(root[p],1,x-1);auto[low,high]=seg.split(root[p],seg.size(root[p])-c);int hi=seg.qur(high,y+1,n);auto[mid,upper]=seg.split(high,hi);root[p]=seg.merge(low,upper);root[++tot]=mid;}else if(op==1){int t;cin>>t;root[p]=seg.merge(root[p],root[t]);root[t]=0;}else if(op==2){int x,q;cin>>x>>q;if(x)root[p]=seg.change(root[p],q,x);}else if(op==3){int x,y;cin>>x>>y;cout<<seg.qur(root[p],x,y)<<'\n';}else{int k;cin>>k;if(k<=0||k>seg.size(root[p]))cout<<-1<<'\n';else cout<<seg.kth(root[p],seg.size(root[p])-k+1)<<'\n';}}}'''),
example('P3224','永无乡','https://www.luogu.com.cn/problem/P3224','合并岛屿，查询连通块内重要度第k小的岛编号。','DSU维护块代表；每块一棵权值树，合并时破坏性merge。','建立排名到编号映射；DSU合并前取两根，合并后挂到新代表。','总合并访问量按节点计，查询O(log n)；空间O(n log n)。',r'''void solve(){int n,m;cin>>n>>m;DSU dsu(n);WeightSegForest seg(1,n);vector<int>root(n+1),id(n+1);for(int i=1,x;i<=n;i++){cin>>x;id[x]=i;root[i]=seg.change(0,x,1);}auto join=[&](int x,int y){x=dsu.root(x);y=dsu.root(y);if(x==y)return;int r=seg.merge(root[x],root[y]);root[x]=root[y]=0;dsu.merge(x,y);root[dsu.root(x)]=r;};while(m--){int u,v;cin>>u>>v;join(u,v);}int q;cin>>q;while(q--){char op;int x,y;cin>>op>>x>>y;if(op=='B')join(x,y);else{int r=root[dsu.root(x)];if(y>seg.size(r))cout<<-1<<'\n';else cout<<id[seg.kth(r,seg.size(r)-y+1)]<<'\n';}}}''')])

add('数据结构','势能线段树','SegTree',r'''
struct SegTree {
    struct info{int sum=0,mx=0;friend info operator+(const info&l,const info&r){return {l.sum+r.sum,max(l.mx,r.mx)};}};
    struct node{info val;};int n;vector<node>seg;
    int ls(int id){return id<<1;}int rs(int id){return id<<1|1;}
    void update(int id){seg[id].val=seg[ls(id)].val+seg[rs(id)].val;}
    void build(int id,int l,int r,const vector<int>&a){if(l==r){seg[id].val={a[l],a[l]};return;}int mid=(l+r)>>1;build(ls(id),l,mid,a);build(rs(id),mid+1,r,a);update(id);}
    void build(const vector<int>&a){n=a.size()-1;assert(n>0);seg.assign(4*n+4,{});build(1,1,n,a);}
    int isqrt(int x){int y=sqrtl((long double)x);while((__int128)y*y>x)--y;while((__int128)(y+1)*(y+1)<=x)++y;return y;}
    void update_sqrt(int id,int l,int r,int ql,int qr){if(qr<l||r<ql||seg[id].val.mx<=1)return;if(l==r){int v=isqrt(seg[id].val.mx);seg[id].val={v,v};return;}int mid=(l+r)>>1;update_sqrt(ls(id),l,mid,ql,qr);update_sqrt(rs(id),mid+1,r,ql,qr);update(id);}
    void modify_mod(int id,int l,int r,int ql,int qr,int x){if(qr<l||r<ql||seg[id].val.mx<x)return;if(l==r){int v=seg[id].val.mx%x;seg[id].val={v,v};return;}int mid=(l+r)>>1;modify_mod(ls(id),l,mid,ql,qr,x);modify_mod(rs(id),mid+1,r,ql,qr,x);update(id);}
    void change(int id,int l,int r,int p,int x){if(l==r){seg[id].val={x,x};return;}int mid=(l+r)>>1;if(p<=mid)change(ls(id),l,mid,p,x);else change(rs(id),mid+1,r,p,x);update(id);}
    info qur(int id,int l,int r,int ql,int qr){if(ql<=l&&r<=qr)return seg[id].val;int mid=(l+r)>>1;if(qr<=mid)return qur(ls(id),l,mid,ql,qr);if(ql>mid)return qur(rs(id),mid+1,r,ql,qr);return qur(ls(id),l,mid,ql,qr)+qur(rs(id),mid+1,r,ql,qr);}
    void update_sqrt(int l,int r){update_sqrt(1,1,n,l,r);}
    void modify_mod(int l,int r,int x){assert(x>0);modify_mod(1,1,n,l,r,x);}
    void change(int p,int x){assert(x>=0);change(1,1,n,p,x);}
    info qur(int l,int r){return qur(1,1,n,l,r);}
};
''','非负数组区间开方、区间取模、单点赋值和区间和；用mx跳过不变节点。','开方每值只改变O(log log A)次；取模有效改变使值至少减半，累计O((n+m)log A log n)；查询O(log n)，空间O(n)。',[('update_sqrt(l,r)','向下取整开方'),('modify_mod(l,r,x)','x>0，区间取模'),('change(p,x)','非负赋值'),('qur(l,r).sum','区间和')],['用整数平方比较修正sqrt浮点误差。','不能将单次修改声称总是O(log n)；需势能摊还分析。'],['数据结构/线段树/势能线段树.cpp'],[
example('P4145','花神游历各国','https://www.luogu.com.cn/problem/P4145','区间开方或区间和。','max<=1的节点所有值已稳定，可停止递归。','op0调用update_sqrt，op1调用qur；先交换反向端点。','累计O(n log log A log n+m log n)时间、O(n)空间。',r'''void solve(){int n;cin>>n;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];SegTree seg;seg.build(a);int m;cin>>m;while(m--){int op,l,r;cin>>op>>l>>r;if(l>r)swap(l,r);if(!op)seg.update_sqrt(l,r);else cout<<seg.qur(l,r).sum<<'\n';}}'''),
example('CF438D','The Child and Sequence','https://codeforces.com/problemset/problem/438/D','区间和、区间取模、单点赋值。','a%x只有在a>=x时改变，并且改变后小于原值一半。','modify_mod用区间max剪枝；赋值change恢复势能。','摊还O((n+m)log A log n)时间、O(n)空间。',r'''void solve(){int n,m;cin>>n>>m;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];SegTree seg;seg.build(a);while(m--){int op,l,r,x;cin>>op;if(op==3){cin>>l>>x;seg.change(l,x);}else{cin>>l>>r;if(op==1)cout<<seg.qur(l,r).sum<<'\n';else{cin>>x;seg.modify_mod(l,r,x);}}}}''',tests=[['5 5\n1 2 3 4 5\n2 3 5 4\n3 3 5\n1 2 5\n2 1 3 3\n1 1 3\n','8 5']])])

sg=source_struct('数据结构/线段树/线段树优化建图.cpp','SegGraph')
sg=sg.replace('pq.push({0, s});','pq.push({0, s});').replace('void add_edge(int u, int v, int w) { adj[u].push_back({v, w}); }','void add_edge(int u, int v, int w) { if((int)adj.size()<=max(u,v))adj.resize(max(u,v)+1); adj[u].push_back({v, w}); }')
add('数据结构','线段树优化建图','SegGraph','const int INF=4000000000000000000LL;\nusing pii=pair<int,int>;\n'+sg,'点到区间、区间到点建有向边；两棵树方向相反，原点共享叶子。','建图O(n+q log n)，非负最短路O((n+q log n)log(n+q))，空间O(n+q log n)。',[('add_edge(u,v,w)','普通边，允许新增辅助点'),('add_out(v,l,r,w)','点到区间'),('add_in(l,r,v,w)','区间到点'),('dijkstra(s)','非负边权，返回距离')],['不能把in/out两棵树方向反写。','INF需大于可达最短路，d+w不溢出。','辅助点需要先++tot，add_edge动态扩容。'],['数据结构/线段树/线段树优化建图.cpp'],[
example('CF786B','Legacy','https://codeforces.com/problemset/problem/786/B','三类点/区间边，求源点到所有原点的距离。','每个区间拆成O(log n)个树节点，保持原图可达与代价。','按op1/2/3调用add_edge/add_out/add_in，dijkstra只输出原点。','O((n+q log n)log n)时间、O(n+q log n)空间。',r'''void solve(){int n,q,s;cin>>n>>q>>s;SegGraph sg(n);while(q--){int op,v,l,r,w;cin>>op;if(op==1){cin>>v>>l>>w;sg.add_edge(v,l,w);}else{cin>>v>>l>>r>>w;if(op==2)sg.add_out(v,l,r,w);else sg.add_in(l,r,v,w);}}auto d=sg.dijkstra(s);for(int i=1;i<=n;i++)cout<<(d[i]==INF?-1:d[i])<<(i==n?'\n':' ');}'''),
example('P6348','Journeys','https://www.luogu.com.cn/problem/P6348','区间间建立双向通信线路，求起点到各站的最少线路数。','区间到辅助点0，辅助点到另一段1；反向另建辅助点。','每条线路新增两个点，add_in与add_out组合；Dijkstra求代价。','O((n+m log n)log(n+m))时间、O(n+m log n)空间。',r'''void solve(){int n,m,p;cin>>n>>m>>p;SegGraph sg(n);while(m--){int a,b,c,d;cin>>a>>b>>c>>d;int x=++sg.tot;sg.add_in(a,b,x,0);sg.add_out(x,c,d,1);int y=++sg.tot;sg.add_in(c,d,y,0);sg.add_out(y,a,b,1);}auto dis=sg.dijkstra(p);for(int i=1;i<=n;i++)cout<<(dis[i]==INF?-1:dis[i])<<'\n';}''')])
