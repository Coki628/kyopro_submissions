# -*- coding: utf-8 -*-

"""
・自力WA
"""

import sys
if sys.version_info.minor >= 5: from math import gcd
else: from fractions import gcd

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for j in range(c)] for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(N=None): return list(MAP()) if N is None else [INT() for i in range(N)]
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10 ** 9)
INF = 10 ** 18
MOD = 10 ** 9 + 7

X, Y = map(int, input().split('/'))

# 約分しておく
_gcd = gcd(X, Y)
if _gcd != 1:
    X //= _gcd
    Y //= _gcd

orgX, orgY = X, Y
while True:
    # 1からYの等差数列の和
    sm = (Y+1)*Y // 2
    M = sm - X
    # 最初からオーバーならこの先も無理
    if M > Y:
        print('Impossible')
        exit()
    # 今回の範囲にあるならそれを引けばいいから答え
    elif 0 < M <= Y:
        N = Y
        print(N, M)
        exit()
    # 足りなければ1つ先に進む
    X += orgX
    Y += orgY
