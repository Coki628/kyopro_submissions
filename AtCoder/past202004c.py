# -*- coding: utf-8 -*-

"""
・グリッド
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

def build_grid(H, W, intv, _type, space=True, padding=False):
    if space:
        _input = lambda: input().split()
    else:
        _input = lambda: input()
    _list = lambda: list(map(_type, _input()))
    if padding:
        offset = 1
    else:
        offset = 0
    grid = list2d(H+offset*2, W+offset*2, intv)
    for i in range(offset, H+offset):
        row = _list()
        for j in range(offset, W+offset):
            grid[i][j] = row[j-offset]
    return grid

N = INT()
H, W = N, N * 2 -1
grid = build_grid(H, W, '.', str, space=0, padding=1)
directions = ((-1, -1), (-1, 0), (-1, 1))

for h in range(H, 0, -1):
    for w in range(1, W+1):
        if grid[h][w] == 'X':
            for dh, dw in directions:
                nh = h + dh
                nw = w + dw
                if grid[nh][nw] == '#':
                    grid[nh][nw] = 'X'

for i in range(1, H+1):
    print(''.join(grid[i][1:W+1]))
