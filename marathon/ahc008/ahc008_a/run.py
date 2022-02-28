# ローカルテスターでテスト一括実行
# 最初からn個
# python run.py c++ファイル名 n
# l個目からr個目まで[l,r)
# python run.py c++ファイル名 l r

import sys
import os
from subprocess import run, PIPE

args = sys.argv

# ビルドするc++ファイル
cpp_file = args[1]

# 実行テストケース
if len(args) == 3:
    _from = 0
    to = int(args[2])
else:
    _from = int(args[2])
    to = int(args[3])

home = os.path.expanduser('~')
file_dirname = os.getcwd()
os.chdir('../../../')
run('python compresscpplib.py', shell=True, encoding='utf-8')
run('python _dist/prepare.py {0}/ {1}'.format(file_dirname, cpp_file),
    shell=True,
    encoding='utf-8'
)
run(
    'oj-bundle {0}/_tmp.cpp -I _lib/cpp/_dist -I {1}/repos/ac-library > _dist/main.cpp'.format(
        file_dirname,
        home,
    ),
    shell=True,
    encoding='utf-8',
    # 出力出さない
    stdout=PIPE,
    stderr=PIPE,
)
run(
    'python _dist/finalize.py {0}/_tmp.cpp'.format(file_dirname),
    shell=True,
    encoding='utf-8'
)
run(
    'g++ -O2 -Wall -Wextra _dist/main.cpp -std=c++17 -I _lib/cpp/_dist -I {0}/repos/ac-library -o {1}/a.exe'.format(
        home,
        file_dirname,
    ),
    shell=True,
    encoding='utf-8',
    # 出力出さない
    stdout=PIPE,
    stderr=PIPE,
)

os.chdir(file_dirname)
os.chdir('{0}/tools'.format(os.getcwd()))
total = 0
for i in range(_from, to):
    print('run testcase {0}'.format(i))
    proc = run(
        'cargo run --release --bin tester ../a.exe < in/{0}.txt > out/{0}.txt'.format(str(i).zfill(4)),
        shell=True,
        encoding='utf-8',
        stdout=PIPE,
        stderr=PIPE,
    )
    # 合計スコアを算出
    outputs = proc.stderr.split('\n')
    try:
        score = int(outputs[-2].split()[2])
        print("{:,}".format(score))
        total += score
    except ValueError:
        print('ValueError')
        print(outputs)
print('total score is {0}'.format("{:,}".format(total)))
