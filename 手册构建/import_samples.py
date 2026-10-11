from common import *
import html
topics=json.loads(CATALOG.read_text(encoding='utf-8'))
sources={s['url']:s for s in json.loads((ROOT/'手册构建/source_results.json').read_text(encoding='utf-8'))}
def plain(s):return html.unescape(re.sub('<[^>]*>','',re.sub(r'<br\s*/?>','\n',s,flags=re.I))).strip()+'\n'
count=0
for t in topics:
    for e in t['examples']:
        rec=sources.get(e['url'],{})
        if not rec.get('statement_detected') or not rec.get('cache') or e['id'] in ('ABC350C','practice2_d'):continue
        s=(ROOT/rec['cache']).read_bytes().decode('gb18030' if 'hdu' in e['url'] else 'utf-8',errors='replace')
        inputs={};outputs={}
        for h,pre in re.findall(r'<h3[^>]*>(.*?)</h3>\s*(?:.*?)<pre[^>]*>(.*?)</pre>',s,re.S):
            name=plain(h)
            mi=re.search(r'(?:Sample Input|入力例)\s*(\d+)',name);mo=re.search(r'(?:Sample Output|出力例)\s*(\d+)',name)
            if mi:inputs[mi.group(1)]=plain(pre)
            if mo:outputs[mo.group(1)]=plain(pre)
        if 'hdu' in e['url']:
            mi=re.search(r'Sample Input</div>\s*<div[^>]*>(.*?)</div>',s,re.S);mo=re.search(r'Sample Output</div>\s*<div[^>]*>(.*?)</div>',s,re.S)
            if mi and mo:inputs['1']=plain(mi.group(1));outputs['1']=plain(mo.group(1))
        present={(x['input'],x['output']) if isinstance(x,dict) else tuple(x) for x in e['tests']}
        for key in sorted(inputs):
            if key not in outputs:continue
            a,b=inputs[key],outputs[key]
            if (a,b) in present:continue
            case=dict(input=a,output=b,provenance='原站官方样例'+key,url=e['url'])
            if e['id']=='ABC139F':case['comparison']='float';case['tolerance']=1e-6
            e['tests'].append(case);count+=1
CATALOG.write_text(json.dumps(topics,ensure_ascii=False,indent=2),encoding='utf-8')
print('Imported official sample cases:',count)
