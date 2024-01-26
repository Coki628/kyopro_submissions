# -*- coding: utf-8 -*-

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

N = INT()

A = [0] * N
for i in range(N*(N-1)//2):
    a, b, c, d = MAP()
    a -= 1; b -= 1
    if c > d:
        A[a] += 3
    elif c < d:
        A[b] += 3
    else:
        A[a] += 1
        A[b] += 1

A = [(a, i) for i, a in enumerate(A)]
# 番兵
A.append((INF, -1))
A.sort(reverse=1)

ans = [0] * N
for i, (a, idx) in enumerate(A[1:], 1):
    preva, previdx = A[i-1]
    # 同得点なら、1つ前と同じ値(順位)にする
    if a == preva:
        ans[idx] = ans[previdx]
    else:
        ans[idx] = i
[print(a) for a in ans]
