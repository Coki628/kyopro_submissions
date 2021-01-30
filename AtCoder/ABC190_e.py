"""
・BFSとTSP(巡回セールスマン)
・やや分かりにくくされてるけど、上記に帰着させると、ほぼ同じやつがPASTで出たことがある。(past202005m)
・その時のやつを、始点を全頂点にしたり、ちょこちょこっと変えると、通る。
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

def bfs(nodes, src):
    from collections import deque

    N = len(nodes)
    que = deque([src])
    dist = [INF] * N
    dist[src] = 0
    while que:
        u = que.popleft()
        for v in nodes[u]:
            if dist[v] != INF:
                continue
            dist[v] = dist[u] + 1
            que.append(v)
    return dist

N, M = MAP()
nodes = [[] for i in range(N)]
for i in range(M):
    a, b = MAP()
    a -= 1; b -= 1
    nodes[a].append(b)
    nodes[b].append(a)

K = INT()
T = [t-1 for t in LIST()]
atot = {}
ttoa = {}
for i, t in enumerate(T):
    atot[t] = i
    ttoa[i] = t

dist = [[]] * K
for i in range(K):
    dist[i] = bfs(nodes, ttoa[i])

dp = list2d(1<<K, K, INF)
for i in range(K):
    dp[1<<i][i] = 1
for bit in range(1, (1<<K)-1):
    for i in range(K):
        if not (bit>>i & 1):
            continue
        for j in range(K):
            if bit>>j & 1:
                continue
            dp[bit|1<<j][j] = min(dp[bit|1<<j][j], dp[bit][i] + dist[i][ttoa[j]])
ans = min(dp[-1])
if ans == INF:
    print(-1)
else:
    print(ans)
