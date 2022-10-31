# 提出用ビルドを生成する
# python submit-build.py file_dir_name file_base_name

import sys
import os
from subprocess import run, PIPE

args = sys.argv

home = os.path.expanduser('~')
file_dirname = args[1]
cpp_filename = args[2]

# 拡張子をojと合わせる(winならexe、それ以外でout)
ext = 'exe' if os.name == 'nt' else 'out'
# 落ちた時、前のやつ実行されると紛らわしいので消しておく
if os.path.exists('{0}/a.exe'.format(file_dirname)):
    os.remove('{0}/a.exe'.format(file_dirname))
# 提出用ビルド
run(
    [
        # 参考：https://atcoder.jp/contests/APG4b/rules?lang=ja
        'g++', '-O2', '-Wall', '-Wextra',
        # デバッグしたいのでoj-bundle前の元ファイル
        '{0}/{1}'.format(file_dirname, cpp_filename), '-std=c++17',
        # ライブラリのパス(こちらもdistではなくsrcから)
        '-I', '{0}/repos/kyopro_library/src'.format(home),
        # ACLのパス
        '-I', '{0}/repos/kyopro_library/ac-library'.format(home),
        '-o', '{0}/a.{1}'.format(file_dirname, ext),
    ],
    encoding='utf-8',
)
