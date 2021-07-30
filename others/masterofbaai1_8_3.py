"""
・DPをした。最初と最後は白2連続もNGを見落としていたのでどのみちダメだった。。
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
INF = 10 ** 18
MOD = 10 ** 9 + 7

A = 10
B = 7
N = A + B

# 白0,黒1として、直近2回を00,01,10の3つで表す
dp = list3d(N+1, A+1, 3, 0)
# 最初は白黒どっちにも遷移できるように便宜上10にしておく
dp[0][0][2] = 1
for i in range(N):
    for j in range(A+1):
        # 白白 → 黒
        dp[i+1][j][1] += dp[i][j][0]
        if j+1 <= A:
            # 白黒 → 白
            dp[i+1][j+1][2] += dp[i][j][1]
            # 最初と最後は白2連続もNG
            if i != 1 and i != N-1:
                # 黒白 → 白
                dp[i+1][j+1][0] += dp[i][j][2]
        # 黒白 → 黒
        dp[i+1][j][1] += dp[i][j][2]
ans = dp[N][A][0] + dp[N][A][1] + dp[N][A][2]
print(ans)
