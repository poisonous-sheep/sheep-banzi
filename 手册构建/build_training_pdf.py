"""Five-part, type-aware print handbook. Content comes from the verified catalog."""
from pdf_layout import *
from collections import Counter
topics=json.loads(CATALOG.read_text(encoding='utf-8'))
order=['数据结构','图论','数论','dp','杂','tirick']
catnames={'dp':'动态规划','杂':'字符串、线性代数与几何','tirick':'转化、构造与计数'}
topics.sort(key=lambda t:(order.index(t['category']),t['name']))
byname={t['name']:t for t in topics}
counts=Counter(t['kind'] for t in topics)
examples=sum(len(t['examples']) for t in topics)
boards=sum(t['has_template'] for t in topics)
results=json.loads((ROOT/'手册构建/compile_results.json').read_text(encoding='utf-8'))
oracles=json.loads((ROOT/'手册构建/random_results.json').read_text(encoding='utf-8'))+json.loads((ROOT/'手册构建/training_results.json').read_text(encoding='utf-8'))
assert len(results)==examples and all(r['compiled'] and not r.get('run_failed') for r in results)
assert all(2<=len(t['examples'])<=3 for t in topics)
story=[]
def key(t):return 'topic_'+hashlib.sha256((t['category']+t['name']).encode()).hexdigest()[:12]
def code(s):story.extend([CondPageBreak(68),CodeListing(s)])
def linked(s,url,style=SMALL):return rich('<link href="'+html.escape(url,quote=True)+'" color="#202020">'+esc(s)+'</link>',style)
def boardref(t):
    owner=byname[t.get('template_ref',t['name'])]
    dest='board_'+key(owner) if owner['kind']=='混合型' else key(owner)
    return linked('复用模板：'+owner['name']+'（本册第二部分）','#'+dest)

cover=ParagraphStyle('Cover',parent=H1,fontSize=25,leading=36,alignment=1)
sub=ParagraphStyle('Sub',parent=BODY,fontSize=13,leading=22,alignment=1)
story.extend([Spacer(1,45*mm),para('ACM/ICPC',cover),para('个人算法模板',cover),para('与思维训练手册',cover),Spacer(1,14*mm),para('poisonous-sheep / sheep-banzi',sub),para('C++17 · 模板调用 · 状态设计 · 建模证明',sub),Spacer(1,17*mm),para(f'{len(topics)} 专题 / {boards} 份速查板子 / {examples} 份例题',sub),para('A4 打印装订版 · 2026-10-12 · v2',sub),Spacer(1,12*mm),para('本地编译与样例验证记录见阅读说明。未提交在线评测，不宣称 AC。',SMALL),PageBreak()])
story.append(Heading('第一部分  阅读说明与总目录',0,'part1'))
story.append(para('本版基于本地库及 GitHub main 的 fbd87c80b2ead1717b992c9c273153e9c20803f5。完整覆盖上一版85项知识内容：两项树上行走专用DP归入一个含三道递进例题的思维专题，活跃专题因此为84项，旧文件保留。课程原件、视频、无关软件与压缩包没有自动导入。'))
story.append(para(f'模板型 {counts["模板型"]} 项，思维型 {counts["思维型"]} 项，混合型 {counts["混合型"]} 项。共 {boards} 份不重复的速查板子；其余以题目推导组织。每个专题都有2至3道真实例题，共{examples}份实现。F1/F2仍明确视为同题的难度版本，LCM两道题明确为相同公式的批量应用。'))
story.append(para(f'本版{examples}个例题程序通过C++17编译，完成{sum(r["sample_tests"] for r in results)}次登记样例/边界运行。独立参考共{len(oracles)}组、{sum(r["cases"] for r in oracles)}例，其中原17组8550例、函数版11组4850例与新增直接题解4组1950例；具体范围见附录。以上不是在线AC或全部最大数据性能保证。'))
story.append(para('第二部分提供通用板子、接口和模板型例题。第三部分围绕观察、朴素方案、突破、状态/建模、证明、初始化、优化和启发讲解；普通DP使用函数和必要全局变量。第四部分先推导模型，再把实际操作映射到已经收录的模块，不再次展开相同板子。'))
story.append(para('标为完整题解的代码含头文件、solve和signed main；若注明组合依赖，则需从第二部分取对应struct定义后再编译。源文件与catalog分别保存阅读片段和验证组合程序，不能把缺少依赖的片段称为独立可编译。旧模板的示范main读取一次solve，多测在solve内处理。'))
story.append(para('代码源272/273原题无法访问，按用户要求改用HDU5293、HDU4912、CF1675D、CF671D。它们分别讲点不相交选路、祖先点覆盖及边覆盖转换；不会声称课堂原题已经获得。'))
story.append(para('A4纵向，左26mm装订边、右18mm；正文10.2pt、等宽代码9pt，黑白打印。建议按实际大小打印。代码行号连续，标题、题号及网址可检索，电子版目录与书签可点击。'))
story.extend([PageBreak(),para('总目录',H1)])
toc=TableOfContents()
toc.levelStyles=[ParagraphStyle('toc0',fontName='CNB',fontSize=11.5,leading=20,spaceBefore=6,wordWrap='CJK'),ParagraphStyle('toc1',fontName='CN',fontSize=9.6,leading=16,leftIndent=12,wordWrap='CJK'),ParagraphStyle('toc2',fontName='CN',fontSize=8.8,leading=14,leftIndent=24,wordWrap='CJK')]
story.append(toc)

def example(t,e,i):
    story.append(Heading(f'例题 {i}  {e["id"]}  {e["name"]}',2,key(t)+'_'+str(i)))
    story.append(linked(e['url'],e['url'],LINK))
    story.append(rich('<b>题意：</b>'+esc(e['description'])))
    if e.get('reasoning'):
        for label,value in e['reasoning']:
            if label=='启发式总结':continue
            story.append(rich('<b>'+esc(label)+'：</b>'+esc(value)))
    else:
        story.append(rich('<b>观察与建模：</b>'+esc(e['specific_observation'])))
        story.append(rich('<b>为何对应此算法：</b>'+esc(e['why'])))
        story.append(rich('<b>初始化、组织数据与调用：</b>'+esc(e['calls'])))
        story.append(para('具体调用顺序及变量对应见下面solve；区间开闭、值域和无解约定遵循本节接口，不能只凭函数名替换其他模板。',SMALL))
    if e.get('changes'):story.append(rich('<b>特殊修改：</b>'+esc(e['changes'])))
    for old,new in e.get('replace',[]):code('// 合并信息的题目变体：\n// 原\n'+old+'\n// 新\n'+new)
    story.append(rich('<b>本题复杂度：</b>'+esc(e['complexity'])))
    deps=e.get('dependencies',[])
    if deps:
        for d in deps:story.append(linked('组合依赖：'+d+' 的定义','#'+key(byname[d])))
    elif not e.get('full_code'):story.append(boardref(t))
    label='完整函数题解' if e.get('full_code') and not deps else '题解代码（需组合上述依赖）' if deps else 'solve 与必要辅助代码（配合已收录板子）'
    story.extend([CondPageBreak(100),para(label,HCODE),CodeListing(e.get('display_code',e['code']))])
    if e.get('reasoning'):
        story.append(rich('<b>启发式总结：</b>'+esc(dict(e['reasoning'])['启发式总结'])))
    story.append(para('验证：'+e.get('validation','待验证')+'；来源：'+e.get('source_status','待核实'),SMALL))

def topic(t,showboard=True,showexamples=True):
    story.extend([CondPageBreak(220),Heading(catnames.get(t['category'],t['category'])+' / '+t['name'],1,key(t))])
    story.append(rich('<b>类型与用途：</b>'+esc(t['kind']+'；'+t['intro'])))
    story.append(rich('<b>复杂度与适用范围：</b>'+esc(t['complexity'])))
    if showboard:
        if t['has_template']:
            story.extend([CondPageBreak(100),para('完整 C++17 板子',HCODE),CodeListing(t['code'])])
        elif t.get('template_ref'):story.append(boardref(t))
        for name,desc in t['api']:story.append(para(name+'：'+desc,SMALL))
    elif t['has_template'] or t.get('template_ref'):story.append(boardref(t))
    if showexamples:
        for i,e in enumerate(t['examples'],1):example(t,e,i)
        story.append(para('共同思路、边界与反例',H2))
        for p in t['pitfalls']:story.append(para('- '+p,SMALL))
        if t.get('model_notes'):story.append(para(dict(t['model_notes'])['启发式总结']))
    story.append(para('个人资料来源：'+'；'.join(t['sources']),SMALL))

story.extend([PageBreak(),Heading('第二部分  算法模板速查',0,'part2')])
for cat in order:
    group=[t for t in topics if t['category']==cat and t['kind']=='模板型']
    if not group:continue
    story.append(para(catnames.get(cat,cat),H1))
    for t in group:topic(t)
story.extend([PageBreak(),Heading('综合应用的可复用模块',0,'shared')])
story.append(para('以下板子在第四部分使用；这里只保存一次定义，建模推导与例题集中放在第四部分。'))
for t in topics:
    if t['kind']=='混合型' and t['has_template']:
        story.extend([CondPageBreak(220),Heading(t['name']+' / 速查模块',1,'board_'+key(t))])
        story.append(para(t['intro']));story.append(para(t['complexity']))
        code(t['code'])
        for name,desc in t['api']:story.append(para(name+'：'+desc,SMALL))

story.extend([PageBreak(),Heading('第三部分  算法思维与经典模型',0,'part3')])
for cat in ['dp','数据结构','杂','tirick','数论']:
    group=[t for t in topics if t['kind']=='思维型' and t['category']==cat]
    if not group:continue
    story.append(para(catnames.get(cat,cat)+'：模型与推导',H1))
    for t in group:topic(t,False)

story.extend([PageBreak(),Heading('第四部分  混合与综合应用',0,'part4')])
story.append(para('先写出原问题的选择、费用或转移，再明确哪些部分成为图的边、区间统计或子树接口。代码复用第二部分的结构；含普通DP的解法保留函数形式。'))
for t in topics:
    if t['kind']=='混合型':topic(t,False)

story.extend([PageBreak(),Heading('第五部分  附录与索引',0,'part5')])
story.append(Heading('常用代码片段与复杂度',1,'snippets'))
code(HEADER+MAIN)
for s in ['线性/树遍历O(n)：通常适合百万级，但递归深度和邻接内存要另查。','排序与平衡结构O(nlog n)：适合十万级常见题；常数、long long表和节点总数仍要预算。','背包O(nW)、区间DP O(n^3)：只在实际容量/区间数足够小时使用，不能把“DP”误当复杂度保证。','枚举集合O(2^n)、枚举全部状态转移O(3^n)：只适合小集合；上界应按操作数及内存具体估算。','__int128乘法后再取模可避免64位中间乘积溢出；仅#define int long long不能解决所有乘法。']:
    story.append(para(s))
story.append(Heading('常见边界与本版验证范围',1,'checks'))
for s in ['区间下标、空集/非空要求、0基/1基、闭区间端点和哨兵需与题面一致。','多测对全局vector、memo、堆、BIT以及时间戳显式init；函数版替代对象默认构造时必须补清空。','深树DFS、Tarjan、重构树和附着树递归都可能栈RE；本册保持用户递归写法，并注明需要足够栈空间。','节点池、二维表和#define int long long使每项8字节，可能MLE；统计表/编号可在确有范围保证时用int32_t。','本版新增ABC361E原站两个样例，普通背包和顶点覆盖另给直接题解；全部177份程序编译及登记输入运行，变更函数与原版还进行独立/回归对照，详情以手册验证记录和验证摘要为准。','没有在线评测AC记录，也没有对所有模型跑最大规模压力测试。课程272/273无法取得原题，以核实的相似题替代，未伪造原题输入格式。']:
    story.append(para(s))
story.append(Heading('知识点与旧版映射',1,'mapping'))
for t in topics:
    story.append(linked(t['kind']+' / '+t['name'],'#'+key(t)))
    if t.get('legacy_paths'):story.append(para('合并覆盖旧专题：'+'；'.join(t['legacy_paths'])+'。原模板与例题未删除。',SMALL))
mapping={}
for t in topics:
    for s in t['sources']:mapping.setdefault(s,[]).append(t['name'])
for s,names in sorted(mapping.items()):story.append(para(s+' → '+'；'.join(names),SMALL))
story.append(Heading('题号、位置与原题网址',1,'problems'))
entries=[]
for t in topics:
    for i,e in enumerate(t['examples'],1):entries.append((e['id'],t,i,e))
for _,t,i,e in sorted(entries,key=lambda x:(x[0],x[1]['name'])):
    story.append(KeepTogether([linked(e['id']+' / '+e['name']+' / '+t['name'],'#'+key(t)+'_'+str(i)),linked(e['url'],e['url'],LINK)]))

def check(items):
    for item in items:
        if isinstance(item,Paragraph):
            face=pdfmetrics.getFont(item.style.fontName).face
            for ch in item.getPlainText():
                if ch not in '\n\r\t' and ord(ch) not in face.charToGlyph:audit['missing_glyphs'].add(ch)
        elif isinstance(item,KeepTogether):check(item._content)
check(story)
assert not audit['missing_glyphs'],audit['missing_glyphs']
doc=HandbookDoc(str(TARGET),pagesize=A4,title='ACM/ICPC 个人算法模板与思维训练手册',author='poisonous-sheep',subject='算法模板、解题推导、综合建模与本地验证',pageCompression=1)
doc.multiBuild(story,maxPasses=5)
assert not audit['overflow'],audit['overflow'][:10]
assert not audit['missing_glyphs'],audit['missing_glyphs']
audit['missing_glyphs']=[]
audit.update(pages=doc.page,passes=doc.pass_count,topics=len(topics),examples=examples,boards=boards,kinds=dict(counts),output=TARGET.name,bookmarks=doc.entries)
(ROOT/'手册构建/pdf_build.json').write_text(json.dumps(audit,ensure_ascii=False,indent=2),encoding='utf-8')
print('Created PDF:',doc.page,'pages;',len(topics),'topics;',examples,'examples;',doc.pass_count,'TOC passes')
