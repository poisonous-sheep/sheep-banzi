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
TARGET=OUT/'ACM_ICPC_个人算法模板与思维训练手册.pdf'
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
        if doc.page>1:c.drawString(LM,PAGE_H-12*mm,'ACM/ICPC 个人算法模板与思维训练手册')
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

