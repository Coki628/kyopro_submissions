"""
・さくっと自力AC！
・枝刈り全探索
・N以下で冪乗になる方を調べて全体から引く。冪乗はすぐでかくなるので、全部調べても大丈夫。
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

se = set()
for a in range(2, N+1):
    if a**2 > N:
        break
    for b in range(2, N+1):
        if a**b > N:
            break
        se.add(a**b)

ans = N - len(se)
print(ans)
