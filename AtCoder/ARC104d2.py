"""
・個数制限付き部分和DP、平均を総和にするテク、MOD累積和
・平均を総和にするテクのおかげで部分和に使える値が負数やら0も入ってしまっているので、
　遷移用のMOD累積和を作る時に、正負0で場合分けしてある。
・さすがにこの問題はこれでも計算量きつすぎるので、ここから先はC++で。
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
        acc = [0] * (MX+1)
        if A[i] == 0:
            for j in range(MX+1):
                dp[i+1][j] = dp[i][j]*(K+1)
                dp[i+1][j] %= MOD
        elif A[i] > 0:
            m = A[i]
            for j in range(MX+1):
                if 0 <= j-m:
                    acc[j] = acc[j-m] + dp[i][j]
                    acc[j] %= MOD
            for j in range(MX+1):
                k = max(j-m*(K+1), j%m)
                dp[i+1][j] = acc[j] - acc[k]
                dp[i+1][j] %= MOD
        else:
            m = -A[i]
            for j in range(MX, -1, -1):
                if j+m <= MX:
                    acc[j] = acc[j+m] + dp[i][j]
                    acc[j] %= MOD
            for j in range(MX+1):
                k = min(j+m*(K+1), MX//m*m)
                dp[i+1][j] = acc[j] - acc[k]
                dp[i+1][j] %= MOD

        # for j in range(MX+1):
        #     for k in range(K+1):
        #         if 0 <= j-A[i]*k <= MX:
        #             dp[i+1][j] += dp[i][j-A[i]*k]
        #             dp[i+1][j] %= MOD
    ans = (dp[N][MX//2] - 1) % MOD
    print(ans)
