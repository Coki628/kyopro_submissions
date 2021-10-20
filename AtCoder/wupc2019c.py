# -*- coding: utf-8 -*-

"""
・WA
・まあそのうちやろう。
"""

import sys

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

N,M=MAP()
nodes=[[] for i in range(N)]
for i in range(M):
    u,v=MAP()
    nodes[u-1].append(v-1)
    nodes[v-1].append(u-1)

def search(u, l):
    for v in l:
        for vv in nodes[v]:
            if not used[vv]:
                ans[u]=vv+1
                used[vv]=True
                return

ans=[0]*N
used=[False]*N
for u in range(N):
    for v in nodes[u]:
        if not used[v]:
            ans[u]=v+1
            used[v]=True
            break
    else:
        search(u, nodes[u])
print(*ans)
