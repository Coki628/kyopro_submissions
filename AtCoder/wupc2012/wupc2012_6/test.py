"""
・オーバーフローの疑いもして、Pythonもやった。
　変換ツールが思ったより優秀だったからあんま手では書き換えてない。
　これも同じ所でWAをする残念なやつ。
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

N = INT()
XY = []
for i in range(N):
    x, y = MAP()
    XY.append((x, y))

M = 1000
acc = list2d(M, M, 0)
has = list2d(M, M,  False)
for x, y in XY:
    acc[x][y] += 1
    has[x][y] = True
for i in range(M):
    for j in range(M-1):
        acc[i][j+1] += acc[i][j]
for j in range(M):
    for i in range(M-1):
        acc[i+1][j] += acc[i][j]

ans = 0
for i in range(N):
    x1, y1 = XY[i]
    for j in range(i+1, N):
        x2, y2 = XY[j]
        if x1 == x2 or y1 == y2: continue
        if not has[x1][y2] or not has[x2][y1]: continue
        if x1 > x2: x1, x2 = x2, x1
        if y1 > y2: y1, y2 = y2, y1
        sm = acc[x1][y1]-acc[x1][y2-1]-acc[x2-1][y1]+acc[x2-1][y2-1]
        if sm == 0:
            ans = max(ans, (x2-x1)*(y2-y1))
print(ans)
