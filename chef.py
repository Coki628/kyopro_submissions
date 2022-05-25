# 実行方法
# python chef.py 問題URL

import sys
import os
from subprocess import run
import shutil

args = sys.argv

url = args[1]
if url[-1] == '/':
    url = url[:-1]
contest_name = url.split('/')[-3]
problem_name = url.split('/')[-1]
project_root = os.getcwd()

os.chdir('{0}/codechef'.format(os.getcwd()))
os.makedirs(contest_name, exist_ok=True)
os.chdir('{0}/{1}'.format(os.getcwd(), contest_name))
os.makedirs(problem_name, exist_ok=True)
os.chdir('{0}/{1}'.format(os.getcwd(), problem_name))
if not os.path.exists('test'):
    run('oj download {0}'.format(url), shell=True, encoding='utf-8')
if os.path.exists('1.cpp'):
    print('1.ccp already exists')
else:
    shutil.copy(
        '{0}/_tools/templates/tpl-cf.cpp'.format(project_root),
        '{0}/1.cpp'.format(os.getcwd()),
    )
run('code 1.cpp', shell=True, encoding='utf-8')
