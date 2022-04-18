# -*- coding: utf-8 -*-

import sys
from collections import Counter

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
    N = INT()
    A = LIST()

    B = []
    tmp = [A[0]]
    pos = 0
    if A[0] > 0:
        pos = 1
    for i in range(1, N):
        if pos and A[i] < 0 or not pos and A[i] > 0:
            pos = 1 - pos
            B.append(tmp)
            tmp = [A[i]]
        else:
            tmp.append(A[i])
    B.append(tmp)
    
    ans = 0
    for li in B:
        ans += max(li)
    print(ans)
