# -*- coding: utf-8 -*-

"""
・遅かった。
・三角形の性質
・1辺だけやたら長いのがあると三角形にならない。
　長い2つが同じ長さなら、残り1辺はどうでも大丈夫。
・よく考えたら分かったけど、こういうの何でみんな秒で分かるんだ。数学強すぎでしょ。。
"""

import sys
from itertools import accumulate

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
INF = 10 ** 18
MOD = 10 ** 9 + 7

for _ in range(INT()):
    a, b, c, d = MAP()

    print(b, c, c)
