"""
・自力AC
・グリッド頑張る重実装
・ぐるぐる回す。最初の縦横でやったとこも45度回転*4にした方が楽だったかもしれない。
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

def rot90(grid):
    """ グリッドを時計回りに90度回転 """
    H = len(grid)
    W = len(grid[0])
    res = list2d(W, H, 0)
    for i in range(H):
        for j in range(W):
            res[j][H-i-1] = grid[i][j]
    return res

H, W = MAP()
grid = [[]] * H
for i in range(H):
    grid[i] = input()
stamp = [[]] * H
for i in range(H):
    stamp[i] = input()

# 縦横切り替えて上下左右の余白を潰す
H2, W2 = H, W
for _ in range(2):
    idxl = 0
    for i in range(H2):
        if stamp[i].count('#'):
            break
        else:
            idxl = i + 1
    idxr = H2
    for i in range(H2-1, -1, -1):
        if stamp[i].count('#'):
            break
        else:
            idxr = i
    stamp = [list(row) for row in list(zip(*stamp))]
    H2, W2 = W2, H2
    for i in range(H2):
        stamp[i] = stamp[i][idxl:idxr]
    W2 = idxr - idxl

def check(h, w):
    for i in range(H2):
        for j in range(W2):
            if grid[h+i][w+j] == stamp[i][j] == '#':
                return False
    return True

# 45度回転させながら全位置に移動してチェックしていく
for _ in range(4):
    for i in range(H-H2+1):
        for j in range(W-W2+1):
            if check(i, j):
                Yes()
                exit()
    stamp = rot90(stamp)
    H2, W2 = W2, H2
No()
