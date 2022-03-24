# 提出用ファイルを生成してoj testする
# python oj-test.py file_dir_name file_base_name

import sys
import os
from subprocess import run, PIPE

args = sys.argv

home = os.path.expanduser('~')
file_dirname = args[1]
cpp_filename = args[2]

# distに最新のsrcを反映
run('python _tools/scripts/compresscpplib.py', shell=True, encoding='utf-8')
# 提出用ファイル_dist/main.cppの生成
run(
    [
        'oj-bundle',
        '{0}/{1}'.format(file_dirname, cpp_filename),
        # ライブラリのパス
        '-I', '{0}/repos/kyopro_library/dist'.format(home),
        # ACLのパス
        '-I', '{0}/repos/ac-library'.format(home),
        '>', '_dist/main.cpp'
    ],
    shell=True,
    encoding='utf-8',
    # 出力出さない
    stdout=PIPE,
    stderr=PIPE,
)
# 後始末と整形処理
run(
    'python _tools/scripts/finalize.py {0}/{1}'.format(file_dirname, cpp_filename),
    shell=True,
    encoding='utf-8'
)
# 提出用ビルド
run(
    [
        # 参考：https://atcoder.jp/contests/APG4b/rules?lang=ja
        'g++', '-O2', '-Wall', '-Wextra',
        # oj-bundle済の提出用ファイル
        '_dist/main.cpp', '-std=c++17',
        # ライブラリのパス
        '-I', '{0}/repos/kyopro_library/dist'.format(home),
        # ACLのパス
        '-I', '{0}/repos/ac-library'.format(home),
        '-o', '{0}/a.exe'.format(file_dirname),
    ],
    shell=True,
    encoding='utf-8',
)

os.chdir(file_dirname)
run('oj t', shell=True, encoding='utf-8')
