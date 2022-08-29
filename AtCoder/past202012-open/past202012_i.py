"""
・自力AC！
・DAG、メモ化再帰
・題意のグラフはDAGになっているので、メモ化再帰で経路を辿る。
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

N, M, K = MAP()
H = LIST()
C = set(c-1 for c in LIST())
nodes = [[] for i in range(N)]
for i in range(M):
    a, b = MAP()
    a -= 1; b -= 1
    if H[a] < H[b]:
        nodes[b].append(a)
    else:
        nodes[a].append(b)

memo = [-1] * N
def dfs(u):
    if memo[u] != -1:
        return memo[u]
    res = INF
    for v in nodes[u]:
        res = min(res, dfs(v) + 1)
    if u in C:
        res = 0
    memo[u] = res
    return res

for u in range(N):
    if memo[u] == -1:
        dfs(u)
for ans in memo:
    if ans == INF:
        print(-1)
    else:
        print(ans)
