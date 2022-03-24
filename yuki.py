# 実行方法
# python yuki.py 問題URL

import sys
import os
from subprocess import run

args = sys.argv

url = args[1]
if url[-1] == '/':
    url = url[:-1]
problem_name = url.split('/')[-1]
project_root = os.getcwd()

os.chdir('{0}/yukicoder'.format(os.getcwd()))
run(
    'oj-prepare --config-file {0}/_tools/oj-configs/prepare.config.ac.toml {1}'.format(project_root, url),
    shell=True, encoding='utf-8'
)
os.chdir('{0}/{1}'.format(os.getcwd(), problem_name))
run('code 1.cpp', shell=True, encoding='utf-8')
