"""
・oj-bundleの出力を自分好みに整形する。
"""

import os

path_r = '{0}/_dist/main.cpp'.format(os.getcwd())
path_w = '{0}/_dist/main.cpp'.format(os.getcwd())

out = []
with open(path_r, encoding='utf-8') as f:
    lines = f.readlines()
    n = len(lines)
    has_comment_lines = False
    i = 0
    while i < n:
        # 最初のコメント行を非表示
        if i == 1 and lines[i].startswith('/*'):
            has_comment_lines = True
            i += 1
            continue
        if has_comment_lines:
            if lines[i].startswith('*/'):
                has_comment_lines = False
                i += 1
            i += 1
            continue
        # oj-bundleの行表示を非表示
        if lines[i].startswith('#line '):
            i += 1
            continue
        out.append(lines[i])
        i += 1

with open(path_w, mode='w', encoding='utf-8') as f:
    f.write(''.join(out))
