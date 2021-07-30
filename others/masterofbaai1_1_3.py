# -*- coding: utf-8 -*-

"""
・想定解は樹形図だったけど、競プロならこんなDPにしたい。
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

N, M = MAP()
NM = N + M

# dp[i][j] := 合計i匹、狼をj匹入れた状態の通り数
dp = list2d(NM+1, N+1, 0)
dp[0][0] = 1
for i in range(NM):
    for j in range(min(i+1, N+1)):
        # 全体と狼の差分で羊の数を出す
        k = i - j
        if k < 0:
            continue
        # 羊を入れる遷移
        if k+1 <= M:
            dp[i+1][j] += dp[i][j]
        # 狼を入れる遷移
        # 最初だけは例外的に狼が先行してもよくて、以降は羊の数以下のみ
        if j+1 <= N and (k == 0 and j == 0 or j+1 <= k):
            dp[i+1][j+1] += dp[i][j]
ans = dp[NM][M]
print(ans)
