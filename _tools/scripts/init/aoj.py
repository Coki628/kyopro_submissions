# 実行方法
# python aoj.py 問題URL

import sys
import os
from subprocess import run
import shutil
from urllib import parse

args = sys.argv

url = args[1]
if url[-1] == '/':
    url = url[:-1]

contest_type = url.split('/')[3]
contest_name = '{0}_{1}'.format(url.split('/')[-3], url.split('/')[-2])
if contest_type == 'courses':
    problem_name = url.split('/')[-1]
elif contest_type == 'challenges':
    # 参考：https://stackoverflow.com/questions/21584545/url-query-parameters-to-dict-python/44310775
    params = dict(parse.parse_qsl(parse.urlsplit(url).query))
    if 'year' not in params:
        print('no year info found')
        exit()
    contest_name += '_{0}'.format(params['year'])
    problem_name = parse.urlsplit(url).path.split('/')[-1]
project_root = os.getcwd()

os.chdir('{0}/AOJ'.format(os.getcwd()))
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
        '{0}/_tools/templates/tpl-small.cpp'.format(project_root),
        '{0}/1.cpp'.format(os.getcwd()),
    )
run('code 1.cpp', shell=True, encoding='utf-8')
