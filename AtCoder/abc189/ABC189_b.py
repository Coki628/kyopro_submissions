""" 
・さくっと自力AC
・多分誤差ゲー。確認はしてないけど、普通に小数でやると落とすケースあるってTLで言ってた。
　100倍するとも言ってたけど、こういう時pythonのDecimalは信用できる。(遅いけど。。)
"""

import sys
from decimal import Decimal

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

N, X = MAP()
cur = Decimal(0)
for i in range(N):
    v, p = map(Decimal, input().split())
    cur += v*p/100
    if cur > X:
        print(i+1)
        exit()
print(-1)
