"""
・自力AC
・グリッドDFS、一筆書き、オイラー路
・制約が小さいので、DFSで経路全探索できる。
"""

import sys

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for k in range(c)] for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(N=None): return list(MAP()) if N is None else [INT() for i in range(N)]
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10**9)
INF = 10**19
MOD = 10**9 + 7
EPS = 10**-10

def build_grid(H, W, intv, _type, space=False, padding=True):
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

H, W = MAP()
grid = build_grid(H, W, '.', str)

N = 0
for i in range(1, H+1):
    N += grid[i].count('#')

visited = list2d(H+2, W+2, 0)
directions = ((1, 0), (-1, 0), (0, 1), (0, -1))
ans = []
def dfs(i, j, cnt):
    if cnt == N:
        return 1
    for di, dj in directions:
        ni, nj = i+di, j+dj
        if grid[ni][nj] == '.':
            continue
        if visited[ni][nj]:
            continue
        visited[ni][nj] = 1
        if dfs(ni, nj, cnt+1):
            ans.append((ni, nj))
            return 1
        visited[ni][nj] = 0
    return 0

for i in range(1, H+1):
    for j in range(1, W+1):
        if grid[i][j] == '#':
            visited = list2d(H+2, W+2, 0)
            visited[i][j] = 1
            if dfs(i, j, 1):
                ans.append((i, j))
                print(N)
                for a, b in ans:
                    print(a, b)
                exit()
