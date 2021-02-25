"""
・自力AC！
・logに変換
・大小関係が分かればいいので、logに変換して冪乗の代わりに掛け算する。
・多倍長殴りに失敗(明らかにTLE)して、そのままpythonでやったけど、
　pythonならDecimal使っとけばより安心だったな。これでも通ったけど。
"""

import sys
from math import log

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for k in range(c)] for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(N=None): return list(MAP()) if N is None else [INT() for i in range(N)]
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

x, y = MAP()

xy = log(x)*y
yx = log(y)*x
if xy < yx-EPS:
    print('<')
elif xy-EPS > yx:
    print('>')
else:
    print('=')
