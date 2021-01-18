"""
・期待値DP
・最近類題(past202012_k)をやったのでこっちでも同じ方法をやってみた。
　問題なくAC。やっぱりこの形がいい感じかな。
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

N = INT()
A = LIST()
MAX = 16

memo = [-1] * (1<<MAX)
def rec(S):
    if memo[S] != -1:
        return memo[S]
    if S == (1<<MAX)-1:
        return 0
    res = INF
    for i in range(1, MAX-1):
        cnt = 0
        exp = 1
        for j in range(i-1, i+2):
            if not S & (1<<j):
                # その先の期待値 * そうなる確率(1/3)
                exp += rec(S|(1<<j)) / 3
                cnt += 1
        if cnt:
            # 3箇所見た全体に「1回の遷移の総数/自己ループにならずに遷移する数」を掛ける
            exp *= 3 / cnt
            res = min(res, exp)
    memo[S] = res
    return res

ans = (1<<MAX) - 1
for a in A:
    ans ^= 1<<a
print(rec(ans))
