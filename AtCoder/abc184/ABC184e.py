"""
・自力AC！
・グリッドBFS、辺の追加
・ワープできるところ同士で行き来できる辺を張る。
　この時、同じワープゾーンに何回も入ったら無駄なので、
　1回通ったら使用済みみたいにする。
・単純にグリッドだけではないのでダイクストラしたくなるが、
　ワープもコスト1なのは変わらないので、BFSで大丈夫。
　(と願って投げた。計算量的にダイクストラはきついと思ったので。。)
・400万グリッドでpypyAC2.43秒。(制約3秒)
"""

import sys
from string import ascii_lowercase

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for k in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for k in range(c)] for k in range(b)] for i in range(a)]
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

def bfs(grid, src):
    """ BFS(グリッド、重みなし) """
    from collections import deque

    H, W = len(grid), len(grid[0])
    directions = ((1, 0), (-1, 0), (0, 1), (0, -1))
    dist = list2d(H, W, -1)
    que = deque()
    used = [0] * 26
    for h, w in src:
        que.append((h, w))
        dist[h][w] = 0
    while que:
        h, w = que.popleft()
        # アルファベットのマスだったら、ワープの遷移をする
        if grid[h][w] in ascii_lowercase and not used[ord(grid[h][w])-97]:
            # 何回もやらない
            used[ord(grid[h][w])-97] = 1
            for nh, nw in C[ord(grid[h][w])-97]:
                if grid[nh][nw] == '#':
                    continue
                if dist[nh][nw] != -1:
                    continue
                dist[nh][nw] = dist[h][w] + 1
                que.append((nh, nw))
        for dh, dw in directions:
            nh = h + dh
            nw = w + dw
            if grid[nh][nw] == '#':
                continue
            if dist[nh][nw] != -1:
                continue
            dist[nh][nw] = dist[h][w] + 1
            que.append((nh, nw))
    return dist

H, W = MAP()
grid = build_grid(H, W, '#', str)

C = [[] for i in range(26)]
s = (-1, -1)
g = (-1, -1)
for i in range(1, H+1):
    for j in range(1, W+1):
        if grid[i][j] in ascii_lowercase:
            C[ord(grid[i][j])-97].append((i, j))
        elif grid[i][j] == 'S':
            s = (i, j)
        elif grid[i][j] == 'G':
            g = (i, j)

res = bfs(grid, [s])
ans = res[g[0]][g[1]]
print(ans)
