"""
・個数制限付き部分和DP、平均を総和にするテク
・とりあえずこれは愚直書いて下準備。ここから内側のループを1つ減らす。
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
INF = 10**19
MOD = 10**9 + 7
EPS = 10**-10

N, K, MOD = MAP()

for x in range(1, N+1):
    A = list(range(1, N+1))
    for i in range(N):
        A[i] -= x

    MX = N*N*K*2
    dp = list2d(N+1, MX+1, 0)
    dp[0][MX//2] = 1
    for i in range(N):
        for j in range(MX+1):
            for k in range(K+1):
                if 0 <= j-A[i]*k <= MX:
                    dp[i+1][j] += dp[i][j-A[i]*k]
                    dp[i+1][j] %= MOD
    ans = dp[N][MX//2] - 1
    print(ans)
