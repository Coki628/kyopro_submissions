# -*- coding: utf-8 -*-

"""
・ダイクストラ高速化確認用
・heapqにタプル詰めないで値1つにする。
・pythonで0.05秒、pypyで0.1秒くらい速くなった。
"""

import sys
from heapq import heappush, heappop

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(): return list(map(int, input().split()))
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10 ** 9)
INF = float('inf')
MOD = 10 ** 9 + 7

def dijkstra(N: int, nodes: list, src: int) -> list:
    """ ダイクストラ(頂点数, 隣接リスト(0-indexed), 始点) """

    # 頂点[ある始点からの最短距離] (経路自体を知りたい時はここに前の頂点も持たせる)
    res = [INF] * N
    # スタート位置
    que = [src]
    res[src] = 0
    # キューが空になるまで
    while len(que) != 0:
        # 距離*N + 現在のノード
        cur = heappop(que)
        # ノードだけ取り出す
        cur %= N
        # 出発ノードcurの到着ノードでループ
        for nxt, cost in nodes[cur]:
            # 今回の経路のが短い時
            if res[cur] + cost < res[nxt]:
                res[nxt] = res[cur] + cost
                # 距離*N+ノード番号 の形でキューに詰める
                heappush(que, res[nxt]*N+nxt)
    # ノードsrcからの最短距離リストを返却
    return res

N,M,T=MAP()
A=LIST()
nodes1=[[] for i in range(N)]
nodes2=[[] for i in range(N)]
for i in range(M):
    a,b,c=MAP()
    nodes1[a-1].append((b-1, c))
    # 辺の向きが逆のグラフは帰りの経路に使える
    nodes2[b-1].append((a-1, c))

res1=dijkstra(N, nodes1, 0)
res2=dijkstra(N, nodes2, 0)

ans=0
for i in range(N):
    ans=max(ans, max(0, T-res1[i]-res2[i])*A[i])
print(ans)
