"""
参考：http://mayokoex.hatenablog.com/entry/2016/02/29/170005
　　　https://suikaba.hatenablog.com/entry/2017/08/26/172626
・蟻本演習4-3-1
・強連結成分分解、DAG上でDP、メモ化再帰、ワーシャルフロイド
・むずい。TDPCみんなむずいよね。さすがにりんごさん。。
・まずDPするためにグラフの閉路を潰してDAGにする。ここではSCCをした後、辺を繋ぎ直してグラフを再構成する。
・2回の操作で、という条件があるので、通る頂点を重複して数えないように工夫する。
　具体的には、dp[i][j] := 頂点i,jからスタートして通れる最大数 みたいな形にして、
　i,jをそれぞれ遷移できる頂点に遷移させる。この時の条件として、
　「頂点i,jの間にある頂点には遷移できない」って考えると、自分的には分かりやすかった。
　そこを遷移先にしてしまうと、後で先の方にある頂点がもう1回そこを数えてしまう。
　これを条件としてまとめると、「頂点iからは行けて、頂点jには行けない頂点」には
　頂点iからの遷移が可能ということになる。jについてもその逆で理屈は同じ。
・さて、これをチェックするために、任意の頂点間について、DAGにした後のグラフでの到達可否を
　知らないといけないが、これはN^3がOKの制約なのでワーシャルフロイドが使える。
・最初TLEして、N=300で状態N^2遷移Nのメモ化再帰がきついのかと思ったら、
　どうやらN^3のワーシャルフロイドの方っぽい。INFを10^19から10^18にしたらpypyAC1.00秒。
　2^63-1にしてWF内にif文つけてINFをオーバーしないようにしたら1.66秒。
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
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

def SCC(N, edges):
    """ 強連結成分分解 """

    nodes1 = [[] for i in range(N)]
    nodes2 = [[] for i in range(N)]
    for u, v in edges:
        nodes1[u].append(v)
        nodes2[v].append(u)

    T = []
    visited = [False] * N
    def rec1(cur):
        visited[cur] = True
        for nxt in nodes1[cur]:
            if not visited[nxt]:
                rec1(nxt)
        T.append(cur)

    for u in range(N):
        if not visited[u]:
            rec1(u)

    visited = [False] * N
    group = [0] * N
    grpnum = 0
    def rec2(cur):
        group[cur] = grpnum
        visited[cur] = True
        for nxt in nodes2[cur]:
            if not visited[nxt]:
                rec2(nxt)

    for u in reversed(T):
        if not visited[u]:
            rec2(u)
            grpnum += 1
    return grpnum, group

def warshall_floyd(graph: list) -> list:
    """ ワーシャルフロイド(頂点数, 隣接行列(0-indexed)) """
    from copy import deepcopy

    N = len(graph)
    res = deepcopy(graph)
    for i in range(N):
        res[i][i] = 0
    for k in range(N):
        for i in range(N):
            for j in range(N):
                res[i][j] = min(res[i][j], res[i][k] + res[k][j])
    for i in range(N):
        if res[i][i] < 0:
            return []
    return res

N = INT()
G = [[] for i in range(N)]
for i in range(N):
    G[i] = LIST()

edges = []
for i in range(N):
    for j in range(N):
        if G[i][j]:
            edges.append((i, j))

grpcnt, group = SCC(N, edges)

vgroup = [[] for i in range(N)]
for i in range(N):
    g = group[i]
    vgroup[g].append(i)
G2 = list2d(N+1, N+1, INF)
for i in range(N):
    for j, v in enumerate(vgroup[i][1:], 1):
        u = vgroup[i][j-1]
        G2[u][v] = 1
for a, b in edges:
    ga, gb = group[a], group[b]
    if ga == gb:
        continue
    u = vgroup[ga][-1]
    v = vgroup[gb][0]
    G2[u][v] = 1
for i in range(N):
    G2[N][i] = 1

wf = warshall_floyd(G2)

memo = list2d(N+1, N+1, -1)
def rec(u1, u2):
    if memo[u1][u2] != -1:
        return memo[u1][u2]
    res = 0
    for v in range(N):
        if v != u1 and wf[u1][v] < INF and not wf[v][u2] < INF:
            res = max(res, rec(v, u2) + 1)
        if v != u2 and wf[u2][v] < INF and not wf[v][u1] < INF:
            res = max(res, rec(u1, v) + 1)
    memo[u1][u2] = res
    return res

ans = rec(N, N)
print(ans)
