"""
・グリッドBFS応用
・pypyTLEでC++ACなのでそっちで。
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

def bfs(grid, grid2, src):
    """ BFS(グリッド、重みなし) """
    from collections import deque

    H, W = len(grid), len(grid[0])
    directions = ((-1, 0), (1, 0), (0, -1), (0, 1))
    dist = list2d(H, W, 0)
    que = deque()
    for h, w in src:
        que.append((h, w))
        dist[h][w] = 1
    while que:
        h, w = que.popleft()
        for i, (dh, dw) in enumerate(directions):
            nh = h + dh
            nw = w + dw
            if grid[nh][nw] == '#':
                continue
            if not grid2[nh][nw][i]:
                continue
            if dist[nh][nw]:
                continue
            dist[nh][nw] = 1
            que.append((nh, nw))
    return dist

H, W = MAP()
si, sj = MAP()
grid = build_grid(H, W, '#', str)

grid2 = list3d(H+2, W+2, 4, 1)
for i in range(1, H+1):
    for j in range(1, W+1):
        if grid[i][j] == '<':
            grid2[i][j] = [0] * 4
            grid2[i][j][3] = 1
        elif grid[i][j] == '>':
            grid2[i][j] = [0] * 4
            grid2[i][j][2] = 1
        elif grid[i][j] == '^':
            grid2[i][j] = [0] * 4
            grid2[i][j][1] = 1
        elif grid[i][j] == 'v':
            grid2[i][j] = [0] * 4
            grid2[i][j][0] = 1
res = bfs(grid, grid2, [(si, sj)])

ans = list2d(H+2, W+2, '#')
for i in range(1, H+1):
    for j in range(1, W+1):
        if grid[i][j] != '#':
            if res[i][j]:
                ans[i][j] = 'o'
            else:
                ans[i][j] = 'x'
for i in range(1, H+1):
    print(''.join(ans[i][1:W+1]))
