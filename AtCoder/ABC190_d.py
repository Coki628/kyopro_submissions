"""
参考：https://twitter.com/ui_mtc/status/1355512044137500672
　　　https://oeis.org/A054844
・自力ならず。。数学問つらいね。
・実験、OEIS
・実験してみて、適当に1〜50項くらいを検索かけるとピタリ一致するやつが出る。
　「Nの奇数の約数の2倍」とあるので、その通りにやると合う。
・公式解とかみんなもっと賢く式変形したりできるみたいだけど、
　自分でそのプロセスを導ける筋道は見えてこない。
　今回はFに時間割いてこれ後回しにしたのもあったけど、もし本気で自分が解くつもりなら、
　こっちの方針が現実的だろう、と思って実験+OEISで通しておいた。
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
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

# cnt = [0] * 100
# for i in range(-100, 100):
#     for j in range(i+1, 100):
#         cur = 0
#         for x in range(i, j):
#             cur += x
#         if 0 <= cur < 100:
#             cnt[cur] += 1
# print(cnt[1:])

def divisors(N: int) -> set:
    """ 約数の列挙・個数 """
    from math import sqrt

    s = {1, N}
    for i in range(2, int(sqrt(N))+1):
        if N % i == 0:
            s.add(i)
            s.add(N // i)
    return s

N = INT()

ans = 0
for div in divisors(N):
    if div % 2 == 1:
        ans += 1
ans *= 2
print(ans)
