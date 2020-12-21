"""
・これは誤差をカバーするため、floatをやめてFractionを使ったもの。
・計算量がテストケース100に100^2=100万くらいやるのがきつくてTLE。。。制約1秒とかやめてほしい。
"""

import sys
from fractions import Fraction

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c for j in range(b)] for i in range(a)]
def list3d(a, b, c, d): return [[[d for k in range(c)] for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e for l in range(d)] for k in range(c)] for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(N=None): return list(MAP()) if N is None else [INT() for i in range(N)]
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
INF = 10**19
MOD = 10**9 + 7
EPS = 10**-10

for _ in range(INT()):
    N, K = MAP()
    A = LIST()

    A.sort()
    ans = 0
    for i in range(N):
        for j in range(i, N):
            ans += Fraction(A[j], (j+1))
    if ans == K:
        YES()
    else:
        NO()
