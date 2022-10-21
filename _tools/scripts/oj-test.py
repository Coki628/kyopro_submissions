# 提出用ファイルを生成してoj testする
# python oj-test.py file_dir_name file_base_name

import sys
import os
from subprocess import run, PIPE

args = sys.argv

home = os.path.expanduser('~')
file_dirname = args[1]
filename = args[2]

# python版
ext = filename.split('.')[-1]
if ext == 'py':
    os.chdir(file_dirname)
    run('oj test -c "python {0}"'.format(filename), shell=True, encoding='utf-8')
    exit()

# distに最新のsrcを反映
run('python _tools/scripts/compresscpplib.py', shell=True, encoding='utf-8')
# 提出用ファイル_dist/main.cppの生成
run(
    ' '.join([
        'oj-bundle',
        '{0}/{1}'.format(file_dirname, filename),
        # ライブラリのパス
        '-I', '{0}/repos/kyopro_library/dist'.format(home),
        # ACLのパス
        '-I', '{0}/repos/kyopro_library/ac-library'.format(home),
        '>', '_dist/main.cpp'
    ]),
    shell=True,
    encoding='utf-8',
    # 出力出さない
    stdout=PIPE,
    stderr=PIPE,
)
# 後始末と整形処理
run(
    'python _tools/scripts/finalize.py {0}/{1}'.format(file_dirname, filename),
    shell=True,
    encoding='utf-8'
)
# 拡張子をojと合わせる(winならexe、それ以外でout)
ext = 'exe' if os.name == 'nt' else 'out'
# 落ちた時、前のやつ実行されると紛らわしいので消しておく
if os.path.exists('{0}/a.{1}'.format(file_dirname, ext)):
    os.remove('{0}/a.{1}'.format(file_dirname, ext))
# 提出用ビルド
run(
    [
        # 参考：https://atcoder.jp/contests/APG4b/rules?lang=ja
        'g++','-D=__LOCAL', '-O2', '-Wall', '-Wextra',
        # oj-bundle済の提出用ファイル
        '_dist/main.cpp', '-std=c++17',
        '-o', '{0}/a.{1}'.format(file_dirname, ext),
    ],
    encoding='utf-8',
)
if not os.path.exists('{0}/a.{1}'.format(file_dirname, ext)):
    print('build command failed...')
    exit()
os.chdir(file_dirname)
# AHC
if os.path.exists('tools/in'):
    run('a.{0}'.format(ext), shell=True, encoding='utf-8')
else:
    run('oj test', shell=True, encoding='utf-8')
