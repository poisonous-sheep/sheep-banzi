from common import *
for p in Path(__file__).parent.glob('*.py'):
    if p.name == 'fix_constants.py':continue
    s=p.read_text(encoding='utf-8');r=s.replace('static const int INF=', 'static constexpr int INF=')
    if r!=s:p.write_text(r,encoding='utf-8')
topics=json.loads(CATALOG.read_text(encoding='utf-8'))
for t in topics:
    for key in ('body','code'):t[key]=t[key].replace('static const int INF=', 'static constexpr int INF=')
    (ROOT/t['path']/'模板.cpp').write_text(t['code'],encoding='utf-8')
CATALOG.write_text(json.dumps(topics,ensure_ascii=False,indent=2),encoding='utf-8')
