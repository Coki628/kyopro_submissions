"""
・自力AC
・ソート
・0部分と数値部分で分ける。比較関数自作しようと思ったけどうまく組めなかったので、
　結局pythonの多倍長を信じてでかい値も数値として比較した。
"""

import sys
from operator import itemgetter

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

N = INT()
P = []
for i in range(N):
    s = input()
    m = len(s)
    i = 0
    while i < m and s[i] == '0':
        i += 1
    P.append((int(s[i:]) if s[i:] else 0, i))

P.sort(key=itemgetter(1), reverse=1)
P.sort(key=itemgetter(0))
for s, zero in P:
    ans = '0'*zero + (str(s) if s else '')
    print(ans)
