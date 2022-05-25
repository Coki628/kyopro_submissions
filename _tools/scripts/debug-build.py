# デバッグビルドを生成する
# python debug-build.py file_dir_name file_base_name

import sys
import os
from subprocess import run, PIPE

args = sys.argv

home = os.path.expanduser('~')
file_dirname = args[1]
cpp_filename = args[2]

# 落ちた時、前のやつ実行されると紛らわしいので消しておく
if os.path.exists('{0}/a.exe'.format(file_dirname)):
    os.remove('{0}/a.exe'.format(file_dirname))
# デバッグ用ビルド
run(
    [
        'g++', '-D=__DEBUG', '-g3', '-O0', '-D_GLIBCXX_DEBUG', '-Wall',
        # デバッグしたいのでoj-bundle前の元ファイル
        '{0}/{1}'.format(file_dirname, cpp_filename), '-std=c++17',
        # ライブラリのパス(こちらもdistではなくsrcから)
        '-I', '{0}/repos/kyopro_library/src'.format(home),
        # ACLのパス
        '-I', '{0}/repos/kyopro_library/ac-library'.format(home),
        '-o', '{0}/a.exe'.format(file_dirname),
    ],
    shell=True,
    encoding='utf-8',
)
