# デバッグビルドを生成する
# python debug-build.py file_dir_name file_base_name

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
# デバッグ用ビルド
run(
    [
        'g++', '-D=__DEBUG',
        '-g3', '-O0', '-Wall',
        '-fsanitize=address', '-fno-omit-frame-pointer',
        '-D_GLIBCXX_DEBUG', '-D_GLIBCXX_DEBUG_PEDANTIC',
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

# 参考：https://xn--kst.jp/blog/2019/08/29/cpp-comp/#%E3%82%B3%E3%83%B3%E3%83%91%E3%82%A4%E3%83%AB%E3%82%AA%E3%83%97%E3%82%B7%E3%83%A7%E3%83%B3%E3%81%A7%E5%A2%83%E7%95%8C%E3%83%81%E3%82%A7%E3%83%83%E3%82%AF
# 　　　https://codeforces.com/blog/entry/15547#comment-205104
# '-Wall', '-Wextra', '-pedantic', '-O2', '-Wshadow', '-Wformat=2', '-Wfloat-equal', '-Wconversion', '-Wlogical-op', '-Wshift-overflow=2', '-Wduplicated-cond', '-Wcast-qual', '-Wcast-align', '-D_GLIBCXX_DEBUG', '-D_GLIBCXX_DEBUG_PEDANTIC', '-D_FORTIFY_SOURCE=2', '-fsanitize=address', '-fsanitize=undefined', '-fno-sanitize-recover', '-fstack-protector',
