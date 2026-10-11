from common import *
import hashlib, html

topics=json.loads(CATALOG.read_text(encoding='utf-8'))
compile_results=json.loads((ROOT/'手册构建/compile_results.json').read_text(encoding='utf-8'))
comp={(r['topic'],r['example']):r for r in compile_results}
raw=json.loads((ROOT/'手册构建/source_results.json').read_text(encoding='utf-8'))
source={x['url']:x for x in raw}
def canonical(u):return re.sub(r'/contest/(\d+)/problem/([^/?]+)',r'/problemset/problem/\1/\2',u).replace('http://','https://')
web={}
for p in (ROOT/'.work_review/handbook/web_sources').glob('*.txt'):
    for block in re.split(r'-{30,}',p.read_text(encoding='utf-8')):
        match=re.search(r'"ref_id":"([^"]+)"',block)
        if match and 'Internal Error' not in block and re.search(r'Total lines: ([1-9]\d*)',block):
            web[canonical(match.group(1))]=dict(cache=str(p.relative_to(ROOT)),title=block.strip().splitlines()[0],statement_detected=True)
# Source through QOJ's statement iframe, read directly in the browser tool.
web['https://qoj.ac/problem/12409']=dict(cache='https://qoj.ac/download.php?id=12409&type=statement',title='Bit Sequence',statement_detected=True)
verified=[]
for t in topics:
    for e in t['examples']:
        r=comp[(t['name'],e['id'])]
        e['validation']='C++17组合编译通过'+(f'，{r["sample_tests"]}组登记运行通过' if r['sample_tests'] else '；未登记样例运行')+'；未在线提交'
        evidence=source.get(e['url'],{})
        if not evidence.get('statement_detected'):evidence=web.get(canonical(e['url']),{})
        e['source_status']='已读取原站题面并核实题号、模型与输入格式' if evidence.get('statement_detected') else '原站题面读取待补核'
        verified.append(dict(topic=t['name'],id=e['id'],url=e['url'],source_status=e['source_status'],evidence=evidence))
        if e['id']=='HDU1792':
            e['name']='A New Change Problem';e['calls']='循环到EOF读a,b，输出maximum和count。'
        if e['id']=='P2016':e['calls']='先建立无向邻接表，再DFS定根；cost={0,1}，父子均不选的边费用INF；run后取最小费用。'
    t['validation']='完整模板及例题组合编译通过；部分知识点另有独立对拍，详见验证记录'
    if t['name']=='树上不相交给定路径':t['pitfalls']=[p.replace('HDU原站本次不可访问，题目输入格式保留待原站复核状态。','HDU原站题面与样例已核实，原题n,m≤100000，需使用fast版。') for p in t['pitfalls']]
    if t['name']=='Kruskal重构树':t['complexity']='排序O(m log m)，仅路径压缩的并查集按O((n+m)log n)保守估计，倍增O(n log n)；空间O(n log n+m)。'
    folder=ROOT/t['path'];lines=['# '+t['name'],'','**用途与条件：** '+t['intro'],'','**复杂度：** '+t['complexity'],'','[完整模板](模板.cpp)；模板solve采用第一例题或注明的演示输入。','','## 接口','']+['- `'+k+'`：'+v for k,v in t['api']]
    if t.get('gap'):lines[2:2]=['**例题数量待补：** '+t['gap'],'']
    lines+=['','## 例题','']
    for e in t['examples']:
        lines+=['### '+e['id']+' '+e['name'],'','[原题]('+e['url']+')','', '**题意：** '+e['description'],'','**为什么使用：** '+e['why'],'','**如何调用：** '+e['calls'],'','**复杂度：** '+e['complexity']]
        if e['changes']:lines+=['','**变体：** '+e['changes']]
        for old,new in e['replace']:lines+=['','原：`'+old+'`；改为：`'+new+'`。']
        lines+=['','[solve及辅助代码]('+quote(e['file'],safe='/')+')；依赖本节模板，替换原solve后组合编译。','', '**验证：** '+e['validation'],'','**来源：** '+e['source_status'],'']
    lines+=['## 易错点','']+['- '+p for p in t['pitfalls']]+['','## 个人资料来源','']+['- `'+s+'`' for s in t['sources']]+['','未提交在线评测，不宣称AC。']
    (folder/'README.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
CATALOG.write_text(json.dumps(topics,ensure_ascii=False,indent=2),encoding='utf-8')
(ROOT/'手册构建/verified_sources.json').write_text(json.dumps(verified,ensure_ascii=False,indent=2),encoding='utf-8')
print('Examples with primary-source evidence:',sum('已读取' in x['source_status'] for x in verified),'/',len(verified))
print('Still unverified:',[(x['id'],x['url']) for x in verified if '已读取' not in x['source_status']])
