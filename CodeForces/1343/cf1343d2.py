# -*- coding: utf-8 -*-

"""
・いもすを普通の形にした。やっぱこっちのがスッキリしてるな。
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
    N, K = MAP()
    A = LIST()

    B = [()] * (N//2)
    for i in range(N//2):
        j = N - i - 1
        if A[i] < A[j]:
            B[i] = (A[i], A[j])
        else:
            B[i] = (A[j], A[i])
    
    imos = [0] * (K*2+2)
    for a, b in B:
        # 操作0回でいける点
        sm = a + b
        imos[sm] += 1
        imos[sm+1] -= 1
        # 操作1回でいける区間
        lo = a + 1
        hi = K + b
        imos[lo] += 1
        imos[hi+1] -= 1
    imos = list(accumulate(imos))
    ans = N - max(imos)
    print(ans)
