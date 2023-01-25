"""
・愚直シミュレーション
・2冪なので、計算量logくらいで済むやつ。
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

LOG = INT()
N = 2**LOG
A = [(a, i) for i, a in enumerate(LIST())]

cur = A[:]
while len(cur) > 3:
    nxt = []
    for i in range(0, len(cur), 2):
        if cur[i][0] > cur[i+1][0]:
            nxt.append(cur[i])
        else:
            nxt.append(cur[i+1])
    cur = nxt
if cur[0][0] < cur[1][0]:
    print(cur[0][1]+1)
else:
    print(cur[1][1]+1)
