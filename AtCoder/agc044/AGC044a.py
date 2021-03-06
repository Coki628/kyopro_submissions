"""
・なんとか自力AC
・グラフに帰着、整数ダイクストラ、逆操作
・計算量は公式解によると、15万くらいらしいので、それにlog乗った感じ。
・なんかみんなの話だとDFSでも解けるっぽい？そのうち要確認かな。
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
INF = 10 ** 19
MOD = 10 ** 9 + 7

def dijkstra(src):
    from heapq import heappush, heappop

    que = [(0, src)]
    dist = {}
    dist[src] = 0
    while que:
        cost, u = heappop(que)
        if u >= 5:
            x = u % 5
            v = (u-x) // 5
            if v not in dist or cost+c+d*x < dist[v]:
                dist[v] = cost+c+d*x
                heappush(que, (cost+c+d*x, v))
            if u % 5 != 0:
                x = 5 - u % 5
                v = (u+x) // 5
                if v not in dist or cost+c+d*x < dist[v]:
                    dist[v] = cost+c+d*x
                    heappush(que, (cost+c+d*x, v))
        if u >= 3:
            x = u % 3
            v = (u-x) // 3
            if v not in dist or cost+b+d*x < dist[v]:
                dist[v] = cost+b+d*x
                heappush(que, (cost+b+d*x, v))
            if u % 3 != 0:
                x = 3 - u % 3
                v = (u+x) // 3
                if v not in dist or cost+b+d*x < dist[v]:
                    dist[v] = cost+b+d*x
                    heappush(que, (cost+b+d*x, v))
        if u >= 2:
            x = u % 2
            v = (u-x) // 2
            if v not in dist or cost+a+d*x < dist[v]:
                dist[v] = cost+a+d*x
                heappush(que, (cost+a+d*x, v))
            if u % 2 != 0:
                x = 2 - u % 2
                v = (u+x) // 2
                if v not in dist or cost+a+d*x < dist[v]:
                    dist[v] = cost+a+d*x
                    heappush(que, (cost+a+d*x, v))
    return dist

for _ in range(INT()):
    N, a, b, c, d = MAP()

    res = dijkstra(N)
    ans = INF
    for u, cost in res.items():
        ans = min(ans, cost+abs(u)*d)
    print(ans)
