from pathlib import Path
import json, re, textwrap
import sys
if hasattr(sys.stdout,'reconfigure'):sys.stdout.reconfigure(encoding='utf-8')
from urllib.parse import quote

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / '手册构建/catalog.json'
HEADER = '#include <bits/stdc++.h>\nusing namespace std;\n#define int long long\n\n'
MAIN = '''signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
'''

def clean(s):
    return textwrap.dedent(s).strip()+'\n'

def example(id, name, url, description, why, calls, complexity, code, *, changes='', replace=None, tests=None):
    return dict(id=id,name=name,url=url,description=description,why=why,calls=calls,complexity=complexity,code=clean(code),changes=changes,replace=replace or [],tests=tests or [],source_status='待原题核实',validation='待组合编译')

def add(category,name,struct,body,intro,complexity,api,pitfalls,sources,examples,demo=None,gap=''):
    assert (2 <= len(examples) <= 3) or (gap and len(examples)<=1),(name,len(examples))
    folder=ROOT/category/'整理版'/name
    folder.mkdir(parents=True,exist_ok=True)
    (folder/'例题').mkdir(exist_ok=True)
    body=clean(body)
    for e in examples:
        e['file']='例题/'+re.sub(r'[<>:"/\\|?*]','-',e['id']+'-'+e['name'])+'.cpp'
        comments=['// 依赖：../模板.cpp；本文件为代码片段，替换模板 solve 后编译。', '// '+e['id']+' '+e['name'], '// 原题：'+e['url'], '// 所属知识点：'+name+'；使用模板：'+struct, '// 题意：'+e['description'], '// 转化：'+e['why'], '// 调用：'+e['calls'], '// 复杂度：'+e['complexity']]
        if e['changes']: comments.append('// 变体修改：'+e['changes'])
        (folder/e['file']).write_text('\n'.join(comments)+'\n'+e['code'],encoding='utf-8')
    if demo is None:
        demo=examples[0]['code']
        assert not examples[0]['replace'],name
    code=HEADER+'// '+name+'：'+intro+'\n// '+complexity+'\n'+body+'\n'+clean(demo)+'\n'+MAIN
    (folder/'模板.cpp').write_text(code,encoding='utf-8')
    topic=dict(category=category,name=name,struct=struct,path=folder.relative_to(ROOT).as_posix(),intro=intro,complexity=complexity,api=api,pitfalls=pitfalls,sources=sources,body=body,code=code,examples=examples,gap=gap,validation='待编译与运行验证')
    topics=json.loads(CATALOG.read_text(encoding='utf-8')) if CATALOG.exists() else []
    topics=[t for t in topics if (t['category'],t['name'])!=(category,name)]+[topic]
    CATALOG.write_text(json.dumps(topics,ensure_ascii=False,indent=2),encoding='utf-8')
    lines=['# '+name,'','**用途与条件：** '+intro,'','**复杂度：** '+complexity,'','[完整模板](模板.cpp)；模板 solve 使用基础例题的输入格式。','','## 接口','']+[ '- `'+k+'`：'+v for k,v in api ]+['','## 例题','']
    for e in examples:
        lines+=['### '+e['id']+' '+e['name'],'','原题：['+e['url']+']('+e['url']+')','', '**题意：** '+e['description'],'','**为什么使用：** '+e['why'],'','**调用步骤：** '+e['calls'],'','**复杂度：** '+e['complexity']]
        if e['changes']: lines+=['','**板子变体：** '+e['changes']]
        lines+=['','[完整 solve 及辅助代码]('+quote(e['file'],safe='/')+')；依赖模板，不能独立编译。','']
    lines+=['## 易错点','']+['- '+p for p in pitfalls]+['','## 来源与验证','','本知识点从以下已有个人资料整理；保留原稿，整理版为后续维护入口。']+['- `'+p+'`' for p in sources]+['','原题核实、组合编译与运行状态由构建脚本汇总；未提交在线评测，不标记AC。']
    if gap:lines[2:2]=['**未满足例题数量要求：** '+gap,'']
    (folder/'README.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')

def source_struct(path, name):
    s=(ROOT/path).read_text(encoding='utf-8-sig')
    start=s.index('struct '+name+' {')
    brace=s.index('{',start); depth=1; pos=brace+1
    while depth:
        if s[pos]=='{': depth+=1
        elif s[pos]=='}': depth-=1
        pos+=1
    return s[start:pos+1]
