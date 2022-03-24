# 実行方法
# python ac.py 問題URL

import sys
import os
from subprocess import run

args = sys.argv

url = args[1]
if url[-1] == '/':
    url = url[:-1]
contest_name = url.split('/')[-3]
problem_name = url.split('/')[-1]
project_root = os.getcwd()

os.chdir('{0}/AtCoder'.format(os.getcwd()))
os.makedirs(contest_name, exist_ok=True)
os.chdir('{0}/{1}'.format(os.getcwd(), contest_name))
run(
    'oj-prepare --config-file {0}/_tools/oj-configs/prepare.config.ac.toml {1}'.format(project_root, url),
    shell=True, encoding='utf-8'
)
os.chdir('{0}/{1}'.format(os.getcwd(), problem_name))
run('code 1.cpp', shell=True, encoding='utf-8')
