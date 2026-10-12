"""Non-destructive upgrade of the published catalog to template/model/application roles."""
from common import *
from training_notes import NOTES, EXTRA, EXAMPLE_NOTES
import subprocess, copy, hashlib, collections

BASE=ROOT/'.work_review/thinking/catalog_before.json'
assert BASE.exists(), 'First save the actual prior catalog; never rebuild it from generators.'
topics=json.loads(BASE.read_text(encoding='utf-8'))
mixed={'线段树优化建图','Kruskal重构树','最小割建模','离线二维数点','启发式合并','DSU on Tree','步长根号分治','度数根号分治','曼哈顿距离坐标旋转','DFS序依赖背包','树上不相交给定路径','祖先路径最小费用覆盖','基环树最大权独立集','基环树最长路径与断环直径'}
thinking={'启发式分治','极角排序','异或比较与最高不同位','前缀关系计数','同余差与GCD','置换环分解','两互质面额不可表示数','卡特兰数与反射原理','互质集合与GCD分类计数','LCM单行求和','LCM矩形与集合求和'}
plain_mixed={'DFS序依赖背包','树上不相交给定路径','祖先路径最小费用覆盖','基环树最大权独立集','基环树最长路径与断环直径'}
byname={t['name']:t for t in topics}
cr=byname['Crystalfly三状态树DP']; kp=byname['Kingdom军队遍历树DP']
new=copy.deepcopy(kp)
new.update(name='树上行走与返回状态设计',struct='',path='dp/整理版/树上行走与返回状态设计',intro='从自由起终点遍历，到多军队，再到短倒计时：按题目约束重新推导子树与外界的状态接口。',complexity='三个例题均O(n)时间、O(n)空间；递归代码长链栈风险另计。',sources=sorted(set(cr['sources']+kp['sources'])),gap='',api=[],body='',code='',pitfalls=['自由端点、从根新军、捕获倒计时三种规则不能共享同一转移。','Crystalfly第一孩子可为t=1，仅第二孩子须t=3；Kingdom逆编号依赖fa[i]<i。'])
abc=dict(id='ABC361E',name='Tree and Hamilton Path 2',url='https://atcoder.jp/contests/abc361/tasks/abc361_e',description='带正权树，任选起点和终点，访问所有顶点至少一次，求最短总路程。',why='非起终点路径的边至少走两次，路径边至少一次；选择最长路径省下最多重复代价。',calls='后序DFS维护每点两条最长下行分支，得到直径；输出2*sum-diameter。',complexity='O(n)时间、O(n)邻接与递归空间。',changes='',replace=[],tests=[{'input':'4\n1 2 2\n1 3 3\n1 4 4\n','output':'11\n','provenance':'原站样例1','url':'https://atcoder.jp/contests/abc361/tasks/abc361_e'},{'input':'10\n10 9 1000000000\n9 8 1000000000\n8 7 1000000000\n7 6 1000000000\n6 5 1000000000\n5 4 1000000000\n4 3 1000000000\n3 2 1000000000\n2 1 1000000000\n','output':'9000000000\n','provenance':'原站样例2','url':'https://atcoder.jp/contests/abc361/tasks/abc361_e'}],source_status='已读取AtCoder原站题面，核实n≤2e5、正边权≤1e9及两个样例',validation='待编译')
abc['code']='''void solve() {
    int n, sum = 0, diameter = 0;
    cin >> n;
    vector<vector<pair<int,int>>> e(n + 1);
    vector<int> f(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        e[u].push_back({v,w}); e[v].push_back({u,w}); sum += w;
    }
    function<void(int,int)> dfs = [&](int u, int fa) {
        int mx1 = 0, mx2 = 0;
        for (auto [v,w] : e[u]) if (v != fa) {
            dfs(v,u); int z = f[v] + w;
            if (z >= mx1) { mx2 = mx1; mx1 = z; }
            else mx2 = max(mx2,z);
        }
        f[u] = mx1; diameter = max(diameter,mx1 + mx2);
    };
    dfs(1,0);
    cout << 2 * sum - diameter << '\\n';
}
'''
new['examples']=[abc,copy.deepcopy(kp['examples'][0]),copy.deepcopy(cr['examples'][0])]
topics=[t for t in topics if t['name'] not in (cr['name'],kp['name'])]+[new]

def matching(s,start,open='{',close='}'):
    depth=0
    for i in range(start,len(s)):
        if s[i]==open:depth+=1
        if s[i]==close:
            depth-=1
            if depth==0:return i
    raise ValueError('unbalanced source')

def flatten(body, name, code):
    # Preserve all member names, recursion and transitions. Only remove object packaging.
    pattern=r'struct\s+'+re.escape(name)+r'(?:\s*:\s*\w+)?\s*\{'
    m=re.search(pattern,body); assert m,name
    start=m.end()-1; end=matching(body,start)
    content=body[start+1:end]; prefix=body[:m.start()]; tail=body[end+2:]
    ctor=re.search(r'\b'+re.escape(name)+r'\s*\(',content)
    wrapper='void init_model() {}\n'
    if ctor:
        par=content.index('(',ctor.start()); pend=matching(content,par,'(',')')
        brace=content.index('{',pend); bend=matching(content,brace)
        args=content[par+1:pend]; initializer=content[pend+1:brace].strip()
        statements=content[brace+1:bend]
        if initializer==': FunctionalGraph(n)': statements='init(n);'
        elif initializer:
            assert initializer==': mod(mod)',(name,initializer)
            args=args.replace('int mod','int mod_');statements='mod=mod_;'
        wrapper='void init_model('+args+') {'+statements+'}\n'
        content=content[:ctor.start()]+content[bend+1:]
    elif name=='DigitKnapsack':wrapper='void init_model() { init(); }\n'
    # Inheritance existed only in old functional-graph wrappers. Inline the shared base.
    if ': FunctionalGraph' in m.group():
        bm=re.search(r'struct FunctionalGraph\s*\{',prefix);assert bm
        bs=bm.end()-1;be=matching(prefix,bs)
        base=prefix[bs+1:be]
        # Base constructor, if present, is replaced by derived init_model.
        bc=re.search(r'\bFunctionalGraph\s*\(',base)
        if bc:
            bb=base.index('{',bc.start());bbend=matching(base,bb);base=base[:bc.start()]+base[bbend+1:]
        prefix=prefix[:bm.start()]+base+prefix[be+2:]
        content=content.replace('FunctionalGraph::','')
    # One model object per solve (or sequential tests). Explicit global scope avoids shadows.
    objpat=r'\b'+re.escape(name)+r'\s+(\w+)\s*(?:\(([^;]*)\))?\s*;'
    objs=[]
    def obj(m):objs.append(m.group(1));return '::init_model('+ (m.group(2) or '') +');'
    code=re.sub(objpat,obj,code)
    assert objs or name+'::' in code,(name,code)
    for objname in objs:code=re.sub(r'\b'+re.escape(objname)+r'\.', '::',code)
    code=code.replace(name+'::','::')
    content='\n'.join(x[4:] if x.startswith('    ') else x for x in content.splitlines())
    # Anonymous namespace houses plain globals/functions, not a DP object or inheritance.
    raw=prefix+'\n'+content+'\n'+tail
    return raw+'\n'+wrapper+'\n'+code

def formatted(code):
    p=subprocess.run(['clang-format','-style={BasedOnStyle: LLVM, IndentWidth: 4, ColumnLimit: 88, AllowShortFunctionsOnASingleLine: None, BreakBeforeBraces: Attach}'],input=code.encode(),capture_output=True,check=True)
    return p.stdout.decode()

def prune_problem_functions(src):
    """Remove functions belonging solely to the other examples of the same topic."""
    defs=[]
    for m in re.finditer(r'(?m)^[A-Za-z][^;{}]*?\b(\w+)\s*\(',src):
        par=src.index('(',m.start());pend=matching(src,par,'(',')')
        brace=src.find('{',pend);semi=src.find(';',pend)
        if brace<0 or (semi>=0 and semi<brace):continue
        end=matching(src,brace)
        defs.append((m.group(1),m.start(),end+1,src[m.start():end+1]))
    names={d[0] for d in defs};needed={'main','solve'}
    while True:
        old=set(needed)
        for name,a,b,part in defs:
            if name in needed:
                needed.update(x for x in names if re.search(r'\b'+re.escape(x)+r'\s*\(',part))
        if old==needed:break
    for name,a,b,part in reversed(defs):
        if name not in needed:src=src[:a]+src[b:]
    return formatted(src)

for t in topics:
    t['kind']='混合型' if t['name'] in mixed else '思维型' if t['name'] in thinking or (t['category']=='dp' and t['name']!='数位DP与有限状态') else '模板型'
    t['has_template']=t['kind']=='模板型' or (t['kind']=='混合型' and t['name'] not in plain_mixed)
    if t['name']==new['name']:t['kind']='思维型';t['has_template']=False
    if t['kind']!='模板型':assert t['name'] in NOTES,t['name']
    t['model_notes']=NOTES.get(t['name'],[])
    t['legacy_paths']=[cr['path'],kp['path']] if t['name']==new['name'] else []
    folder=ROOT/t['path'];(folder/'例题').mkdir(parents=True,exist_ok=True)
    for e in t['examples']:
        e['specific_observation']=EXTRA.get(e['id'],e['description']+' '+e['why'])
        e['reasoning']=[list(x) for x in t['model_notes']]
        if e['reasoning']:
            e['reasoning'][0][1]=e['specific_observation']+' '+e['reasoning'][0][1]
            e['reasoning'].insert(4,('本题映射',e['description']+' '+e['why']+' '+e['calls']))
        if e['id'] in EXAMPLE_NOTES:e['reasoning']=[list(x) for x in EXAMPLE_NOTES[e['id']]]
        if e['id']=='P1048':e['complexity']='O(TM)时间、O(T)空间。'
        if e['id']=='P2016':e['complexity']='O(n)时间、O(n)邻接、状态及递归空间。'
        if e['id']=='CF1675D':
            e['complexity']='O(n)时间、O(n)空间；每个顶点只被上爬加入一次。'
            e['why']='每条竖直链至多含一个叶子，叶子数是下界；从每个叶子向上收集未使用点达到下界。'
            e['calls']='建立fa、has_child、used；从叶子上爬至已访问点，反转并输出paths。'
            e['changes']='本题是无权竖直链分组，采用O(n)直接构造；一般有权覆盖模型用于下一例CF671D。'
        if t['kind']=='思维型' or t['name'] in plain_mixed:
            origin=t
            if e['id']=='Gym103470H':origin=cr
            if e['id']=='Gym102769K':origin=kp
            if e['id']=='ABC361E':plain=e['code']
            elif e['id']=='CF1675D':
                plain='''void solve() {
                    int T; cin >> T;
                    while (T--) {
                        int n; cin >> n;
                        vector<int> fa(n+1), has_child(n+1), used(n+1);
                        for(int u=1;u<=n;u++) {cin>>fa[u]; if(fa[u]!=u) has_child[fa[u]]=1;}
                        vector<vector<int>> paths;
                        for(int u=1;u<=n;u++) if(!has_child[u]) {
                            vector<int> p; int v=u;
                            while(!used[v]) {
                                p.push_back(v); used[v]=1;
                                if(fa[v]==v) break;
                                v=fa[v];
                            }
                            reverse(p.begin(),p.end()); paths.push_back(p);
                        }
                        cout<<paths.size()<<'\\n';
                        for(auto &p:paths) {cout<<p.size()<<'\\n';for(int x:p)cout<<x<<' ';cout<<'\\n';}
                        cout<<'\\n';
                    }
                }'''
            elif e['id']=='P1048':
                plain='''void solve() {
                    int T, M; cin >> T >> M;
                    vector<int> dp(T+1);
                    while(M--) { int w,v; cin >> w >> v;
                        for(int j=T;j>=w;j--) dp[j]=max(dp[j],dp[j-w]+v);
                    }
                    cout << dp[T] << '\\n';
                }'''
            elif e['id']=='P2016':
                plain='''void solve() {
                    int n; cin >> n;
                    vector<vector<int>> e(n);
                    for(int i=0;i<n;i++) {int u,k;cin>>u>>k;while(k--){int v;cin>>v;e[u].push_back(v);e[v].push_back(u);}}
                    vector<array<int,2>> dp(n);
                    function<void(int,int)> dfs=[&](int u,int fa){
                        dp[u]={0,1};
                        for(int v:e[u]) if(v!=fa){dfs(v,u);dp[u][0]+=dp[v][1];dp[u][1]+=min(dp[v][0],dp[v][1]);}
                    };
                    dfs(0,-1);cout<<min(dp[0][0],dp[0][1])<<'\\n';
                }'''
            else:plain=flatten(e.get('combined_body',origin['body']),origin['struct'],e['code'])
            if e['id']=='P2014':
                sm=re.search(r'struct SCC\s*\{',plain)
                if sm:
                    se=matching(plain,sm.end()-1);plain=plain[:sm.start()]+plain[se+2:]
            if e['id']=='P1044':
                plain='''int exact(int n) {
                    assert(0 <= n && n <= 35);
                    __int128 c = 1;
                    for (int i = 1; i <= n; i++) c = c * 2 * (2 * i - 1) / (i + 1);
                    return c;
                }
                void solve() { int n; cin >> n; cout << exact(n) << '\\n'; }
                '''
            # Store a complete executable translation unit. Model wrapper is ordinary functions.
            e['full_code']=formatted(HEADER+plain+'\n'+MAIN)
            if t['name'] in {'二进制位贡献与Popcount计数','括号计数与无歧义区间DP','进位支付与有符号数位','树上距离分层计数','自相似序列奇偶分治','异或比较与最高不同位','同余差与GCD','LCM矩形与集合求和','互质集合与GCD分类计数'}:
                e['full_code']=prune_problem_functions(e['full_code'])
            e['display_code']=e['full_code']
            e['dependencies']=[]
            for depname, dep_topic in [('SCC','Tarjan强连通分量'),('Mobius','莫比乌斯反演与线性筛'),('Comb','素数模组合数')]:
                dm=re.search(r'struct\s+'+depname+r'\s*\{',e['display_code'])
                if dm:
                    ds=dm.end()-1;de=matching(e['display_code'],ds)
                    e['display_code']=e['display_code'][:dm.start()]+'// 组合依赖：本册 '+dep_topic+' 的 '+depname+' 定义。\n'+e['display_code'][de+2:]
                    e['dependencies'].append(dep_topic)
            e['file']='例题/'+re.sub(r'[<>:"/\\|?*]','-',e['id']+'-'+e['name'])+'-题解.cpp'
            saved=e['display_code'] if e['dependencies'] else e['full_code']
            (folder/e['file']).write_text('// '+e['id']+' '+e['url']+'\n'+saved,encoding='utf-8')
            e['validation']='待函数版C++17编译；不宣称在线AC'
        assert 2<=len(t['examples'])<=3,(t['name'],len(t['examples']))

# A shared algorithm body is printed once; other chapters link to its owner.
owners={}
for t in topics:
    if not t['has_template']:continue
    sig=hashlib.sha256(re.sub(r'\s+','',t['body']).encode()).hexdigest()
    if sig in owners:t['template_ref']=owners[sig]['name'];t['has_template']=False
    else:owners[sig]=t
CATALOG.write_text(json.dumps(topics,ensure_ascii=False,indent=2),encoding='utf-8')
counts=collections.Counter(t['kind'] for t in topics)
print('Classification:',dict(counts),'topics',len(topics),'boards',sum(t['has_template'] for t in topics),'examples',sum(len(t['examples']) for t in topics))
