from pathlib import Path
import subprocess,sys
for name in sys.argv[1:]:
    p=Path(__file__).with_name(name+'.py')
    # Existing SCC has init/addedge/run/bel; do not invent a second API.
    s=p.read_text(encoding='utf-8')
    s=s.replace('SCC s(n);','SCC s;s.init(n);').replace('SCC sc(n);','SCC sc;sc.init(n);')
    p.write_text(s,encoding='utf-8')
    subprocess.run([sys.executable,str(p)],check=True)
