"""
・負数MODがめんどいので先にpythonで試してみたやつ。
・こっちも問題なくACしてるけど、20万のNでgcdのlog乗って0.78秒。やっぱ遅いね。
　これは制約2秒でよかったけど、こどふぉは制約1秒全然あるし、極力C++で行った方がいい。
"""

import sys
from math import gcd

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
INF = 2**63 - 1
MOD = 10**9 + 7
EPS = 10**-10

for _ in range(INT()):
    N, K = MAP()
    A = LIST()

    g = 0
    for i in range(N-1):
        g = gcd(g, abs(A[i]-A[i+1]))
    if A[0]%g == K%g:
        YES()
    else:
        NO()
