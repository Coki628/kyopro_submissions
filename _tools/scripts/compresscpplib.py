"""
・C++ライブラリ圧縮
・srcに格納されたC++のライブラリを圧縮してdistに出力する。
"""

import os
import glob
import shutil
from subprocess import run, PIPE

from compresscpp import compress

home = os.path.expanduser('~')
libdir = '{0}{1}repos{1}kyopro_library{1}src'.format(home, os.sep)

for path in glob.glob('{0}{1}**'.format(libdir, os.sep), recursive=True):
    if path.find('kyopro_library{0}dist'.format(os.sep)) != -1:
        continue
    # 整形したくないファイルがあればここで
    # if path.endswith('xxx'):
    #     shutil.copy(path, path.replace('_src', '_dist', 1))
    if os.path.isdir(path):
        # 該当フォルダがなければ作成
        os.makedirs(path.replace(
            'kyopro_library{0}src'.format(os.sep),
            'kyopro_library{0}dist'.format(os.sep),
            1,
        ), exist_ok=True)
    elif os.path.isfile(path) and path.endswith('.hpp'):
        # ACLはoj-bundleでtmpに展開してから圧縮
        if 'kyopro_library{0}src{0}acl'.format(os.sep) in path:
            run(
                ' '.join([
                    'oj-bundle',
                    path,
                    # ACLのパス
                    '-I', '{0}/repos/kyopro_library/ac-library'.format(home),
                    '>', '{0}.tmp'.format(path)
                ]),
                shell=True,
                encoding='utf-8',
                # 出力出さない
                stdout=PIPE,
                stderr=PIPE,
            )
            compress(
                '{0}.tmp'.format(path),
                path.replace(
                    'kyopro_library{0}src'.format(os.sep),
                    'kyopro_library{0}dist'.format(os.sep),
                    1,
                )
            )
            os.remove('{0}.tmp'.format(path))
        else:
            compress(
                path,
                path.replace(
                    'kyopro_library{0}src'.format(os.sep),
                    'kyopro_library{0}dist'.format(os.sep),
                    1,
                )
            )
