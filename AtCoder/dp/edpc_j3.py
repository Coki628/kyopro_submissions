"""
・期待値DP
・最近類題(past202012_k)をやったのでこっちでも同じ方法をやってみた。
　問題なくAC。これはbitDPのやつじゃないし、最小値でもなく全体の期待値を求めるやつだけど、
　こういうタイプにも同じように適用できるね。
"""

import sys
from collections import Counter

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

N = INT()
A = LIST()
C = Counter(A)

# memo[i][j][k] := 1個残りがi個、2個残りがj個、3個残りがk個である状態にするまでの操作回数の期待値
memo = list3d(N+1, N+1, N+1, -1)
def rec(i, j, k):
    if memo[i][j][k] != -1:
        return memo[i][j][k]
    if i == j == k == 0:
        return 0
    exp = 1
    # その先の期待値 * そうなる確率(1/3)
    if i: exp += rec(i-1, j, k) * (i/N)
    if j: exp += rec(i+1, j-1, k) * (j/N)
    if k: exp += rec(i, j+1, k-1) * (k/N)
    # N箇所見た全体に「1回の遷移の総数/自己ループにならずに遷移する数」を掛ける
    exp *= N / (i+j+k)
    memo[i][j][k] = exp
    return exp

print(rec(C[1], C[2], C[3]))
