"""
・C++ライブラリ圧縮
・_srcに格納されたC++のライブラリを圧縮して_distに出力する。
"""

import os
import glob
import shutil

from _lib.python.tools.compresscpp import compress

libdir = '_lib{0}cpp{0}_src'.format(os.sep)

for path in glob.glob('{0}{1}**'.format(libdir, os.sep), recursive=True):
    # 整形したくないファイルがあればここで
    # if path.endswith('xxx'):
    #     shutil.copy(path, path.replace('_src', '_dist', 1))
    if os.path.isdir(path):
        # 該当フォルダがなければ作成
        os.makedirs(path.replace('_src', '_dist', 1), exist_ok=True)
    elif os.path.isfile(path) and path.endswith('.hpp'):
        compress(path, path.replace('_src', '_dist', 1))
