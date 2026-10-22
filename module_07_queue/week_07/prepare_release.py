"""Build the bounded Week 7 release; never include faculty solutions."""
from pathlib import Path
from zipfile import ZipFile, ZIP_DEFLATED

base = Path(__file__).resolve().parent
names = ['README.md', 'textbook.md', 'lab.md', 'code/linked_queue.h',
         'code/support.h', 'code/support.c', 'code/starter/linked_queue.c',
         'code/tests/test_core.c', 'code/tests/test_student.c', 'code/Makefile']
files = {name: (base / name).read_bytes() for name in names}
# Remove repository-only faculty navigation from the release landing page.
files['README.md'] = b'''# Week 7 student release\n\nRead textbook.md and lab.md. Code and tests are in code/.\nImplement only enqueue and dequeue in code/starter/linked_queue.c.\nThe instructor supplies the circular-array reference separately.\nThis is one lab artifact; full general-list and circular-Queue labs are optional.\n'''
files['MANIFEST.txt'] = ('Week 7 linked Queue; two TODOs; no faculty solutions.\n' +
                         '\n'.join(sorted(files)) + '\n').encode()
out = base / 'dist/week_07_linked_queue.zip'
out.parent.mkdir(exist_ok=True)
with ZipFile(out, 'w', ZIP_DEFLATED) as archive:
    for name, data in sorted(files.items()):
        archive.writestr(name, data)
print(out)
