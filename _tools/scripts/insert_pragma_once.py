"""
・#pragma onceがついてないやつに全部つける。
"""

import os
import glob

home = os.path.expanduser('~')
libdir = '{0}{1}repos{1}kyopro_library{1}src'.format(home, os.sep)

for path in glob.glob('{0}{1}**'.format(libdir, os.sep), recursive=True):
    if os.path.isfile(path) and path.endswith('.hpp'):
        output = []
        with open(path, encoding='utf-8') as f:
            for line in f.readlines():
                output.append(line)
        if len(output) and not output[0].startswith('#pragma once'):
            output.insert(0, '#pragma once\n')

        with open(path, mode='w', encoding='utf-8') as f:
            f.write(''.join(output))
