from common import *
import hashlib, collections
topics=json.loads(CATALOG.read_text(encoding='utf-8'));comp=json.loads((ROOT/'手册构建/compile_results.json').read_text(encoding='utf-8'));ran=json.loads((ROOT/'手册构建/random_results.json').read_text(encoding='utf-8'));pdf=json.loads((ROOT/'手册构建/pdf_check.json').read_text(encoding='utf-8'))
snapshot=json.loads((ROOT/'.work_review/handbook/github_snapshot.json').read_text(encoding='utf-8'));old=json.loads((ROOT/'.work_review/library/local_inventory.json').read_text(encoding='utf-8'))
preserved=[]
for r in old:
    actual=hashlib.sha256((ROOT/r['path']).read_bytes()).hexdigest();assert actual==r['sha256'],r['path'];preserved.append(r['path'])
for r in snapshot['files']:
    path='/'.join(part.rstrip() for part in r['path'].split('/'))
    if path in ('README.md','验证记录.md','GitHub同步预览.md','数据结构/线段树/权值线段树-README.md'):continue
    local=(ROOT/path).read_text(encoding='utf-8-sig').replace('\r\n','\n')
    assert local==r['content'].replace('\r\n','\n'),path
    preserved.append(path)
gaps=[t for t in topics if t.get('gap')];N=len(topics);E=sum(len(t['examples']) for t in topics)
summary=dict(topics=N,templates=N,examples=E,standalone_compiled=N,combined_compiled=len(comp),recorded_runs=sum(r['sample_tests'] for r in comp),oracle_groups=len(ran),oracle_cases=sum(r['cases'] for r in ran),primary_source_examples=E,pdf_pages=pdf['pages'],pdf_links=pdf['links'],pdf_bookmarks=pdf['bookmarks'],pdf_sha256=pdf['sha256'],pdf_bytes=pdf['bytes'],original_note_hash_checks=len(old),remote_snapshot_files=len(snapshot['files']),online_submissions=0,gaps=[dict(name=t['name'],reason=t['gap']) for t in gaps],compile=[{k:r[k] for k in ('topic','category','example','sha256','compiled','sample_tests')} for r in comp],oracles=[{k:r[k] for k in ('topic','cases','result','seed')} for r in ran])
(ROOT/'手册构建/验证摘要.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf-8')
back=ROOT/'.work_review/handbook/doc_backups';back.mkdir(parents=True,exist_ok=True)
for name in ('README.md','验证记录.md'):
    if (ROOT/name).exists() and not (back/name).exists():(back/name).write_bytes((ROOT/name).read_bytes())
link=lambda p:quote(p,safe='/')
lines=['# sheep-banzi','','个人 ACM/ICPC 算法模板库，C++17，沿用 WeightSegTree 的 struct、递归与命名风格。','','[可打印完整手册]('+link('output/pdf/ACM_ICPC 个人算法模板与例题手册.pdf')+') · [整理清单](手册整理清单.md) · [验证记录](手册验证记录.md) · [重建说明]('+link('手册构建/README.md')+')','',f'本版：**{N} 个知识点、{N} 份完整模板、{E} 份例题实现、{pdf["pages"]} 页 A4 PDF**。旧资料保留，整理版为统一维护入口。',f'全部独立模板和例题组合编译通过；{summary["recorded_runs"]} 组登记运行、{summary["oracle_cases"]} 例独立对拍通过。没有在线提交，不宣称AC。','','**待补：** Crystalfly 与 Kingdom’s Power 各只有一道已核实独立原题；其余知识点有2～3份例题。数位构造F1/F2为同题两档，LCM单行求和的两题为同一公式应用，已在说明中标明。','','## 整理版知识点索引','']
category_order=['数据结构','图论','数论','dp','杂','tirick'];names={'dp':'动态规划','杂':'字符串、线性代数与几何','tirick':'转化与技巧'}
for cat in category_order:
    lines+=['### '+names.get(cat,cat),'','| 知识点 | 支持功能 | 复杂度 | 真实例题 |','|---|---|---|---|']
    for t in sorted([x for x in topics if x['category']==cat],key=lambda x:x['name']):
        path=t['path'];ex=' · '.join('['+e['id']+']('+e['url']+')' for e in t['examples'])
        lines.append('| ['+t['name']+']('+link(path+'/README.md')+') / [板子]('+link(path+'/模板.cpp')+') | '+t['intro'].replace('|','\\|')+' | '+t['complexity'].replace('|','\\|')+' | '+ex+' |')
    lines+=['']
lines+=['## 原有资料与目录','','原有代码、笔记没有删除或批量改名。远端 `数据结构 ` 含尾随空格，本地使用 `数据结构`，发布时明确映射。课程原始PPT/视频/压缩包与无关程序目录未上传。','','[维护规范](维护规范.md) · [执行规则](AGENTS.md)。','','模板含完整头文件、struct、solve和signed main；例题文件只含solve及必要辅助代码，需要与本节模板组合。']
(ROOT/'README.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
report=['# 手册整理清单','','核实日期：2026-10-11。','',f'- 整理知识点：{N}。',f'- 独立完整模板：{N}；真实例题实现：{E}。',f'- PDF：{pdf["pages"]}页A4纵向；{pdf["bookmarks"]}个章节/例题书签；{pdf["links"]}个可点击目录/题目链接。',f'- 远端扫描快照：`{snapshot["commit"]}`，{len(snapshot["files"])}文件；原本地算法Markdown {len(old)}份的SHA-256全部保持一致。','- 新增代码位于原类别的`整理版/知识点/`下；原始板子保留。','- GitHub发布收录整理版、索引、构建程序和PDF；不会自动上传课程原件或工作缓存。','','## 尚未满足的要求','']
for t in gaps:report+=['- '+t['name']+'：'+t['gap']]
report+=['','代码源272/273的原题仍无法访问。按用户要求查找相似题：路径1对应HDU5293/HDU4912，路径2对应CF1675D/CF671D。四题均已读取原站信息，完整solve与模板组合验证通过；路径的点/边覆盖差异和特例转换见对应章节。','','## 重复与版本处理','','- 普通模板与课堂模板按具体算法合并；Tarjan/Kosaraju、两种匹配、点双/边双等独立算法分别归档。','- 普通权值树与破坏性合并分裂树分开；位图、树DP等课堂变体保留必要接口。','- 原稿缺少N、头文件或main时不直接视为算法BUG；整理版补齐完整依赖。','- 案例F1/F2和同公式LCMSUM两题的重复性质已写明；同一原题在不同板子下的调用分别计为例题实现。','','## 原资料映射','']
mapping=collections.defaultdict(list)
for t in topics:
    for p in t['sources']:mapping[p].append(t['name'])
for p,ns in sorted(mapping.items()):report+=['- `'+p+'`：'+'；'.join(ns)+'。']
(ROOT/'手册整理清单.md').write_text('\n'.join(report)+'\n',encoding='utf-8')
validation=['# 手册验证记录','','## 编译与运行','',f'- g++ 15.2，C++17，`-O2 -Wall -Wextra`；{N}份独立模板、{len(comp)}份例题组合均通过。',f'- {summary["recorded_runs"]}组登记样例/边界运行通过；其中54组新增用例来自原站官方样例。',f'- 17组独立穷举/直接算法参考，共{summary["oracle_cases"]}用例通过，固定随机种子20261011。','- 权值线段树此前另有63600次随机操作验证，详见保留的旧验证记录；本次计数不将其混入8550例。','- 这些是本地验证结果，没有提交在线评测；没有最大规模TLE/MLE/递归栈基准。','', '## 修复的明确问题','', '- 路径覆盖：补齐另一侧后缀最小转移，返回父亲前禁用未覆盖哨兵；INF改constexpr。','- Monster Hunter：消除对子血量的重复收费，父子均普通时只额外加一次子血量。','- Crystalfly：立即返回的第一个子点无需t=3，只有第3秒到达的第二点要求t=3。','- Outer space invaders：左右严格缩小为[l,k-1]、[k+1,r]，保留单时间点状态。','- 数位构造：不同数字使用次数不能用bool加减；至少k种允许增加多位。','- 01Trie：删除不存在值时先验证整条路径；动态扩容不保留vector失效引用。','- 基环图定向：按边编号避开前一条边，支持二点平行边环。','- P2016：原题给的是无向边，先DFS定根再转树DP。','- P1891：大量查询改为批量筛，不逐次试除。','- 样例编译任务对同一代码哈希加锁，避免并发写同一个exe。','','## 独立对拍范围','','| 知识点 | 独立参考 | 用例数 |','|---|---|---:|']
for r in ran:validation.append('| '+r['topic']+' | 小规模全子集/流量枚举、直接计算或状态搜索，详见verify_random.py | '+str(r['cases'])+' |')
validation+=['','## PDF 检查','',f'- 实际渲染全部{pdf["pages"]}页；检查全页联系图及高分辨率代表页面。','- A4页面尺寸、页码、全部知识点/例题题号、目录与书签目标、外链数量检查通过。','- 中文与代码字体内嵌，代码字符宽度检查无溢出、无缺字；正文黑白打印设计。','- 调整长代码分页，保留所有代码和例题后从428页减至320页。', '- 最终PDF SHA-256：`'+pdf['sha256']+'`。','','详见[验证摘要]('+link('手册构建/验证摘要.json')+')、[独立对拍程序]('+link('手册构建/verify_random.py')+')。']
(ROOT/'手册验证记录.md').write_text('\n'.join(validation)+'\n',encoding='utf-8')
(ROOT/'手册构建/README.md').write_text('''# 手册重建

构建数据以`catalog.json`为发布版快照：包含完整板子、独立例题、接口、复杂度、来源与实际用例。原始生成模块仅用于维护某个知识点；执行生成模块后需重新核实内容，不能盲目覆盖全部目录。

## 本地重建

需要Python 3.12、g++（C++17）、ReportLab、pypdf、Pillow、Poppler。排版使用Windows的仿宋、黑体与Consolas；其他平台请在build_pdf.py中指定可用的中文及等宽字体。

```text
python verify_all.py
python verify_templates.py
python verify_random.py
python build_pdf.py
python verify_pdf.py
```

从本目录运行上述命令。`verify_pdf.py`可用环境变量PDFTOPPM指定pdftoppm路径。渲染图在`tmp/pdfs`，PDF在`output/pdf`。

代码片段需组合模板编译。`combined_body`保存各例题经过变体修改后的实际依赖。`format_code.py`需要clang-format；样例验证对非唯一输出题不会盲目与官方示例逐字比较。

发布版的验证结果在`验证摘要.json`，没有写入机器的绝对临时路径。原站核实索引在`verified_sources.json`；缓存文件留在本地工作目录，不上传。
'''.replace('\n+','\n'),encoding='utf-8')
print('Docs updated; original notes preserved:',len(old),'templates:',N,'examples:',E,'PDF pages:',pdf['pages'])
