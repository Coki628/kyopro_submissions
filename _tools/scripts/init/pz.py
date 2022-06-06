# 実行方法
# python pz.py 問題URL

import sys
import os
from subprocess import run
import shutil

args = sys.argv

url = args[1]
if url[-1] == '/':
    url = url[:-1]
problem_name = url.split('/')[-2]
project_root = os.getcwd()

os.chdir('{0}/paiza'.format(os.getcwd()))
os.makedirs(problem_name, exist_ok=True)
os.chdir('{0}/{1}'.format(os.getcwd(), problem_name))
if os.path.exists('1.cpp'):
    print('1.ccp already exists')
else:
    shutil.copy(
        '{0}/_tools/templates/tpl-pz.cpp'.format(project_root),
        '{0}/1.cpp'.format(os.getcwd()),
    )
run('code 1.cpp', shell=True, encoding='utf-8')
