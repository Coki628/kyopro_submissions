"""
・きっちり自力AC！
・多倍長演算
"""

import sys

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

if N == 1:
    print(0)
else:
    N -= 1
    print(len(str(N)))
