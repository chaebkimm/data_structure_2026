"""Materialize a bounded DSU/Kruskal release with complete Prim supplied."""
from pathlib import Path
from zipfile import ZipFile, ZIP_DEFLATED

base = Path(__file__).resolve().parent
mst = base.parent / 'code'
files = {name: (base / name).read_bytes() for name in
         ['textbook.md', 'lab.md', 'code/dsu.c', 'code/test_dsu.c', 'code/test_student.c']}
files['README.md'] = b'''# Week 13 student release\n\nRead textbook.md and lab.md; build from code/.\nComplete find and union in code/dsu.c and select_sorted_edges in\ncode/mst/starter/kruskal.c. All other functions are supplied.\nPrim is supplied reference/demo code and has no student TODOs.\nSubmit one DSU/Kruskal artifact including the integration checkpoint.\n'''
for path in (mst / 'include').glob('*.h'):
    files['code/mst/include/' + path.name] = path.read_bytes()
for name in ['undirected_edge_list.c', 'prim_frontier.c', 'mst_support.c']:
    files['code/mst/support/' + name] = (mst / 'support' / name).read_bytes()
files['code/mst/starter/kruskal.c'] = (mst / 'starter/kruskal.c').read_bytes()
files['code/mst/supplied/prim.c'] = (mst / 'solution/prim.c').read_bytes()
files['code/mst/tests/test_core.c'] = (mst / 'tests/test_core.c').read_bytes()
makefile = (base / 'code/Makefile').read_text()
a = makefile.index('# Repository mode.'); b = makefile.index('DSU_STUDENT', a)
makefile = makefile[:a] + 'MST_DIR = mst\n' + makefile[b:]
makefile = makefile.replace('$(MST_DIR)/solution/prim.c', '$(MST_DIR)/supplied/prim.c')
a = makefile.index('solution-core:'); b = makefile.index('student-tests:', a)
makefile = makefile[:a] + makefile[b:]
makefile = makefile.replace(' solution-core', '')
files['code/Makefile'] = makefile.encode()
files['MANIFEST.txt'] = ('Week 13 DSU/Kruskal; three TODOs. Prim supplied.\n' +
                         '\n'.join(sorted(files)) + '\n').encode()
out = base / 'dist/week_13_dsu_kruskal.zip'
out.parent.mkdir(exist_ok=True)
with ZipFile(out, 'w', ZIP_DEFLATED) as archive:
    for name, data in sorted(files.items()):
        archive.writestr(name, data)
print(out)
