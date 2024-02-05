"""
・自力ならず…。これ通るならちゃんともっと悪あがきすれば良かったな。
・多倍長演算
・多倍長で殴るは軽く試したら無理だったので、
　無理かと思ったら結構みんなこれで通していた。
　型変換をやめて、ループ半分にするだけで間に合った。。
・pythonの多倍長乗算はカラツバ法ってのを使っていて、
　N桁同士の掛け算の計算量はO(N^{log3 / log2})だそう。
参考：https://twitter.com/kiri8128/status/1753872490387112108
"""

import sys
from collections import Counter

# int<->str型変換の制限に対する対応
# see: https://qiita.com/taikis/items/1b6925088b15892b212c
if sys.version_info.minor >= 11 or \
        sys.version_info.minor == 10 and sys.version_info.micro >= 7 or \
        7 <= sys.version_info.minor <= 9 and sys.version_info.micro >= 14:
    sys.set_int_max_str_digits(0)

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
MOD = 998244353
EPS = 10**-10

N = INT()
A = LIST(N)

C = Counter(A)
ans = 0
for i in range(N):
    ans += C[A[i] * A[i]]
    for j in range(i + 1, N):
        ans += C[A[i] * A[j]] * 2
print(ans)
