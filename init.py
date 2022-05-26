# 入口を1つにまとめた。
# 実行方法
# python init.py 問題URL (+他に引数があれば付ける)

import sys
import os
from subprocess import run
from urllib import parse

args = sys.argv

pr = parse.urlparse(args[1])
scripts_dir = '{0}/_tools/scripts/init/'.format(os.getcwd())

if pr.netloc == 'atcoder.jp':
    args[0] = '{0}ac.py'.format(scripts_dir)
    run('python {0}'.format(' '.join(args)), shell=True, encoding='utf-8')

elif pr.netloc == 'codeforces.com':
    args[0] = '{0}cf.py'.format(scripts_dir)
    run('python {0}'.format(' '.join(args)), shell=True, encoding='utf-8')

elif pr.netloc == 'onlinejudge.u-aizu.ac.jp':
    args[0] = '{0}aoj.py'.format(scripts_dir)
    run('python {0}'.format(' '.join(args)), shell=True, encoding='utf-8')

elif pr.netloc == 'www.codechef.com':
    args[0] = '{0}chef.py'.format(scripts_dir)
    run('python {0}'.format(' '.join(args)), shell=True, encoding='utf-8')

elif pr.netloc == 'leetcode.com':
    args[0] = '{0}leet.py'.format(scripts_dir)
    run('python {0}'.format(' '.join(args)), shell=True, encoding='utf-8')

elif pr.netloc == 'yukicoder.me':
    args[0] = '{0}yuki.py'.format(scripts_dir)
    run('python {0}'.format(' '.join(args)), shell=True, encoding='utf-8')

elif pr.nexloc == 'judge.yosupo.jp':
    args[0] = '{0}libc.py'.format(scripts_dir)
    run('python {0}'.format(' '.join(args)), shell=True, encoding='utf-8')

else:
    print('this contest site not supported...')
