"""Check actual delivered files and relative links against the compiled translation units."""
from common import *
from urllib.parse import unquote
import hashlib
topics=json.loads(CATALOG.read_text(encoding='utf-8'));byname={t['name']:t for t in topics}
def canonical(src):
    # Preserve strings/characters while dropping comments, so // inside strings stays intact.
    pat=r'"(?:\\.|[^"\\])*"|\x27(?:\\.|[^\x27\\])*\x27|//[^\n]*|/\*[\s\S]*?\*/'
    src=re.sub(pat,lambda m:'' if m.group().startswith(('//','/*')) else m.group(),src)
    for x in ['#include <bits/stdc++.h>','using namespace std;','#define int long long']:src=src.replace(x,'')
    return re.sub(r'\s+','',src)
def body(t):
    src=(ROOT/t['path']/'模板.cpp').read_text(encoding='utf-8')
    assert '\nvoid solve()' in src,t['name']
    return src.split('\nvoid solve()')[0]
checked=0
for t in topics:
    if t['has_template']:assert canonical((ROOT/t['path']/'模板.cpp').read_text(encoding='utf-8'))==canonical(t['code']),t['name']
    for e in t['examples']:
        src=(ROOT/t['path']/e['file']).read_text(encoding='utf-8')
        if e.get('full_code'):
            actual=''.join(body(byname[d]) for d in e.get('dependencies',[]))+src
            expected=e['full_code']
        else:
            dep=body(t)
            for old,new in e.get('replace',[]):
                assert old in dep,(t['name'],e['id'],old);dep=dep.replace(old,new)
            actual=dep+'\n'+src+'\n'+MAIN
            expected=HEADER+e.get('combined_body',t['body'])+'\n'+e['code']+'\n'+MAIN
        assert canonical(actual)==canonical(expected),(t['name'],e['id'],'physical file differs from compiled program')
        checked+=1
docs=[ROOT/'README.md',ROOT/'手册整理清单.md',ROOT/'手册验证记录.md',ROOT/'手册构建/README.md']+[ROOT/t['path']/'README.md' for t in topics]
links=0
for p in docs:
    for href in re.findall(r'(?<!\\)\]\(([^)]+)\)',p.read_text(encoding='utf-8')):
        if href.startswith(('https://','http://','#')):continue
        dest=p.parent/unquote(href)
        assert dest.exists(),(str(p),href)
        links+=1
print('Physical files match compiled units:',checked,'relative links:',links,'all exist')
