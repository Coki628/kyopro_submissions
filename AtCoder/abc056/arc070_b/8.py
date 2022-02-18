# -*- coding: utf-8 -*-

"""
参考：https://img.atcoder.jp/arc070/editorial.pdf
・解説の解法2、WA
・直したいけどうまくいかん。なんか累積和とか取らなきゃいけないぽいのだが。。
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
INF = float('inf')
MOD = 10 ** 9 + 7

N, K = MAP()
A = [0] + LIST() + [0]

# 部分和DP
dp = list2d(N+2, K, 0)
dp[0][0] = 1
for i in range(1, N+1):
    for j in range(K):
        dp[i][j] |= dp[i-1][j]
        if j-A[i] >= 0:
            dp[i][j] |= dp[i-1][j-A[i]]

# Nについて後ろから同じDP
redp = list2d(N+2, K, 0)
redp[N+1][0] = 1
for i in range(N, 0, -1):
    for j in range(K):
        redp[i][j] |= redp[i+1][j]
        if j-A[i] >= 0:
            redp[i][j] |= redp[i+1][j-A[i]]

ans = 0
for i in range(1, N+1):
    # 今回の値A[i]を足してKに到達できるような部分和があれば、これは必要
    for j in range(max(0, K-A[i]), K):
        # 自分を除いた結果と比べるには、前から来て1つ前までと、後ろから来て1つ後までを合わせればいい
        if dp[i-1][j] or redp[i+1][j]:
            break
    else:
        ans += 1
print(ans)
