"""
・oj-bundleに読み込ませる前処理
※include pathで制御できるようになったので今はもう使ってない。
"""

import sys

args = sys.argv

path_r = args[1] + args[2]
path_w = args[1] + '_tmp.cpp'

out = []
with open(path_r, encoding='utf-8') as f:
    lines = f.readlines()
    for i, line in enumerate(lines):
        # src -> dist
        if line.startswith('#include'):
            line = line.replace('_src', '_dist')  
        out.append(line)

with open(path_w, mode='w', encoding='utf-8') as f:
    f.write(''.join(out))
