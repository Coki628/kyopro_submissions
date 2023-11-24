"""
参考：https://stackoverflow.com/questions/31795109/decimal-quantize-raises-invalidoperation
・誤差対策
・先にやろうとしてた、小数のままやる方針。
　quantizeで小数部の表示桁数を指定するも、提出ではREになり、手元でd=100と試すと、
　InvalidOperationなるエラーが出る。が、詳細は分からず。
　で方針を変えたんだけど、「decimal quantize InvalidOperation」でググったら普通に答えが出た。
　getcontext().precでの精度指定よりも大きい桁数を指定するとこうなるらしい。
　で、この精度指定は整数部も含めるので、今回は整数部3桁+max(d)の100桁を考慮して、
　精度103桁で提出すると、問題なくACした。
　このくらいは手際よくその場で調べて解決できないとダメだねー。。
"""

import sys
from decimal import Decimal, getcontext

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

getcontext().prec = 103

d = INT()
a = Decimal(input())
b = Decimal(input())

ans = str((a + b).quantize(Decimal('1.' + '0' * d)))
print(ans)
