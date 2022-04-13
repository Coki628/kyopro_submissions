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
INF = float('inf')
MOD = 10 ** 9 + 7

H, W = MAP()
R = LIST()
C = LIST()

grid = list2d(H, W, '*')
for i in range(H):
    r = R[i]
    for j in range(W):
        if r == j:
            grid[i][j] = 'W'
            break
        else:
            grid[i][j] = 'B'
for j in range(W):
    c = C[j]
    for i in range(H):
        if c == i:
            if grid[i][j] == 'B':
                print(0)
                exit()
            grid[i][j] = 'W'
            break
        else:
            if grid[i][j] == 'W':
                print(0)
                exit()
            grid[i][j] = 'B'

cnt = 0
for i in range(H):
    cnt += grid[i].count('*')
print(pow(2, cnt, MOD))
