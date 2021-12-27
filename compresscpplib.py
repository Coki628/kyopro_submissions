"""
・C++ライブラリ圧縮
・_srcに格納されたC++のライブラリを圧縮して_distに出力する。
"""

import os
import glob

from _lib.python.tools.compresscpp import compress

libdir = '_lib{0}cpp{0}_src'.format(os.sep)

for path in glob.glob('{0}{1}**'.format(libdir, os.sep), recursive=True):
    if os.path.isdir(path):
        # 該当フォルダがなければ作成
        os.makedirs(path.replace('_src', '_dist', 1), exist_ok=True)
    elif os.path.isfile(path):
        compress(path, path.replace('_src', '_dist', 1))