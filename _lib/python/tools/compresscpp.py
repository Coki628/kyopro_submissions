"""
・C++ソースコード圧縮ツール
・読み込んだファイルの行頭のインデントを取り除いて、
　改行をスペース1個に置き換えて、1行のコードにして出力する。
"""

import os
import re

path_r = '{0}/in.cpp'.format(os.getcwd())
path_w = '{0}/out.cpp'.format(os.getcwd())

out = []
with open(path_r, encoding='utf-8') as f:
    for line in f.readlines():

        # 空行
        if line[0] == '\n':
            continue
        # コメント行
        if line.strip().startswith('//'):
            continue
        out.append(line.strip())

with open(path_w, mode='w', encoding='utf-8') as f:
    f.write(' '.join(out))
