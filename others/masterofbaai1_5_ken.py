"""
・手元でやって数でかすぎてバグったけど、コードに書いたらちゃんと合ってた。
・想定解はもっと頭いいやつだけど、これもO(K+N)で競プロなら通るよね。
"""

import sys
from math import factorial
from fractions import Fraction

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

def nCr(n, r):
    """ 事前テーブルなし組み合わせ簡易版 """
    from math import factorial

    if n < r: return 0
    # 10C7 = 10C3
    r = min(r, n-r)
    return factorial(n) // (factorial(r) * factorial(n-r))

N, K = 13, 7

ans = 0
# Kより前にi枚引く通り数、を0〜Kまで見る
for i in range(K):
    # Kより小さいK-1枚からi枚選ぶ * Kより前に引くi枚の並べ方 * Kより後で引く残りの並べ方
    ans += nCr(K-1, i) * factorial(i) * factorial(N-i-1)
# 全通りで割って確率にする
ans = Fraction(ans) / Fraction(factorial(N))
print(ans)
