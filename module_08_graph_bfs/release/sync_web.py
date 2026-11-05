"""Mirror Chapter 8 readings and the student release into a website checkout."""
import argparse
from pathlib import Path
import subprocess
import sys
import tempfile
import zipfile


def main():
    module = Path(__file__).resolve().parent.parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--web-root', type=Path,
                        default=module.parent / 'student-textbook-web')
    web = parser.parse_args().web_root.resolve()
    if not (web / 'package.json').is_file():
        parser.error('--web-root must identify the existing textbook website')

    protected = {'lab.c', 'ppt.md', 'ppt_lab.md', 'ppt_material.md', 'ppt_lab_material.md'}
    files = {}
    for language, filename in [('en', 'textbook.md'), ('ko', 'textbook_korean.md')]:
        files[web / 'content' / f'chapter-eight.{language}.md'] = (
            module / 'student' / filename).read_bytes()
    with tempfile.TemporaryDirectory(prefix='chapter08-web-') as temporary:
        archive = Path(temporary) / 'sources.zip'
        subprocess.run([sys.executable, str(module / 'release/prepare_student_release.py'),
                        '--output', str(archive)], check=True)
        files[web / 'public/chapter-8/sources.zip'] = archive.read_bytes()
        with zipfile.ZipFile(archive) as package:
            prefix = 'module_08_graph_bfs/'
            for name in package.namelist():
                if name.startswith(prefix):
                    relative = Path(name[len(prefix):])
                    if relative.is_absolute() or '..' in relative.parts:
                        raise ValueError('Unexpected release member path')
                    files[web / 'public/chapter-8' / relative] = package.read(name)
    # Existing protected copies are read-only too. Fail before writing any file.
    for destination, data in files.items():
        if destination.name in protected and destination.exists():
            if destination.read_bytes() != data:
                raise RuntimeError(f'Read-only source differs: {destination}')
    count = 0
    for destination, data in files.items():
        if destination.exists() and destination.read_bytes() == data:
            continue
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(data)
        count += 1
    print(f'Synchronized {count} Chapter 8 website files into {web}')


if __name__ == '__main__':
    main()
