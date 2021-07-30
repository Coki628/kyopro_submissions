# -*- coding: utf-8 -*-

"""
・想定解は樹形図だったけど、競プロならこんなDPにしたい。
"""

import sys

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

def popcount(i):
    return bin(i).count('1')

M = INT()
A = [0, 1, 2, 3]
N = len(A)

dp0 = list2d(M+1, 1<<N, 0)
dp1 = list2d(M+1, 1<<N, 0)
dp0[0][0] = 1
for i in range(M):
    for bit in range(1<<N):
        for j, a in enumerate(A):
            if bit>>j & 1:
                continue
            dp1[i+1][bit|1<<j] += dp1[i][bit]
            if a != 0:
                dp1[i+1][bit|1<<j] += dp0[i][bit]
ans = 0
for bit in range(1<<N):
    if popcount(bit) == M:
        ans += dp1[M][bit]
print(ans)
