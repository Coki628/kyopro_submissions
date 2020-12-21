# -*- coding: utf-8 -*-

"""
・自力WA
・これで1時間以上溶かして終了。。。。
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
    # 入力がスペース区切りかどうか
    if space:
        _input = lambda: input().split()
    else:
        _input = lambda: input()
    _list = lambda: list(map(_type, _input()))
    # 余白の有無
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

H, W, K = MAP()

grid = build_grid(H, W, '*', str, space=False, padding=True)

ans = list2d(H+2, W+2, -1)
cnt = 0
for i in range(1, H+1):
    for j in range(1, W+1):
        if grid[i][j] == '#':
            cnt += 1
            ans[i][j] = cnt
        else:
            ans[i][j] = 0

for i in range(1, H+1):
    for j in range(1, W+1):
        if ans[i][j] != 0:
            k, l = i, j
            while ans[k-1][j] == 0:
                k -= 1
            while ans[i][l-1] == 0:
                l -= 1
            for m in range(k, i+1):
                for n in range(l, j+1):
                    if m == k and n == l:
                        continue
                    if ans[m][n] == 0:
                        ans[m][n] = ans[i][j]
                    else:
                        break
                else:
                    pass
                break

for i in range(H, 0, -1):
    for j in range(W, 0, -1):
        if ans[i][j] != 0:
            k, l = i, j
            while ans[k+1][j] == 0:
                k += 1
            while ans[i][l+1] == 0:
                l += 1
            for m in range(i, k+1):
                for n in range(j, l+1):
                    ans[m][n] = ans[i][j]

for i in range(1, H+1):
    print(*ans[i][1:W+1])
