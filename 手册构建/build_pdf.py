"""Print edition: A4, embedded fonts, complete code, accurate TOC and bookmarks."""
from common import *
import math, html, hashlib
from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.lib.units import mm
from reportlab.lib.styles import ParagraphStyle
from reportlab.platypus import BaseDocTemplate, PageTemplate, Frame, Paragraph, Spacer, PageBreak, Flowable, KeepTogether, CondPageBreak
from reportlab.platypus.tableofcontents import TableOfContents

OUT=ROOT/'output/pdf';OUT.mkdir(parents=True,exist_ok=True)
TARGET=OUT/'ACM_ICPC 个人算法模板与例题手册.pdf'
pdfmetrics.registerFont(TTFont('CN','C:/Windows/Fonts/simfang.ttf'))
pdfmetrics.registerFont(TTFont('CNB','C:/Windows/Fonts/simhei.ttf'))
pdfmetrics.registerFont(TTFont('Mono','C:/Windows/Fonts/consola.ttf'))
pdfmetrics.registerFontFamily('CN',normal='CN',bold='CNB',italic='CN',boldItalic='CNB')
PAGE_W,PAGE_H=A4;LM=26*mm;RM=18*mm;TM=19*mm;BM=18*mm;W=PAGE_W-LM-RM
BODY=ParagraphStyle('Body',fontName='CN',fontSize=10.2,leading=15,wordWrap='CJK',spaceAfter=5,textColor=colors.HexColor('#202020'))
SMALL=ParagraphStyle('Small',parent=BODY,fontSize=9,leading=13,spaceAfter=4)
H1=ParagraphStyle('H1',parent=BODY,fontName='CNB',fontSize=16,leading=23,spaceAfter=10,keepWithNext=True)
H2=ParagraphStyle('H2',parent=BODY,fontName='CNB',fontSize=11.5,leading=17,spaceBefore=8,spaceAfter=5,keepWithNext=True)
HCODE=ParagraphStyle('HCode',parent=H2,keepWithNext=False)
LINK=ParagraphStyle('Link',parent=SMALL,fontName='Mono',fontSize=8.8,leading=12,wordWrap='CJK')
audit={'code_blocks':0,'code_visual_lines':0,'wrapped_comment_lines':0,'overflow':[],'missing_glyphs':set()}

def esc(s):return html.escape(text(str(s))).replace('\n','<br/>')
def para(s,style=BODY):return Paragraph(esc(s),style)
def rich(s,style=BODY):return Paragraph(s,style)
def text(s):
    return str(s).replace('\u2011','-').replace('\u2013','-').replace('\u2014',' - ').replace('\u200b','').replace('²','^2').replace('³','^3').replace('⁴','^4')
def font(c):
    if ord(c)<128:return 'Mono'
    if ord(c) in pdfmetrics.getFont('CN').face.charToGlyph:return 'CN'
    if ord(c) in pdfmetrics.getFont('Mono').face.charToGlyph:return 'Mono'
    audit['missing_glyphs'].add(c);return 'CN'
def width(s,size=9):return sum(pdfmetrics.stringWidth(c,font(c),size) for c in s)
def spans(s):
    res=[];p='';f=None
    for c in s:
        ff=font(c)
        if ff!=f:
            if p:res.append((f,p))
            f=ff;p=c
        else:p+=c
    if p:res.append((f,p))
    return res

class CodeListing(Flowable):
    font_size=9;leading=12
    def __init__(self,code=None,rows=None,continuation=False):
        Flowable.__init__(self);self.continuation=continuation
        if rows is None:
            audit['code_blocks']+=1;rows=[]
            for i,line in enumerate(code.expandtabs(4).splitlines(),1):
                line=text(line.rstrip());maxwidth=W-33
                if width(line)>maxwidth and line.lstrip().startswith('//'):
                    indent=line[:len(line)-len(line.lstrip())];rest=line.lstrip()[2:].lstrip();prefix=indent+'// '
                    first=True
                    while rest:
                        chunk='';j=0
                        while j<len(rest) and width(prefix+chunk+rest[j])<=maxwidth:chunk+=rest[j];j+=1
                        assert j>0
                        rows.append((i if first else None,prefix+chunk));rest=rest[j:];first=False
                        if rest:audit['wrapped_comment_lines']+=1
                else:
                    if width(line)>maxwidth+.5:audit['overflow'].append((i,line,width(line),maxwidth))
                    rows.append((i,line))
            audit['code_visual_lines']+=len(rows)
        self.rows=rows
    def wrap(self,availWidth,availHeight):
        self.width=availWidth;self.height=len(self.rows)*self.leading+12;return self.width,self.height
    def split(self,availWidth,availHeight):
        count=int((availHeight-12)//self.leading)
        if count<4:return []
        if count>=len(self.rows):return [self]
        # Keep an opening declaration/brace with at least two following lines.
        while count>=4 and any(self.rows[j][1].rstrip().endswith('{') for j in range(max(0,count-2),count)):
            count-=1
        if count<4:return []
        return [CodeListing(rows=self.rows[:count],continuation=self.continuation),CodeListing(rows=self.rows[count:],continuation=True)]
    def draw(self):
        c=self.canv;c.setFillColor(colors.HexColor('#f6f6f6'));c.rect(0,0,self.width,self.height,stroke=0,fill=1)
        c.setStrokeColor(colors.HexColor('#c0c0c0'));c.setLineWidth(.4);c.line(0,self.height,self.width,self.height);c.line(0,0,self.width,0)
        y=self.height-9-self.font_size
        for number,line in self.rows:
            if number is not None:
                c.setFont('Mono',6.8);c.setFillColor(colors.HexColor('#707070'));c.drawRightString(24,y,str(number))
            x=31;c.setFillColor(colors.HexColor('#151515'))
            for f,s in spans(line):c.setFont(f,self.font_size);c.drawString(x,y,s);x+=pdfmetrics.stringWidth(s,f,self.font_size)
            y-=self.leading

class Heading(Paragraph):
    def __init__(self,label,level,key):
        Paragraph.__init__(self,esc(label),H1 if level<=1 else H2);self.toc_level=level;self.key=key;self.plain=label

class HandbookDoc(BaseDocTemplate):
    def __init__(self,*args,**kwargs):
        super().__init__(*args,**kwargs);self.chapter='';self.entries={};self.pass_count=0
        frame=Frame(LM,BM,W,PAGE_H-TM-BM,id='body',leftPadding=0,rightPadding=0,topPadding=0,bottomPadding=0)
        self.addPageTemplates(PageTemplate(id='A4',frames=frame,onPage=self.page,onPageEnd=self.footer))
    def beforeDocument(self):self.chapter='';self.entries={};self.pass_count+=1
    def page(self,c,doc):
        c.saveState();c.setFont('CN',8);c.setFillColor(colors.HexColor('#505050'))
        if doc.page>1:c.drawString(LM,PAGE_H-12*mm,'ACM/ICPC 个人算法模板与例题手册')
        c.restoreState()
    def footer(self,c,doc):
        c.saveState();c.setFont('CN',8);c.setFillColor(colors.HexColor('#505050'))
        label=self.chapter
        while pdfmetrics.stringWidth(label,'CN',8)>W-30:label=label[:-1]
        c.drawString(LM,10*mm,label);c.setFont('Mono',9);c.drawRightString(PAGE_W-RM,10*mm,str(doc.page));c.restoreState()
    def afterFlowable(self,f):
        if isinstance(f,Heading):
            if f.toc_level<=1:self.chapter=f.plain
            self.canv.bookmarkPage(f.key);self.canv.addOutlineEntry(f.plain,f.key,level=f.toc_level,closed=f.toc_level==0)
            self.entries[f.key]={'title':f.plain,'page':self.page,'level':f.toc_level}
            self.notify('TOCEntry',(f.toc_level,f.plain,self.page,f.key))

topics=json.loads(CATALOG.read_text(encoding='utf-8'))
category_order=['数据结构','图论','数论','dp','杂','tirick'];category_name={'dp':'动态规划','杂':'字符串、线性代数与几何','tirick':'常用转化与技巧'}
topics.sort(key=lambda t:(category_order.index(t['category']), t['name']))
total_examples=sum(len(t['examples']) for t in topics);gaps=[t for t in topics if t.get('gap')]
results=json.loads((ROOT/'手册构建/compile_results.json').read_text(encoding='utf-8'))
assert len(results)==total_examples and all(r['compiled'] and not r.get('run_failed') for r in results)
random_results=json.loads((ROOT/'手册构建/random_results.json').read_text(encoding='utf-8'))
story=[]
cover=ParagraphStyle('Cover',parent=H1,fontSize=25,leading=36,alignment=1)
sub=ParagraphStyle('Sub',parent=BODY,fontSize=14,leading=23,alignment=1)
story+=[Spacer(1,48*mm),para('ACM/ICPC',cover),para('个人算法模板与例题手册',cover),Spacer(1,14*mm),para('poisonous-sheep / sheep-banzi',sub),para('C++17 · struct 封装 · 原有递归与命名风格',sub),Spacer(1,20*mm),para(f'{len(topics)} 个知识点  /  {total_examples} 份例题实现',sub),para('A4 黑白打印版  ·  2026-10-11',sub),Spacer(1,16*mm),para('本版保留两项例题数量缺口，详见下一页整理清单。代码已本地验证，未提交在线评测。',SMALL),PageBreak()]
story.append(Heading('阅读说明与整理清单',0,'guide'))
story.append(para('本手册汇合本地个人模板、课程复习笔记中的实际板子，以及 GitHub main 分支快照 76aca9130bef3b79f46fb6c88b5c929286c34d3f。旧文件保持原样；整理版独立归档。课程原始 PPT、视频、shareOI-master.zip 与无关软件目录按仓库维护规范保留，不自动作为个人板子导入。'))
story.append(para(f'实际收录 {len(topics)} 份完整模板、{total_examples} 份例题 solve；全部例题与依赖板子组合通过 g++ -std=c++17 -O2 编译。完成 {sum(r["sample_tests"] for r in results)} 次已登记样例或边界运行；另有 {len(random_results)} 组独立穷举/直接算法对拍，共 {sum(r["cases"] for r in random_results)} 例通过。样例和本地对拍不是在线 AC 记录。'))
story.append(para('模板中的 solve 采用该节第一例题或注明的演示输入。例题代码只展示 solve 与额外辅助代码，依赖本节完整板子；替换原 solve 后使用统一 signed main。多测一般在 solve 内读取 T，main 保持 t=1，避免重复读取。'))
story.append(para('有些例题是模板的明确变体：文中列出修改项；本地目录和构建数据保存了组合后的依赖版本。纸质版完整保留算法、转化说明和代码，不需要打开仓库才能阅读。'))
story.append(Heading('尚未满足或需复核的内容',1,'gaps'))
for t in gaps:story.append(para(t['name']+'：'+t['gap']))
story.append(para('代码源272/273原题无法访问，用户确认没有原题，已用 HDU5293、HDU4912、CF1675D、CF671D 建立对应例题。HDU题面经原站只读请求核实，CF题面经原站核实；课堂路径1是点不相交选择，路径2是非负费用祖先路径点覆盖，转换差异见对应章节。'))
story.append(para('数位构造 F1/F2 是同一原题的两档难度；LCM 单行求和两个题是同一公式的批量应用。两者明确注明，避免误认为不同模型。原资料仅顺带推荐、没有独立板子的其他题目不计为新增知识点；对应来源文件映射列在附录。'))
story.append(Heading('打印与使用',1,'print'))
story.append(para('A4 纵向，左侧预留 26 mm 装订边，右侧 18 mm。正文 10.2 pt，代码 9 pt；ASCII 代码使用 Consolas，中文注释使用内嵌仿宋。建议按实际大小打印；长代码保留连续行号，章节目录、书签及网址均可点击。'))
story.append(para('递归板子在长链图/树上需要足够栈空间；本册在对应章节写明风险。数组值域、模数条件、容量与费用乘积须符合每节限制，不能仅凭 #define int long long 假定所有乘积安全。'))
story.append(PageBreak());story.append(para('目录',H1))
toc=TableOfContents();toc.levelStyles=[ParagraphStyle('toc0',fontName='CNB',fontSize=11.5,leading=20,leftIndent=0,firstLineIndent=0,spaceBefore=6,wordWrap='CJK'),ParagraphStyle('toc1',fontName='CN',fontSize=9.6,leading=16,leftIndent=12,firstLineIndent=0,wordWrap='CJK'),ParagraphStyle('toc2',fontName='CN',fontSize=8.8,leading=14,leftIndent=24,firstLineIndent=0,wordWrap='CJK')]
story.append(toc)
for cat in category_order:
    story.append(PageBreak());story.append(Heading(category_name.get(cat,cat),0,'category_'+cat))
    for index,t in enumerate([t for t in topics if t['category']==cat],1):
        if index>1:story.append(CondPageBreak(250))
        key='topic_'+hashlib.sha256((cat+t['name']).encode()).hexdigest()[:12]
        story.append(Heading(f'{index:02d}  {t["name"]}',1,key))
        story.append(rich('<b>用途与条件：</b>'+esc(text(t['intro']))))
        story.append(rich('<b>复杂度：</b>'+esc(text(t['complexity']))))
        if t.get('gap'):story.append(rich('<b>待补：</b>'+esc(t['gap']),SMALL))
        story.append(CondPageBreak(68));story.append(para('完整 C++17 板子',HCODE));story.append(CodeListing(t['code']))
        story.append(para('接口与调用',H2))
        for name,desc in t['api']:story.append(rich(esc(name)+'：'+esc(text(desc)),SMALL))
        for ei,e in enumerate(t['examples'],1):
            story.append(Heading(f'例题 {ei}  {e["id"]}  {e["name"]}',2,key+'_'+str(ei)))
            story.append(rich('<b>所属知识点：</b>'+esc(t['name'])+'；<b>依赖：</b>'+esc(t['struct']),SMALL))
            story.append(rich('<link href="'+html.escape(e['url'],quote=True)+'" color="#202020">'+esc(e['url'])+'</link>',LINK))
            story.append(rich('<b>题意：</b>'+esc(text(e['description']))))
            story.append(rich('<b>为什么使用：</b>'+esc(text(e['why']))))
            story.append(rich('<b>如何调用：</b>'+esc(text(e['calls']))))
            if e.get('changes'):story.append(rich('<b>变体修改：</b>'+esc(text(e['changes']))))
            for old,new in e.get('replace',[]):
                story.append(para('以下合并语句从“原”改为“新”：',SMALL))
                story.append(CodeListing('// 原\n'+old+'\n// 新\n'+new))
            story.append(rich('<b>复杂度：</b>'+esc(text(e['complexity']))))
            story.append(CondPageBreak(68));story.append(para('solve 与必要辅助代码（配合本节板子）',HCODE));story.append(CodeListing(e['code']))
            story.append(para('验证：'+e.get('validation','组合编译通过；未在线提交')+'；来源：'+e.get('source_status','原题信息待复核'),SMALL))
        story.append(para('易错点与边界',H2))
        for p in t['pitfalls']:story.append(para('- '+text(p),SMALL))
        story.append(para('个人资料来源：'+'；'.join(t['sources']),SMALL))
        if t.get('validation'):story.append(para('板子状态：'+t['validation'],SMALL))

story.append(PageBreak());story.append(Heading('附录：原资料与整理知识点映射',0,'mapping'))
mapping={}
for t in topics:
    for s in t['sources']:mapping.setdefault(s,[]).append(t['name'])
for s,names in sorted(mapping.items()):story.append(para(s,H2));story.append(para('；'.join(names),SMALL))
story.append(PageBreak());story.append(Heading('附录：题号与网址索引',0,'problems'))
unique={}
for t in topics:
    for e in t['examples']:unique.setdefault(e['url'],(e['id'],e['name']))
for url,(id,name) in sorted(unique.items(),key=lambda x:x[1][0]):
    story.append(KeepTogether([para(id+'  '+name,SMALL),rich('<link href="'+html.escape(url,quote=True)+'" color="#202020">'+esc(url)+'</link>',LINK)]))

def check_paragraph_glyphs(items):
    for item in items:
        if isinstance(item,Paragraph):
            face=pdfmetrics.getFont(item.style.fontName).face
            for ch in item.getPlainText():
                if ch not in '\n\r\t' and ord(ch) not in face.charToGlyph:audit['missing_glyphs'].add(ch)
        elif isinstance(item,KeepTogether):check_paragraph_glyphs(item._content)
check_paragraph_glyphs(story)
assert not audit['missing_glyphs'],audit['missing_glyphs']
doc=HandbookDoc(str(TARGET),pagesize=A4,title='ACM/ICPC 个人算法模板与例题手册',author='poisonous-sheep',subject='C++17 竞赛模板、API、真实例题与本地验证',pageCompression=1)
doc.multiBuild(story,maxPasses=5)
assert not audit['overflow'],audit['overflow'][:10]
assert not audit['missing_glyphs'],audit['missing_glyphs']
audit['missing_glyphs']=[];audit.update(pages=doc.page,passes=doc.pass_count,topics=len(topics),examples=total_examples,output=str(TARGET),bookmarks=doc.entries)
(ROOT/'手册构建/pdf_build.json').write_text(json.dumps(audit,ensure_ascii=False,indent=2),encoding='utf-8')
print('Created PDF:',doc.page,'pages;',len(topics),'topics;',total_examples,'examples;',doc.pass_count,'TOC passes')
