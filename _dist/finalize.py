"""
・oj-bundleの出力を自分好みに整形する。
"""

import os

path_r = '{0}/_dist/main.cpp'.format(os.getcwd())
path_w = '{0}/_dist/main.cpp'.format(os.getcwd())

out = []
with open(path_r, encoding='utf-8') as f:
    lines = f.readlines()
    has_comment_lines = False
    for i, line in enumerate(lines):
        # 最初のコメント行を非表示
        if i == 1 and line.startswith('/*'):
            has_comment_lines = True
            continue
        if has_comment_lines:
            if lines[i-1].startswith('*/'):
                has_comment_lines = False
            continue
        # oj-bundleの行表示を非表示
        if line.startswith('#line '):
            continue
        out.append(line)

with open(path_w, mode='w', encoding='utf-8') as f:
    f.write(''.join(out))
