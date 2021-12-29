"""
・oj-bundleに読み込ませる前処理
"""

import os
import sys

args = sys.argv

path_r = args[1] + args[2]
path_w = '{0}/_dist/tmp.cpp'.format(os.getcwd())

out = []
with open(path_r, encoding='utf-8') as f:
    lines = f.readlines()
    for i, line in enumerate(lines):
        # 相対パス変更及び src -> dist
        if line.startswith('#include '):
            line = line.replace('../../../', '../')
            line = line.replace('_src', '_dist')  
        out.append(line)

with open(path_w, mode='w', encoding='utf-8') as f:
    f.write(''.join(out))
