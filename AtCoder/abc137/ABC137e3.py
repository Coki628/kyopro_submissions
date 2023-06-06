# -*- coding: utf-8 -*-

"""
・ライブラリ確認
・ベルマンフォード
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

def bellman_ford(N: int, edges: list, src: int) -> list:
    """ ベルマンフォード(頂点数, 辺集合(0-indexed), 始点) """

    # 頂点[ある始点からの最短距離] (経路自体を知りたい時はここに前の頂点も持たせる)
    res = [INF] * N
    res[src] = 0
    # 各辺によるコストの置き換えを頂点数N-1回繰り返す
    for _ in range(N-1):
        for u, v, cost in edges:
            # INFからは更新しない
            if res[u] == INF:
                continue
            if res[v] > res[u] + cost:
                res[v] = res[u] + cost
    tmp = res[:]
    # 負の閉路(いくらでもコストを減らせてしまう場所)がないかチェックする
    for _ in range(N-1):
        for u, v, cost in edges:
            if res[u] == INF:
                continue
            if res[v] > res[u] + cost:
                # 検出した負閉路はすぐに-INFにする
                res[v] = -INF
    for i in range(N):
        if tmp[i] != res[i]:
            res[i] = -INF
    return res

N, M, P = MAP()
edges = []
for i in range(M):
    a, b, c = MAP()
    a -= 1; b -= 1
    edges.append((a, b, P-c))

res = bellman_ford(N, edges, 0)

if res[N-1] != -INF:
    print(max(-res[N-1], 0))
else:
    print(-1)
