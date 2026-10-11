from common import *
import subprocess, hashlib, concurrent.futures, sys, threading, collections

BUILD=ROOT/'.work_review/handbook/build'
BUILD.mkdir(parents=True,exist_ok=True)
topics=json.loads(CATALOG.read_text(encoding='utf-8'))
RESULT=ROOT/'手册构建/compile_results.json'
old=json.loads(RESULT.read_text(encoding='utf-8')) if RESULT.exists() else []
cache={r['sha256']:r for r in old if r['compiled'] and not r.get('run_failed')}
locks=collections.defaultdict(threading.Lock)
jobs=[]
for t in topics:
    for e in t['examples']:
        body=e.get('combined_body',t['body'])
        if not e.get('combined_body'):
            for a,b in e['replace']:
                assert a in body,(t['name'],a)
                body=body.replace(a,b)
        code=HEADER+body+'\n'+e['code']+'\n'+MAIN
        sha=hashlib.sha256(code.encode()).hexdigest()
        jobs.append((t,e,code,sha))

def work(job):
    t,e,code,sha=job
    stem=BUILD/sha[:16];cpp=stem.with_suffix('.cpp');exe=stem.with_suffix('.exe')
    cpp.write_text(code,encoding='utf-8')
    r=dict(topic=t['name'],category=t['category'],example=e['id'],sha256=sha,exe=str(exe),compiled=False,sample_tests=0,errors='')
    with locks[sha]:
        if sha in cache and exe.exists():
            r.update(cache[sha]);r.update(topic=t['name'],category=t['category'],example=e['id'])
        else:
            p=subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra',str(cpp),'-o',str(exe)],capture_output=True,timeout=90)
            r['compiled']=p.returncode==0
            r['errors']=p.stderr.decode('utf-8',errors='replace')[-6000:]
            if r['compiled']:cache[sha]=r.copy()
    r['sample_tests']=0
    if r['compiled']:
        for case in e['tests']:
            data,expected=(case['input'],case['output']) if isinstance(case,dict) else case
            p=subprocess.run([str(exe)],input=data.encode(),capture_output=True,timeout=15)
            actual=p.stdout.decode().split();wanted=expected.split();matches=actual==wanted
            if isinstance(case,dict) and case.get('comparison')=='float':
                eps=case.get('tolerance',1e-6)
                matches=len(actual)==len(wanted) and all(abs(float(a)-float(b))<=eps*max(1,abs(float(b))) for a,b in zip(actual,wanted))
            if p.returncode or not matches:
                r['errors']='运行不符合预期：'+repr((data,expected,p.stdout.decode(errors='replace')[:800],p.stderr.decode(errors='replace')[:800]));r['run_failed']=True;break
            r['sample_tests']+=1
    return r

with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
    results=list(pool.map(work,jobs))
RESULT.write_text(json.dumps(results,ensure_ascii=False,indent=2),encoding='utf-8')
failed=[r for r in results if not r['compiled'] or r.get('run_failed')]
print('Topics:',len(topics),'combined programs:',len(results),'passed compile:',sum(r['compiled'] for r in results),'failed:',len(failed))
for r in failed:print(r['topic'].encode('unicode_escape').decode(),r['example'],r['errors'][-3500:])
sys.exit(bool(failed))
