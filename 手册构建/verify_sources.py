from common import *
import urllib.request, concurrent.futures, hashlib, html, time
OUT=ROOT/'.work_review/handbook/sources';OUT.mkdir(parents=True,exist_ok=True)
topics=json.loads(CATALOG.read_text(encoding='utf-8'));urls=sorted(set(e['url'] for t in topics for e in t['examples']))
if len(sys.argv)>1:urls=[u for u in urls if sys.argv[1] in u]
def work(url):
    stem=OUT/hashlib.sha256(url.encode()).hexdigest()[:16];dest=stem.with_suffix('.html')
    try:
        req=urllib.request.Request(url,headers={'User-Agent':'Mozilla/5.0'})
        with urllib.request.urlopen(req,timeout=18) as r:body=r.read();status=r.status;ctype=r.headers.get('content-type','')
        dest.write_bytes(body)
        s=body.decode('gb18030' if 'hdu' in url else 'utf-8',errors='replace');title=re.search(r'<title[^>]*>(.*?)</title>',s,re.S|re.I);title=html.unescape(title.group(1).strip()) if title else ''
        statement=('問題文' in s or 'Problem Statement' in s or 'Problem Description' in s or 'problem-statement' in s or '题目描述' in s or 'problem_content' in s)
        usable=status==200 and statement and not('Just a moment...' in title or 'Access denied' in title)
        return dict(url=url,http_status=status,title=title,statement_detected=usable,bytes=len(body),cache=str(dest.relative_to(ROOT)),sha256=hashlib.sha256(body).hexdigest(),content_type=ctype)
    except Exception as ex:return dict(url=url,statement_detected=False,error=str(ex))
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:result=list(pool.map(work,urls))
if len(sys.argv)>1:
    old=json.loads((ROOT/'手册构建/source_results.json').read_text(encoding='utf-8'));done={r['url'] for r in result};result=[r for r in old if r['url'] not in done]+result
(ROOT/'手册构建/source_results.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
print('Unique primary URLs:',len(urls),'statement pages fetched:',sum(r['statement_detected'] for r in result),'unavailable or non-HTML:',sum(not r['statement_detected'] for r in result))
print('Non-HTML/unavailable IDs:',[u['url'].rsplit('/',1)[-1] for u in result if not u['statement_detected']])
