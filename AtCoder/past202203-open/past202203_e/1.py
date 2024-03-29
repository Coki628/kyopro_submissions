"""
・pythonのdatetimeとtimedeltaでやる(こういうのC++でやる方法いつまでも分からないね)。
"""

import sys
from datetime import datetime, timedelta

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
sys.setrecursionlimit(10**6)
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

S = input()
y, m, d = map(int, S.split('/'))

dt = datetime(y, m, d)
while 1:
    s = dt.strftime('%Y%m%d')
    se = set(s)
    if len(se) <= 2:
        print(dt.strftime('%Y/%m/%d'))
        break
    dt += timedelta(days=1)
