from common import *
import subprocess, hashlib, concurrent.futures
topics=[t for t in json.loads(CATALOG.read_text(encoding='utf-8')) if t.get('has_template',True)];B=ROOT/'.work_review/handbook/standalone';B.mkdir(parents=True,exist_ok=True)
def work(t):
    code=t['code'];sha=hashlib.sha256(code.encode()).hexdigest();cpp=B/(sha[:16]+'.cpp');exe=cpp.with_suffix('.exe');cpp.write_text(code,encoding='utf-8')
    r=dict(topic=t['name'],sha256=sha,compiled=True,errors='')
    if not exe.exists():
        p=subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra',str(cpp),'-o',str(exe)],capture_output=True,timeout=90);r['compiled']=p.returncode==0;r['errors']=p.stderr.decode('utf-8',errors='replace')[-2500:]
    return r
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:result=list(pool.map(work,topics))
(ROOT/'手册构建/template_results.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
failed=[x for x in result if not x['compiled']];print('Standalone templates:',len(result),'passed:',len(result)-len(failed))
for x in failed:print(x['topic'],x['errors'])
sys.exit(bool(failed))
