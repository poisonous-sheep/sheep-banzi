from common import *
import subprocess
FORMAT='C:/Program Files/LLVM/bin/clang-format.exe'
STYLE='{BasedOnStyle: LLVM, IndentWidth: 4, ColumnLimit: 88, BreakBeforeBraces: Attach, AllowShortIfStatementsOnASingleLine: Never, AllowShortLoopsOnASingleLine: false, AllowShortFunctionsOnASingleLine: Empty, AllowShortBlocksOnASingleLine: Never, SortIncludes: Never, ReflowComments: false}'
def fmt(s):
    p=subprocess.run([FORMAT,'--style='+STYLE],input=s.encode('utf-8'),capture_output=True,check=True)
    return p.stdout.decode('utf-8')
topics=json.loads(CATALOG.read_text(encoding='utf-8'))
for t in topics:
    # Apply example text replacements BEFORE formatting: replacement strings are literal.
    for e in t['examples']:
        body=t['body']
        for a,b in e['replace']:
            assert a in body,(t['name'],a);body=body.replace(a,b)
        e['combined_body']=fmt(body)
        e['code']=fmt(e['code'])
        path=ROOT/t['path']/e['file'];old=path.read_text(encoding='utf-8');comments=old[:old.index(e['code'].splitlines()[0])] if e['code'].splitlines()[0] in old else '\n'.join(x for x in old.splitlines() if x.startswith('// '))+'\n'
        path.write_text(comments+e['code'],encoding='utf-8')
    t['body']=fmt(t['body']);t['code']=fmt(t['code']);(ROOT/t['path']/'模板.cpp').write_text(t['code'],encoding='utf-8')
    if t['name']=='Kruskal重构树':t['complexity']='排序O(m log m)，仅路径压缩的并查集按O((n+m)log n)保守估计，倍增O(n log n)；空间O(n log n+m)。'
CATALOG.write_text(json.dumps(topics,ensure_ascii=False,indent=2),encoding='utf-8')
print('Formatted',len(topics),'templates and',sum(len(t['examples']) for t in topics),'example snippets at 88 columns')
