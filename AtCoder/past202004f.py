# -*- coding: utf-8 -*-

"""
・優先度付きキュー、スケジュール管理
"""

import sys
from heapq import heappush, heappop

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
AB = [[] for i in range(N)]
for _ in range(N):
    a, b = MAP()
    a -= 1
    AB[a].append(b)

que = []
ans = 0
for i in range(N):
    for b in AB[i]:
        heappush(que, -b)
    ans += -heappop(que)
    print(ans)
