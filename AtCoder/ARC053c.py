# -*- coding: utf-8 -*-

"""
・自力AC！
・ソートを工夫する貪欲
"""

import sys
from operator import itemgetter
from bisect import bisect_left

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
A = []
for i in range(N):
    a, b = MAP()
    A.append((a-b, a, b))

A.sort()
tmp, _, _  = zip(*A)
idx = bisect_left(tmp, 0)
# 下がるグループと上がるグループに分ける(真ん中はどっちでもいい)
B = A[idx:]
A = A[:idx]
# 下がるグループはなるべく上がり幅の小さいのから
A.sort(key=itemgetter(1))
# 上がるグループはなるべく下がり幅の大きいのから
B.sort(key=itemgetter(2), reverse=1)
A = A + B

mx = cur = 0
for _, a, b in A:
    cur += a
    mx = max(mx, cur)
    cur -= b
    mx = max(mx, cur)
print(mx)
