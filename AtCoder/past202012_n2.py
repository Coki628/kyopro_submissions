"""
・時間かかったけど自力AC？問題公開されたら投げてみる。
・クエリ系、ダブリングLCA、二分探索
・考えたらこれでもできる気がして作ってみた。ダブリングで各パス間のLの最大とRの最小を求める。
　辺がちゃんとグラフと対応してる分、セグ木でやる方よりやりやすかった。
　→制約4秒あるのにTLE。。C++でAC。
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

def bisearch_min(mn, mx, func):
    """ 条件を満たす最小値を見つける二分探索 """

    ok = mx
    ng = mn
    while ng+1 < ok:
        mid = (ok+ng) // 2
        if func(mid):
            ok = mid
        else:
            ng = mid
    return ok

def bisearch_max(mn, mx, func):
    """ 条件を満たす最大値を見つける二分探索 """

    ok = mn
    ng = mx
    while ok+1 < ng:
        mid = (ok+ng) // 2
        if func(mid):
            ok = mid
        else:
            ng = mid
    return ok

def dfs(N, nodes, src):
    """ DFS(木、スタック、重みあり) """

    stack = [(src, -1, 0, -1, -1)]
    while stack:
        u, prev, depth, prevl, prevr = stack.pop()
        depths[u] = depth
        nxt[0][u] = prev
        L[0][u] = prevl
        R[0][u] = prevr
        for v, l, r in nodes[u]:
            if v != prev:
                stack.append((v, u, depth+1, l, r))

N, Q = MAP()
nodes = [[] for i in range(N)]
for i in range(N-1):
    l, r = MAP()
    nodes[i].append((i+1, l, r))
    nodes[i+1].append((i, l, r))

MX = 18
nxt = list2d(MX+1, N, -1)
L = list2d(MX+1, N, -1)
R = list2d(MX+1, N, -1)
depths = [-1] * N
dfs(N, nodes, 0)

for k in range(1, MX+1):
    for v in range(N):
        if nxt[k-1][v] == -1:
            continue
        nxt[k][v] = nxt[k-1][nxt[k-1][v]]
        L[k][v] = max(L[k-1][v], L[k-1][nxt[k-1][v]])
        R[k][v] = min(R[k-1][v], R[k-1][nxt[k-1][v]])

def get_mnmx(a, b):
    if depths[a] > depths[b]:
        a, b = b, a
    gap = depths[b] - depths[a]
    mx = 0
    mn = INF
    for i in range(MX+1):
        if gap>>i & 1:
            mx = max(mx, L[i][b])
            mn = min(mn, R[i][b])
            b = nxt[i][b]
    if a == b:
        return mn, mx
    else:
        for i in range(MX, -1, -1):
            a2 = nxt[i][a]
            b2 = nxt[i][b]
            if a2 != b2:
                mx = max(mx, L[i][a], L[i][b])
                mn = min(mn, R[i][a], R[i][b])
                a = a2
                b = b2
        if a != b:
            mx = max(mx, L[0][a], L[0][b])
            mn = min(mn, R[0][a], R[0][b])
        return mn, mx

# Lの最大がval以下でRの最小がval以上ならその区間は通れる
def check(m):
    mn, mx = get_mnmx(x, m)
    return mx <= val and mn >= val

for _ in range(Q):
    val, x = MAP()
    x -= 1

    l = bisearch_min(-1, x, check)
    r = bisearch_max(x, N, check)
    res = r-l+1
    print(res)
