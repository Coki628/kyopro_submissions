# -*- coding: utf-8 -*-

"""
・いざ、改めてやってみるも、自力WA。。
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
sys.setrecursionlimit(10 ** 9)
INF = 10 ** 18
MOD = 10 ** 9 + 7

N = INT()
ga, sa, ba = MAP()
gb, sb, bb = MAP()

if ga > gb:
    ga, gb = gb, ga
if sa > sb:
    sa, sb = sb, sa
if ba > bb:
    ba, bb = bb, ba

ans = N
for x in range(N+1):
    for y in range(N+1):
        z = N - x - y
        if z < 0:
            break
        cnt = 0
        d, m = divmod(x, ga)
        cnt += d * gb + m
        d, m = divmod(y, sa)
        cnt += d * sb + m
        d, m = divmod(z, ba)
        cnt += d * bb + m
        ans = max(ans, cnt)
print(ans)
