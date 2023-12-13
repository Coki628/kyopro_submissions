"""
・さくっと自力AC
・耳DP
・先手番か後手番かを状態に持って前に進む。
"""

import sys

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c for j in range(b)] for i in range(a)]
def list3d(a, b, c, d): return [[[d for k in range(c)] for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e for l in range(d)] for k in range(c)] for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(N=None): return list(MAP()) if N is None else [INT() for i in range(N)]
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
INF = 10**19
MOD = 10**9 + 7
EPS = 10**-10

for _ in range(INT()):
    N = INT()
    A = LIST()

    dp0 = [INF] * (N+1)
    dp1 = [INF] * (N+1)
    dp0[0] = 0
    for i in range(N):
        dp1[i+1] = min(dp1[i+1], dp0[i] + A[i])
        dp0[i+1] = min(dp0[i+1], dp1[i])
        if i < N-1:
            dp1[i+2] = min(dp1[i+2], dp0[i] + A[i] + A[i+1])
            dp0[i+2] = min(dp0[i+2], dp1[i])
    ans = min(dp0[N], dp1[N])
    print(ans)
