"""Independent oracles for newly introduced direct programs, including repeated solve calls."""
from common import *
import random,itertools,heapq,subprocess,hashlib,concurrent.futures
R=random.Random(20261012)
topics=json.loads(CATALOG.read_text(encoding='utf-8'))
E={e['id']:e for t in topics for e in t['examples'] if e.get('full_code')}
B=ROOT/'.work_review/thinking/oracles';B.mkdir(parents=True,exist_ok=True)
jobs=[]
cases=[]
for z in range(400):
    n=R.randint(2,8);edges=[(u,R.randrange(u),R.randint(1,20)) for u in range(1,n)]
    g=[[] for _ in range(n)]
    for u,v,w in edges:g[u].append((v,w));g[v].append((u,w))
    D={};pq=[]
    for u in range(n):D[(1<<u,u)]=0;heapq.heappush(pq,(0,1<<u,u))
    while pq:
        d,s,u=heapq.heappop(pq)
        if d!=D[(s,u)]:continue
        if s==(1<<n)-1:ans=d;break
        for v,w in g[u]:
            key=(s|1<<v,v);nd=d+w
            if nd<D.get(key,10**30):D[key]=nd;heapq.heappush(pq,(nd,*key))
    cases.append((str(n)+'\n'+''.join(f'{u+1} {v+1} {w}\n' for u,v,w in edges),str(ans)))
jobs.append(('ABC361E',cases,'所有起点状态的点集最短路'))
cases=[]
for z in range(500):
    n=R.randint(1,11);edges=[(u,R.randrange(u)) for u in range(1,n)]
    ans=min(s.bit_count() for s in range(1<<n) if all((s>>u&1) or (s>>v&1) for u,v in edges))
    rows=[[] for _ in range(n)]
    for u,v in edges:
        if R.randrange(2):u,v=v,u
        rows[u].append(v)
    data=str(n)+'\n'+''.join(str(u)+' '+str(len(a))+' '+' '.join(map(str,a))+'\n' for u,a in enumerate(rows))
    cases.append((data,str(ans)))
jobs.append(('P2016',cases,'穷举全部顶点覆盖，随机输入边方向'))
cases=[]
for z in range(650):
    n=R.randint(0,10);W=R.randint(0,70);items=[(R.randint(1,30),R.randint(0,40)) for _ in range(n)]
    ans=max(sum(v for i,(w,v) in enumerate(items) if s>>i&1) for s in range(1<<n) if sum(w for i,(w,v) in enumerate(items) if s>>i&1)<=W)
    cases.append((f'{W} {n}\n'+''.join(f'{w} {v}\n' for w,v in items),str(ans)))
jobs.append(('P1048',cases,'穷举全部物品子集'))

def run(job):
    id,cases,oracle=job;src=E[id]['full_code']
    assert 'int t = 1;\n    // cin >> t;' in src
    src=src.replace('int t = 1;\n    // cin >> t;','int t;\n    cin >> t;')
    sha=hashlib.sha256(src.encode()).hexdigest();cpp=B/(sha[:16]+'.cpp');exe=cpp.with_suffix('.exe')
    cpp.write_text(src,encoding='utf-8')
    p=subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra',str(cpp),'-o',str(exe)],capture_output=True,timeout=90)
    assert p.returncode==0,p.stderr.decode(errors='replace')
    data=str(len(cases))+'\n'+''.join(x for x,y in cases)
    p=subprocess.run([str(exe)],input=data.encode(),capture_output=True,timeout=45)
    assert p.returncode==0,p.stderr.decode(errors='replace')
    lines=p.stdout.decode().splitlines();assert len(lines)==len(cases)
    for i,(a,(inp,b)) in enumerate(zip(lines,cases)):assert a.split()==b.split(),(id,i,inp,a,b)
    return dict(example=id,cases=len(cases),oracle=oracle,seed=20261012,result='全部通过',sha256=sha)
with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:out=list(pool.map(run,jobs))
cases=[]
for z in range(400):
    n=R.randint(1,90);old=[0,1]+[R.randrange(1,u) for u in range(2,n+1)]
    ids=list(range(1,n+1));R.shuffle(ids);fa=[0]*(n+1)
    for u in range(1,n+1):fa[ids[u-1]]=ids[old[u]-1]
    cases.append(fa)
src=E['CF1675D']['full_code'];sha=hashlib.sha256(src.encode()).hexdigest();cpp=B/(sha[:16]+'.cpp');exe=cpp.with_suffix('.exe')
cpp.write_text(src,encoding='utf-8')
p=subprocess.run(['g++','-std=c++17','-O2',str(cpp),'-o',str(exe)],capture_output=True,timeout=90);assert p.returncode==0,p.stderr.decode(errors='replace')
data=str(len(cases))+'\n'+''.join(str(len(a)-1)+'\n'+' '.join(map(str,a[1:]))+'\n' for a in cases)
p=subprocess.run([str(exe)],input=data.encode(),capture_output=True,timeout=30);assert p.returncode==0
tokens=iter(map(int,p.stdout.decode().split()))
for fa in cases:
    n=len(fa)-1;parents={fa[u] for u in range(1,n+1) if fa[u]!=u};leaves=n-len(parents)
    number=next(tokens);assert number==leaves,(n,number,leaves)
    seen=[]
    for _ in range(number):
        length=next(tokens);assert length>=1
        path=[next(tokens) for _ in range(length)]
        assert all(1<=u<=n for u in path)
        assert all(fa[v]==u for u,v in zip(path,path[1:]))
        seen+=path
    assert sorted(seen)==list(range(1,n+1)),(fa,seen)
assert next(tokens,None) is None
out.append(dict(example='CF1675D',cases=len(cases),oracle='叶子数最优下界＋输出点覆盖、不重与父子连续性检查，随机重编号',seed=20261012,result='全部通过',sha256=sha))
(ROOT/'手册构建/training_results.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
print('New direct-program oracles:',len(out),'cases',sum(x['cases'] for x in out),'all passed')
