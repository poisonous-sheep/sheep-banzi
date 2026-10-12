from common import *
from pypdf import PdfReader
import subprocess, math, concurrent.futures, hashlib, os, shutil
from PIL import Image, ImageDraw, ImageFont
PDF=ROOT/'output/pdf/ACM_ICPC_个人算法模板与思维训练手册.pdf'
OUT=ROOT/'tmp/pdfs';OUT.mkdir(parents=True,exist_ok=True)
POP=os.environ.get('PDFTOPPM') or shutil.which('pdftoppm')
if not POP:
    bundled=Path.home()/'.cache/codex-runtimes/codex-primary-runtime/dependencies/native/poppler/Library/bin/pdftoppm.exe'
    assert bundled.exists(),'安装Poppler并加入PATH，或设置PDFTOPPM指向pdftoppm'
    POP=str(bundled)
for pattern in ('page-*.png','detail-*.png','contact-*.jpg'):
    for p in OUT.glob(pattern):
        assert p.resolve().is_relative_to(OUT.resolve());p.unlink()
reader=PdfReader(PDF);meta=json.loads((ROOT/'手册构建/pdf_build.json').read_text(encoding='utf-8'))
assert len(reader.pages)==meta['pages'];assert len(reader.pages)>200
links=0;fonts={};texts=[]
for i,page in enumerate(reader.pages,1):
    assert abs(float(page.mediabox.width)-595.2756)<.1 and abs(float(page.mediabox.height)-841.8898)<.1
    txt=page.extract_text();texts.append(txt);assert txt.strip(),i
    assert '\ufffd' not in txt,(i,'replacement glyph')
    assert re.search(r'\b'+str(i)+r'\b',txt),(i,'page number missing')
    for a in page.get('/Annots',[]):
        if a.get_object().get('/Subtype')=='/Link':links+=1
    for k,f in page['/Resources'].get('/Font',{}).items():
        f=f.get_object();name=str(f.get('/BaseFont'));desc=f.get('/FontDescriptor');fonts[name]=bool(desc and any(x in desc.get_object() for x in ('/FontFile','/FontFile2','/FontFile3')))
full='\n'.join(texts)
topics=json.loads(CATALOG.read_text(encoding='utf-8'))
for t in topics:
    assert t['name'] in full,t['name']
    for e in t['examples']:assert e['id'] in full,(t['name'],e['id'])
assert links>=sum(len(t['examples']) for t in topics)*2
assert any('consola' in x.lower() or 'Consolas' in x for x in fonts)
def outlines(items):
    for x in items:
        if isinstance(x,list):yield from outlines(x)
        else:yield x
out=list(outlines(reader.outline));assert len(out)==len(meta['bookmarks']),(len(out),len(meta['bookmarks']))
for x in out:
    p=reader.get_destination_page_number(x)+1
    assert any(v['title']==x.title and v['page']==p for v in meta['bookmarks'].values()),(x.title,p)

# Render every page, low resolution for contact sheets, plus selected pages at 130 dpi.
def render_range(start,end):
    stem=OUT/'page'
    subprocess.run([POP,'-f',str(start),'-l',str(end),'-r','38','-png',str(PDF),str(stem)],capture_output=True,check=True,timeout=120)
ranges=[(i,min(i+39,len(reader.pages))) for i in range(1,len(reader.pages)+1,40)]
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(lambda x:render_range(*x),ranges))
pages=sorted(OUT.glob('page-*.png'));assert len(pages)==len(reader.pages)
font=ImageFont.truetype('C:/Windows/Fonts/consola.ttf',15)
for j in range(0,len(pages),48):
    selected=pages[j:j+48];sheet=Image.new('RGB',(6*285,8*415),'#d8d8d8');draw=ImageDraw.Draw(sheet)
    for k,p in enumerate(selected):
        im=Image.open(p).convert('RGB');im.thumbnail((274,385));x=(k%6)*285+5;y=(k//6)*415+23;sheet.paste(im,(x,y));draw.text((x,y-20),str(j+k+1),font=font,fill='black')
    sheet.save(OUT/f'contact-{j//48+1:02}.jpg',quality=92)
selection=sorted(n for n in set([1,2,3,4,5,6,7,8,9,10,20,40,80,120,160,200,240,280,320,360,400,len(reader.pages)]+[x['page'] for x in meta['bookmarks'].values() if x['level']==0]) if n<=len(reader.pages))
for n in selection:subprocess.run([POP,'-f',str(n),'-l',str(n),'-r','130','-png','-singlefile',str(PDF),str(OUT/f'detail-{n:03}')],capture_output=True,check=True,timeout=60)
result=dict(edition='training-v2',pages=len(reader.pages),links=links,bookmarks=len(out),fonts=fonts,all_pages_rendered=len(pages),detail_pages=selection,sha256=hashlib.sha256(PDF.read_bytes()).hexdigest(),bytes=PDF.stat().st_size,layout_missing_glyphs=meta['missing_glyphs'],layout_overflow=meta['overflow'])
(ROOT/'手册构建/pdf_check.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
print('PDF QA:',len(reader.pages),'A4 pages;',links,'links;',len(out),'bookmarks;',len(pages),'pages rendered;',len(selection),'high-resolution details')
