"""Independent exhaustive / direct oracles for high-risk templates; seed fixed."""
from common import *
import random, subprocess, itertools, math, hashlib, collections, concurrent.futures
R=random.Random(20261011)
topics=json.loads(CATALOG.read_text(encoding='utf-8'));T={t['name']:t for t in topics}
B=ROOT/'.work_review/handbook/oracles';B.mkdir(parents=True,exist_ok=True)
jobs=[]
def addjob(name,driver,cases):
    code=HEADER+T[name]['body']+'\nsigned main(){ios::sync_with_stdio(false);cin.tie(nullptr);int T;cin>>T;while(T--){'+driver+'}}\n'
    jobs.append((name,code,cases))
def paths(fa,x,y):
    ax=[]
    while x:ax.append(x);x=fa[x]
    by=[]
    while y:by.append(y);y=fa[y]
    aset=set(ax);l=next(z for z in by if z in aset)
    return set(ax[:ax.index(l)+1]+by[:by.index(l)])
cases=[]
for z in range(500):
    n=R.randint(1,9);m=R.randint(0,11);fa=[0,0]+[R.randrange(1,u) for u in range(2,n+1)]
    pp=[(R.randint(1,n),R.randint(1,n),R.randint(-5,20)) for _ in range(m)]
    masks=[sum(1<<(u-1) for u in paths(fa,x,y)) for x,y,w in pp]
    ans=0
    for s in range(1<<m):
        mask=val=0;ok=True
        for i in range(m):
            if s>>i&1:
                if mask&masks[i]:ok=False;break
                mask|=masks[i];val+=pp[i][2]
        if ok:ans=max(ans,val)
    data=f'{n} {m}\n'+' '.join(map(str,fa[2:]))+'\n'+''.join(f'{x} {y} {w}\n' for x,y,w in pp)
    cases.append((data,f'{ans} {ans}'))
addjob('树上不相交给定路径','int n,m;cin>>n>>m;TreePathSelect t(n);for(int u=2,p;u<=n;u++){cin>>p;t.add_edge(p,u);}t.build();while(m--){int x,y,w;cin>>x>>y>>w;t.add_path(x,y,w);}cout<<t.run(1,false)<<" "<<t.run(1,true)<<"\\n";',cases)
cases=[]
for z in range(600):
    n=R.randint(1,8);m=R.randint(0,11);fa=[0,0]+[R.randrange(1,u) for u in range(2,n+1)];pp=[];masks=[]
    for _ in range(m):
        u=R.randint(1,n);anc=[];x=u
        while x:anc.append(x);x=fa[x]
        v=R.choice(anc);pp.append((u,v,R.randint(0,15)));masks.append(sum(1<<(x-1) for x in paths(fa,u,v)))
    ans=10**9
    for s in range(1<<m):
        mask=val=0
        for i in range(m):
            if s>>i&1:mask|=masks[i];val+=pp[i][2]
        if mask==(1<<n)-1:ans=min(ans,val)
    if ans==10**9:ans=-1
    data=f'{n} {m}\n'+' '.join(map(str,fa[2:]))+'\n'+''.join(f'{x} {y} {w}\n' for x,y,w in pp)
    cases.append((data,f'{ans} {ans}'))
addjob('祖先路径最小费用覆盖','int n,m;cin>>n>>m;AncestorCover t(n);for(int u=2,p;u<=n;u++){cin>>p;t.add_edge(p,u);}t.build();while(m--){int x,y,w;cin>>x>>y>>w;t.add_path(x,y,w);}cout<<t.run()<<" "<<t.run_heap()<<"\\n";',cases)
cases=[]
for z in range(500):
    n=R.randint(1,9);fa=[0,0]+[R.randrange(1,u) for u in range(2,n+1)];hp=[0]+[R.randint(1,30) for _ in range(n)];ans=[10**9]*(n+1)
    for s in range(1<<n):
        k=s.bit_count();val=sum(hp[u]*(1+int(u>1 and not(s>>(fa[u]-1)&1))) for u in range(1,n+1) if not(s>>(u-1)&1));ans[k]=min(ans[k],val)
    cases.append((str(n)+'\n'+' '.join(map(str,fa[2:]))+'\n'+' '.join(map(str,hp[1:]))+'\n',' '.join(map(str,ans))))
addjob('二状态树形背包','int n;cin>>n;BinaryTreeKnapsack t(n);for(int u=2,p;u<=n;u++){cin>>p;t.add_edge(p,u);}for(int u=1,hp;u<=n;u++){cin>>hp;t.cost[u]={hp,0};t.edge_cost[u][0][0]=hp;}for(int x:t.run())cout<<x<<" ";cout<<"\\n";',cases)
cases=[]
for z in range(600):
    m=R.randint(0,7);enemy=[(R.randint(0,5),0,R.randint(1,10)) for _ in range(m)];enemy=[(l,R.randint(l,5),w) for l,r,w in enemy]
    actions=[]
    for time in range(6):
        for w in range(1,11):actions.append((sum(1<<i for i,(l,r,d) in enumerate(enemy) if l<=time<=r and d<=w),w))
    f=[10**9]*(1<<m);f[0]=0
    for s in range(1<<m):
        for mask,cost in actions:f[s|mask]=min(f[s|mask],f[s]+cost)
    cases.append((str(m)+'\n'+''.join(f'{l} {r} {w}\n' for l,r,w in enemy),str(f[-1])))
addjob('区间强制对象分治','int n;cin>>n;vector<IntervalSplit::info>a(n);for(auto &z:a)cin>>z.l>>z.r>>z.w;IntervalSplit t;t.init_enemies(a);cout<<t.run()<<"\\n";',cases)
cases=[]
for z in range(700):
    n=R.randrange(0,35);k=R.randrange(0,n+2);mod=R.randint(1,180);val=math.comb(n,k)%mod if k<=n else 0
    cases.append((f'{n} {k} {mod}\n',str(val)))
addjob('扩展Lucas','int n,k,m;cin>>n>>k>>m;ExLucas t;t.init(m);cout<<t.binom(n,k)<<"\\n";',cases)
cases=[]
for z in range(1200):
    m=R.randint(1,160);a=R.randrange(m+1);b=R.randrange(m);ans=-1;seen=set();v=1%m;x=0
    while v not in seen:
        if v==b:ans=x;break
        seen.add(v);v=v*a%m;x+=1
    cases.append((f'{a} {b} {m}\n',str(ans)))
addjob('BSGS离散对数','int a,b,m;cin>>a>>b>>m;BSGS t;cout<<t.solve(a,b,m)<<"\\n";',cases)
cases=[]
for z in range(600):
    n=R.randint(1,3);a=[R.randint(1,5) for _ in range(n)];m=R.randint(1,200);v=a[-1]
    for x in a[-2::-1]:v=pow(x,v)
    cases.append((f'{n} {m}\n'+' '.join(map(str,a))+'\n',str(v%m)))
addjob('扩展欧拉与指数塔','int n,m;cin>>n>>m;vector<int>a(n+1);for(int i=1;i<=n;i++)cin>>a[i];PowerTower t;t.init(a);cout<<t.qur(1,n,m)<<"\\n";',cases)
cases=[]
for z in range(650):
    n=R.randint(0,10);w=R.randint(0,80);a=[(R.randint(1,30),R.randint(-5,30)) for _ in range(n)];ans=0
    for s in range(1<<n):
        if sum(a[i][0] for i in range(n) if s>>i&1)<=w:ans=max(ans,sum(a[i][1] for i in range(n) if s>>i&1))
    cases.append((f'{n} {w}\n'+''.join(f'{x} {y}\n' for x,y in a),str(ans)))
addjob('数位背包','int n,w;cin>>n>>w;DigitKnapsack t;while(n--){int a,b;cin>>a>>b;t.add(a,b);}cout<<t.qur(w)<<"\\n";',cases)
cases=[]
for z in range(400):
    n=R.randint(1,9);p=list(range(1,n+1));q=p.copy();R.shuffle(p);R.shuffle(q);ans=0
    for s in range(1<<n):
        have=set()
        for i in range(n):
            if s>>i&1:have.update((p[i],q[i]))
        ans+=len(have)==n
    cases.append((str(n)+'\n'+' '.join(map(str,p))+'\n'+' '.join(map(str,q))+'\n',str(ans)))
addjob('置换环分解','int n;cin>>n;vector<int>p(n+1),q(n+1),a(n+1),pos(n+1);for(int i=1;i<=n;i++){cin>>p[i];pos[p[i]]=i;}for(int i=1;i<=n;i++){cin>>q[i];a[i]=pos[q[i]];}Permutation t;t.init(a);cout<<t.cover_ways()<<"\\n";',cases)
cases=[]
for z in range(500):
    n=R.randint(1,8);p=[0]+[R.randint(1,n) for _ in range(n)];val=[0]+[R.randint(-10,25) for _ in range(n)];ans=0
    for s in range(1<<n):
        if any((s>>(u-1)&1) and (s>>(p[u]-1)&1) for u in range(1,n+1)):continue
        ans=max(ans,sum(val[u] for u in range(1,n+1) if s>>(u-1)&1))
    cases.append((str(n)+'\n'+''.join(f'{val[u]} {p[u]}\n' for u in range(1,n+1)),str(ans)))
addjob('基环树最大权独立集','int n;cin>>n;Knight t(n);for(int u=1;u<=n;u++)cin>>t.val[u]>>t.p[u];cout<<t.run()<<"\\n";',cases)
cases=[]
for z in range(300):
    n=R.randint(1,8);p=[0]+[R.randint(1,n) for _ in range(n)];w=[0]+[R.randint(0,12) for _ in range(n)];e=[[] for _ in range(n+1)]
    for u in range(1,n+1):e[u].append((p[u],w[u]));e[p[u]].append((u,w[u]))
    comp=[];seen=set()
    for u in range(1,n+1):
        if u in seen:continue
        s=[u];seen.add(u)
        for v in s:
            for x,c in e[v]:
                if x not in seen:seen.add(x);s.append(x)
        comp.append(s)
    ans=0
    for c in comp:
        best=0
        def dfs(u,mask,d):
            global_unused=None
            nonlocal_placeholder=None
            values.append(d)
            for v,cost in e[u]:
                if not(mask>>(v-1)&1):dfs(v,mask|1<<(v-1),d+cost)
        values=[]
        for u in c:dfs(u,1<<(u-1),0)
        ans+=max(values)
    cases.append((str(n)+'\n'+''.join(f'{p[u]} {w[u]}\n' for u in range(1,n+1)),str(ans)))
addjob('基环树最长路径与断环直径','int n;cin>>n;Island t(n);for(int u=1;u<=n;u++)cin>>t.p[u]>>t.w[u];cout<<t.run()<<"\\n";',cases)

# Generate the formal grammar as a SET, independently of the counting recurrence.
grammar={}
for k in range(1,5):
    gs=[set() for _ in range(9)]
    for length in range(2,9):
        if length==2:gs[length].add('()')
        if 1<=length-2<=k:gs[length].add('('+'*'*(length-2)+')')
        for a in gs[length-2]:gs[length].add('('+a+')')
        for j in range(1,k+1):
            if length-j-2>=0:
                for a in gs[length-j-2]:gs[length].add('('+'*'*j+a+')');gs[length].add('('+a+'*'*j+')')
        for split in range(1,length):
            for a in gs[split]:
                for b in gs[length-split]:gs[length].add(a+b)
                for j in range(1,k+1):
                    if length-split-j>=0:
                        for b in gs[length-split-j]:gs[length].add(a+'*'*j+b)
    grammar[k]=gs
cases=[]
for z in range(600):
    n=R.randint(1,8);k=R.randint(1,4);s=''.join(R.choice('()*????') for _ in range(n));ans=sum(all(a=='?' or a==b for a,b in zip(s,word)) for word in grammar[k][n])
    cases.append((f'{k} {s}\n',str(ans)))
addjob('括号计数与无歧义区间DP','int k;string s;cin>>k>>s;BracketDP t;cout<<t.super(s,k)<<"\\n";',cases)

cases=[]
for z in range(100):
    n=R.randint(1,6);fa=[0,0]+[R.randrange(1,u) for u in range(2,n+1)];e=[[] for _ in range(n+1)]
    for u in range(2,n+1):e[u].append(fa[u]);e[fa[u]].append(u)
    q=collections.deque([(1,(),0)]);seen={(1,())};ans=0
    while q:
        mask,pos,d=q.popleft()
        if mask==(1<<n)-1:ans=d;break
        for v in e[1]:
            nxt=tuple(sorted(pos+(v,)));state=(mask|1<<(v-1),nxt)
            if len(nxt)<=n-1 and state not in seen:seen.add(state);q.append((*state,d+1))
        for i,u in enumerate(pos):
            if i and pos[i]==pos[i-1]:continue
            for v in e[u]:
                nxt=tuple(sorted(pos[:i]+pos[i+1:]+((v,) if v!=1 else ())))
                state=(mask|1<<(v-1),nxt)
                if state not in seen:seen.add(state);q.append((*state,d+1))
    cases.append((str(n)+'\n'+' '.join(map(str,fa[2:]))+'\n',str(ans)))
addjob('Kingdom军队遍历树DP','int n;cin>>n;KingdomPower t(n);for(int u=2;u<=n;u++)cin>>t.fa[u];cout<<t.run()<<"\\n";',cases)

cases=[]
for z in range(100):
    n=R.randint(1,5);fa=[0,0]+[R.randrange(1,u) for u in range(2,n+1)];e=[[] for _ in range(n)];a=[R.randint(1,15) for _ in range(n)];delay=[R.randint(1,3) for _ in range(n)]
    for u in range(2,n+1):e[u-1].append(fa[u]-1);e[fa[u]-1].append(u-1)
    rem=[-1]*n;rem[0]=-3
    for v in e[0]:rem[v]=delay[v]
    state=(0,tuple(rem));q=collections.deque([state]);seen={state};ans=0
    while q:
        u,rem=q.popleft();ans=max(ans,sum(a[i] for i in range(n) if rem[i]==-3))
        for v in e[u]:
            nxt=[x-1 if x>=0 else x for x in rem]
            nxt=[-2 if x==-1 and rem[i]>=0 else x for i,x in enumerate(nxt)]
            if nxt[v]>=0 or nxt[v]==-1:nxt[v]=-3
            for w in e[v]:
                if nxt[w]==-1:nxt[w]=delay[w]
            state=(v,tuple(nxt))
            if state not in seen:seen.add(state);q.append(state)
    cases.append((str(n)+'\n'+' '.join(map(str,a))+'\n'+' '.join(map(str,delay))+'\n'+''.join(f'{fa[u]} {u}\n' for u in range(2,n+1)),str(ans)))
addjob('Crystalfly三状态树DP','int n;cin>>n;Crystalfly t(n);for(int u=1;u<=n;u++)cin>>t.a[u];for(int u=1;u<=n;u++)cin>>t.t[u];for(int i=1,u,v;i<n;i++){cin>>u>>v;t.add_edge(u,v);}cout<<t.run()<<"\\n";',cases)

for kind in ('circulation','maxflow','mincost'):
    cases=[]
    for z in range(400):
        n=R.randint(2,4);pairs=[(u,v) for u in range(1,n+1) for v in range(u+1,n+1)] if kind=='mincost' else [(u,v) for u in range(1,n+1) for v in range(1,n+1) if u!=v]
        R.shuffle(pairs);pairs=pairs[:R.randint(0,min(6,len(pairs)))];edges=[]
        for u,v in pairs:
            hi=R.randint(0,2);lo=R.randint(0,hi);c=R.randint(-5,8);edges.append((u,v,lo,hi,c))
        best=-1;cost=10**9
        for f in itertools.product(*(range(lo if kind!='mincost' else 0,hi+1) for u,v,lo,hi,c in edges)):
            balance=[0]*(n+1);val=0
            for flow,(u,v,lo,hi,c) in zip(f,edges):balance[u]-=flow;balance[v]+=flow;val+=flow*c
            if kind=='circulation':
                if not any(balance):best=1;break
            elif not any(balance[2:n]) and balance[1]<=0 and balance[n]==-balance[1]:
                flow=-balance[1]
                if flow>best:best=flow;cost=val
                elif flow==best:cost=min(cost,val)
        if kind=='circulation':expected=str(best==1 and 1 or 0)
        elif kind=='mincost':expected=f'{best} {cost}'
        else:expected=str(best)
        data=f'{n} {len(edges)}\n'+''.join(f'{u} {v} {lo if kind!="mincost" else 0} {hi} {c}\n' for u,v,lo,hi,c in edges)
        cases.append((data,expected))
    if kind=='mincost':driver='int n,m;cin>>n>>m;MinCostFlow t(n);while(m--){int u,v,l,r,c;cin>>u>>v>>l>>r>>c;t.add_edge(u,v,r,c);}auto [f,c]=t.run(1,n);cout<<f<<" "<<c<<"\\n";';name='最小费用最大流'
    else:
        suffix='cout<<t.feasible()<<"\\n";' if kind=='circulation' else 'auto ans=t.maxflow(1,n);cout<<(ans?*ans:-1)<<"\\n";'
        driver='int n,m;cin>>n>>m;BoundedFlow t(n);while(m--){int u,v,l,r,c;cin>>u>>v>>l>>r>>c;t.add_edge(u,v,l,r);}'+suffix;name='有上下界可行流与最大流'
    addjob(name,driver,cases)

def work(job):
    name,code,cases=job;sha=hashlib.sha256(code.encode()).hexdigest();cpp=B/(sha[:16]+'.cpp');exe=cpp.with_suffix('.exe');cpp.write_text(code,encoding='utf-8')
    if not exe.exists():
        p=subprocess.run(['g++','-std=c++17','-O2',str(cpp),'-o',str(exe)],capture_output=True,timeout=90)
        assert p.returncode==0,(name,p.stderr.decode(errors='replace'))
    data=str(len(cases))+'\n'+''.join(x for x,y in cases);p=subprocess.run([str(exe)],input=data.encode(),capture_output=True,timeout=60)
    assert p.returncode==0,(name,p.stderr.decode(errors='replace'))
    lines=p.stdout.decode().splitlines();assert len(lines)==len(cases),(name,len(lines),len(cases))
    for i,(out,(inp,expected)) in enumerate(zip(lines,cases)):
        assert out.split()==expected.split(),(name,i,inp,expected,out)
    return dict(topic=name,cases=len(cases),result='全部通过',seed=20261011,sha256=sha)
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:results=list(pool.map(work,jobs))
(ROOT/'手册构建/random_results.json').write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')
print('Independent oracle families:',len(results),'cases:',sum(r['cases'] for r in results),'all passed')
