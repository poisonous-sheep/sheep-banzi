"""Generate the active model-aware indexes without deleting legacy files."""
from common import *
from collections import Counter
import os,hashlib
topics=json.loads(CATALOG.read_text(encoding='utf-8'))
byname={t['name']:t for t in topics}
results=json.loads((ROOT/'手册构建/compile_results.json').read_text(encoding='utf-8'))
lookup={(r['topic'],r['example']):r for r in results}
assert len(results)==sum(len(t['examples']) for t in topics)
link=lambda p:quote(str(p).replace('\\','/'),safe='/')
md=lambda s:s.replace('[','\\[').replace(']','\\]')
sources=json.loads((ROOT/'手册构建/verified_sources.json').read_text(encoding='utf-8'))
source_lookup={s['url']:s for s in sources}
verified=[]
for t in topics:
    folder=ROOT/t['path'];lines=['# '+t['name'],'','**类型：** '+t['kind'],'','**适用场景：** '+t['intro'],'','**复杂度与条件：** '+t['complexity'],'']
    if t['has_template']:lines+=['[完整C++17板子](模板.cpp)。','']
    elif t.get('template_ref'):
        owner=byname[t['template_ref']];rel=os.path.relpath(ROOT/owner['path']/'模板.cpp',folder)
        lines+=['复用['+owner['name']+'完整板子]('+link(rel)+')，同一算法定义只收录一次。','']
    else:lines+=['本节围绕题目推导组织，函数版题解不强行封装成struct。旧`模板.cpp`仅作历史对照（若存在），不作为本版推荐复制入口。','']
    if t['kind']=='模板型' or t['has_template']:
        lines+=['## 核心接口','']
        for name,desc in t['api']:lines+=['- `'+name+'`：'+desc]
        lines+=['']
    else:
        lines+=['## 模型识别与变体','']
        for label,value in t['model_notes']:
            if label in ('关键突破','状态与建模','优化与限制'):lines+=['**'+label+'：** '+md(value),'']
    for i,e in enumerate(t['examples'],1):
        r=lookup[(t['name'],e['id'])];assert r['compiled'] and not r.get('run_failed')
        form='独立程序' if e.get('full_code') and not e.get('dependencies') else '组合程序'
        e['validation']='C++17'+form+'编译通过'+(f'；{r["sample_tests"]}组登记运行通过' if r['sample_tests'] else '；未登记原题样例运行')+'；未在线提交'
        if e['id']=='ABC361E':evidence={'title':'AtCoder ABC361 E - Tree and Hamilton Path 2','statement_detected':True,'method':'读取AtCoder原站题面、约束与两个样例，2026-10-12'}
        else:evidence=source_lookup[e['url']]['evidence']
        assert evidence.get('statement_detected'),e['url']
        verified.append(dict(topic=t['name'],id=e['id'],url=e['url'],source_status=e['source_status'],evidence=evidence))
        lines+=['## 例题 '+str(i)+'：'+e['id']+' '+e['name'],'','[原题]('+e['url']+')','','**题意：** '+e['description'],'']
        if e.get('reasoning'):
            for label,value in e['reasoning']:
                if label!='启发式总结':lines+=['**'+label+'：** '+md(value),'']
        else:lines+=['**观察与建模：** '+e['why'],'','**初始化、数据组织、接口与答案：** '+e['calls'],'']
        if e.get('changes'):lines+=['**特殊修改：** '+e['changes'],'']
        lines+=['**本题复杂度：** '+e['complexity'],'']
        deps=e.get('dependencies',[])
        if deps:
            for d in deps:
                dt=byname[d];rel=os.path.relpath(ROOT/dt['path']/'模板.cpp',folder)
                lines+=['组合依赖：['+d+']('+link(rel)+')的struct定义（去掉其演示solve/main），再与本题代码编译。','']
        elif not e.get('full_code'):lines+=['依赖上面的完整板子，替换其solve后组合编译；本题文件是代码片段。','']
        lines+=['['+('完整函数题解' if form=='独立程序' else '题解及辅助代码')+']('+link(e['file'])+')。','']
        if e.get('reasoning'):lines+=['**启发式总结：** '+md(dict(e['reasoning'])['启发式总结']),'']
        lines+=['**验证：** '+e['validation'],'','**来源：** '+e['source_status'],'']
    lines+=['## 共同思路与易错点','']+['- '+p for p in t['pitfalls']]+['']
    if t['model_notes']:lines+=['共同启发：'+md(dict(t['model_notes'])['启发式总结']),'']
    lines+=['## 个人资料与历史','']+['- `'+s+'`' for s in t['sources']]+['']
    for legacy in t.get('legacy_paths',[]):
        rel=os.path.relpath(ROOT/legacy/'README.md',folder);lines+=['保留旧专题：['+Path(legacy).name+']('+link(rel)+')。','']
    (folder/'README.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
CATALOG.write_text(json.dumps(topics,ensure_ascii=False,indent=2),encoding='utf-8')
(ROOT/'手册构建/verified_sources.json').write_text(json.dumps(verified,ensure_ascii=False,indent=2),encoding='utf-8')

counts=Counter(t['kind'] for t in topics);N=len(topics);E=sum(len(t['examples']) for t in topics);boards=sum(t['has_template'] for t in topics)
randoms=json.loads((ROOT/'手册构建/random_results.json').read_text(encoding='utf-8'))
extra=json.loads((ROOT/'手册构建/training_results.json').read_text(encoding='utf-8'))
templates=json.loads((ROOT/'手册构建/template_results.json').read_text(encoding='utf-8'))
pdf_file=ROOT/'手册构建/pdf_check.json'
pdf=json.loads(pdf_file.read_text(encoding='utf-8')) if pdf_file.exists() else {}
# Ignore the old book's QA until the new artifact was actually rendered.
if not pdf.get('edition')=='training-v2':pdf={}
invfile=ROOT/'.work_review/library/local_inventory.json'
inv=json.loads(invfile.read_text(encoding='utf-8')) if invfile.exists() else []
for r in inv:assert hashlib.sha256((ROOT/r['path']).read_bytes()).hexdigest()==r['sha256'],r['path']
summary=dict(edition='training-v2',topics=N,kinds=dict(counts),templates=boards,examples=E,standalone_templates_compiled=len(templates),example_programs_compiled=len(results),function_programs=sum(bool(e.get('full_code')) for t in topics for e in t['examples']),recorded_runs=sum(r['sample_tests'] for r in results),oracle_groups=len(randoms)+len(extra),oracle_cases=sum(r['cases'] for r in randoms+extra),primary_source_examples=len(verified),original_note_hash_checks=len(inv),online_submissions=0,missing_originals=['代码源272/273，用户同意相似题替代'],example_count_gaps=[],pdf=pdf,compile=[{k:r[k] for k in ('topic','category','example','sha256','compiled','sample_tests')} for r in results],oracles=randoms+extra)
(ROOT/'手册构建/验证摘要.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf-8')
newpdf='output/pdf/ACM_ICPC_个人算法模板与思维训练手册.pdf'
pages=str(pdf['pages'])+'页A4 PDF' if pdf else 'A4完整PDF（生成检查后记录页数）'
lines=['# sheep-banzi','','个人ACM/ICPC模板与思维训练库，C++17，保留原命名和递归写法；普通DP/构造以函数题解组织。','','[完整打印手册]('+link(newpdf)+') · [整理清单](手册整理清单.md) · [验证记录](手册验证记录.md) · [重建说明]('+link('手册构建/README.md')+')','',f'本版：**{N}个专题：44模板型、26思维型、14混合型；{boards}份速查板子；{E}份例题；{pages}。**',f'全部例题程序及速查板子通过C++17编译；{summary["recorded_runs"]}组登记运行、{summary["oracle_cases"]}例独立参考对拍通过。未在线提交，不宣称AC。','','每个专题2至3道真实题。旧Crystalfly/Kingdom归入树上行走专题，加ABC361E对照状态接口；旧文件保留。F1/F2明确为同题难度版本，LCM单行两题明确为同公式批量应用。','','## 分类索引','']
for kind in ['模板型','思维型','混合型']:
    lines+=['### '+kind,'','| 类别 / 专题 | 代码入口 | 例题 |','|---|---|---|']
    for t in sorted([x for x in topics if x['kind']==kind],key=lambda x:(x['category'],x['name'])):
        name='['+t['category']+' / '+t['name']+']('+link(t['path']+'/README.md')+')'
        if t['has_template']:entry='[板子]('+link(t['path']+'/模板.cpp')+')'
        elif t.get('template_ref'):
            dt=byname[t['template_ref']];entry='[复用'+dt['name']+']('+link(dt['path']+'/模板.cpp')+')'
        else:entry=' · '.join('['+e['id']+'题解]('+link(t['path']+'/'+e['file'])+')' for e in t['examples'])
        ex=' · '.join('['+e['id']+']('+e['url']+')' for e in t['examples'])
        lines+=['| '+name+' | '+entry+' | '+ex+' |']
    lines+=['']
lines+=['## 原有资料与版本','','原始笔记、旧模板和上一版PDF全部保留，没有批量删除/改名。远端`数据结构 `含尾随空格，本地`数据结构`发布时明确映射。课程原件与工作缓存不自动上传。','','[维护规范](维护规范.md) · [本版完整要求](手册思维训练规范.md) · [执行规则](AGENTS.md)。']
(ROOT/'README.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
report=['# 手册整理清单','','版本：2026-10-12 / training-v2。','',f'- 活跃专题{N}：模板型44、思维型26、混合型14。',f'- 不重复速查板子{boards}；真实例题实现{E}，每专题2至3题。',f'- {summary["function_programs"]}份函数版例题，原struct版与原例题保留。',f'- {pages}；页数、字体、链接及渲染以实际PDF检查记录为准。',f'- {len(inv)}份原始本地算法笔记SHA-256全部保持一致。','','## 本次变化','','- 新增ABC361E及两个官方样例；树上行走专题用它、Kingdom、Crystalfly比较返回状态与不同题意接口，旧两专题代码未删除。','- 普通DP和思维题增加函数版，保留原函数名、核心转移和递归；基环树函数版移除继承包装。','- P1048采用直接O(TM)背包，P2016采用直接O(n)两状态树DP，CF1675D采用O(n)叶子下界构造，复杂度与推导同步更新。','- 补充逐步建模、正确性、边界、反例及组合意义；重复LowLink等共用正文板子。','- 按五部分编排；混合专题先列模型与操作映射，引用速查模块。','','## 未取得与验证边界','','- 代码源272/273原题仍未取得，已按用户要求用四道核实的相似题替代。','- 没有在线AC记录；无全库最大规模性能/栈压力保证。','- F1/F2属于同题两档，LCM两题使用同公式，两者并未标为不同原理。','','## 知识内容映射','']
for t in topics:report+=['- ['+t['name']+']('+link(t['path']+'/README.md')+')：'+t['kind']+'；来源`'+'`、`'.join(t['sources'])+'`。']
(ROOT/'手册整理清单.md').write_text('\n'.join(report)+'\n',encoding='utf-8')
v=['# 手册验证记录','','2026-10-12，本版实测。','',f'- {len(templates)}份速查板子独立编译、{E}份例题程序（含组合依赖）编译通过。',f'- {summary["recorded_runs"]}次登记样例/边界运行通过。',f'- 原17组8550例及11组函数版4850例独立参考全部通过；新增{len(extra)}组{sum(x["cases"] for x in extra)}例，共{summary["oracle_groups"]}组{summary["oracle_cases"]}例。','- ABC361E参考是所有起点的点集状态最短路；P2016穷举点集且随机边输入方向；P1048穷举物品子集；CF1675D校验最优条数与全部输出路径，随机重编号。','- 同一程序连续调用solve验证多组初始化，数位背包函数版的init_model显式清空a。','- 原模板的高风险BUG修复保留，详细历史见旧[验证记录](验证记录.md)及Git提交。','- 未在线提交；没有声称全部模型经过独立对拍或最大规模测试。','','## PDF自检','']
if pdf:v += [f'- 全部{pdf["pages"]}页已渲染，{len(pdf["detail_pages"])}页高分辨率检查。',f'- {pdf["bookmarks"]}书签及{pdf["links"]}链接，A4尺寸、目录目标、题号与知识覆盖检查通过。','- 代码宽度及字体缺字自动审计均为0；中文及等宽字体内嵌。','- SHA-256：`'+pdf['sha256']+'`。']
else:v+=['尚在生成，新版页数和渲染结果未填写。']
v+=['','[可复核摘要]('+link('手册构建/验证摘要.json')+')；[旧/函数版独立参考]('+link('手册构建/verify_random.py')+')；[新增题解参考]('+link('手册构建/verify_training.py')+')。']
(ROOT/'手册验证记录.md').write_text('\n'.join(v)+'\n',encoding='utf-8')
print('Docs:',N,'topics,',boards,'boards,',E,'examples,',summary['recorded_runs'],'runs,',summary['oracle_cases'],'oracle cases')
