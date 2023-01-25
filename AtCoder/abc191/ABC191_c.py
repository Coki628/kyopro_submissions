"""
・なんとか自力AC！危なかった。。
・BFSで黒マスに対する入りの方向とマスを取っておく。
　で、隣り合って連続してるところを1つとして数える。
・でも実はもっと簡単で、4マスずつ見て、黒マスが1個か3個の場所を数える、でよかったみたい。。
　4マスセットで見る発想なかなか出ないよなぁ…。
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
sys.setrecursionlimit(10**6)
INF = 10**18
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
    visited = list2d(H, W, 0)
    res = []
    que = deque()
    for h, w in src:
        que.append((h, w))
        visited[h][w] = 1
    while que:
        h, w = que.popleft()
        for i, (dh, dw) in enumerate(directions):
            nh = h + dh
            nw = w + dw
            if grid[nh][nw] == '*':
                continue
            if visited[nh][nw]:
                continue
            if grid[nh][nw] == '#':
                # 縦横で場合分け
                if i < 2:
                    res.append((i, nh, nw))
                else:
                    res.append((i, nw, nh))
            else:
                visited[nh][nw] = 1
                que.append((nh, nw))
    return res

H, W = MAP()
grid = build_grid(H, W, '*', str)

res = bfs(grid, [(1, 1)])
res.sort()

M = len(res)
ans = 1
for i, (d, a, b) in enumerate(res[:-1]):
    d2, a2, b2 = res[i+1]
    if d == d2 and a == a2 and abs(b-b2) <= 1:
        continue
    ans += 1
print(ans)
