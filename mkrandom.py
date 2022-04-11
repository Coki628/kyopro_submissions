# ランダムテスト自動生成
# ・既に該当問題の階層が作成済である前提
# ・愚直解用naive.cppも作成済である前提
# 実行方法
# python mkrandom.py 問題URL

import sys
import os
from subprocess import run

args = sys.argv

url = args[1]
if url[-1] == '/':
    url = url[:-1]
contest_name = url.split('/')[-3]
problem_name = url.split('/')[-1]
home = os.path.expanduser('~')

if url.find('atcoder') != -1:
    contest_site = 'AtCoder'
elif url.find('codeforces') != -1:
    contest_site = 'CodeForces'
elif url.find('codechef') != -1:
    contest_site = 'codechef'
else:
    print('contest site not found')
    exit()

# 問題の階層へ移動
os.chdir('{0}/{1}'.format(os.getcwd(), contest_site))
os.chdir('{0}/{1}'.format(os.getcwd(), contest_name))
os.chdir('{0}/{1}'.format(os.getcwd(), problem_name))
if not os.path.exists('generate.py'):
    # generate.pyを作成
    run(
        'oj-template -t generate.py {0} > generate.py'.format(url),
        shell=True, encoding='utf-8'
    )
print('update and save generate.py accordingly, then enter')
input()
print('input number of test cases that you want to generate, then enter')
num_of_testcases = int(input())
# ランダムテストケースの生成
run(
    'oj generate-input "python generate.py" {0}'.format(num_of_testcases),
    shell=True, encoding='utf-8'
)
# naive.cppのコンパイル
run(
    [
        'g++', '-O2', '-Wall', '-Wextra',
        '{0}/naive.cpp'.format(os.getcwd()), '-std=c++17',
        '-I', '{0}/repos/kyopro_library/dist'.format(home),
        '-I', '{0}/repos/ac-library'.format(home),
        '-o', '{0}/a.exe'.format(os.getcwd()),
    ],
    shell=True, encoding='utf-8',
)
# naive.cppでランダムテストケースの解を生成
run(
    'oj generate-output',
    shell=True, encoding='utf-8'
)
print('random test cases ready to run')
