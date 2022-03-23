# デバッグビルドを生成する
# python debug-build.py file_dir_name file_base_name

import sys
import os
from subprocess import run, PIPE

args = sys.argv

home = os.path.expanduser('~')
file_dirname = args[1]
cpp_filename = args[2]

# デバッグ用ビルド
run(
    [
        'g++', '-D=__LOCAL', '-g3', '-O0', '-D_GLIBCXX_DEBUG', '-Wall',
        # デバッグしたいのでoj-bundle前の元ファイル
        '{0}/{1}'.format(file_dirname, cpp_filename), '-std=c++17',
        # ライブラリのパス(こちらもdistではなくsrcから)
        '-I', '_lib/cpp/_src',
        # ACLのパス
        '-I', '{0}/repos/ac-library'.format(home),
        '-o', '{0}/a.exe'.format(file_dirname),
    ],
    shell=True,
    encoding='utf-8',
)
