"""
・なんとか自力AC。。
・誤差対策、多倍長
・想定はまあ文字列にして筆算やってくんだろうなって思ったけどPythonでDecimal。
　で、さくっとと思ったらそうも行かなかった。最初、小数のままやろうとしたら、
　小数部の表示桁数の調整がうまくいかず、仕方ないのでd桁ずらして整数にして、
　多倍長で整数足し算して文字列にして分割、みたいにしたんだけど、これでもWAになり合わず。
　原因は精度だった。整数にしてるから関係ないかと思ったけど、
　*10^dしてる所はまだ実数なので、ここで壊れるみたいだった。
　Decimalの精度指定をmax(d)の100桁まで上げたら通った。(確かデフォルトは60とかだったはず)
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

getcontext().prec = 100

d = INT()
a = Decimal(input())
b = Decimal(input())

a *= pow(10, d)
b *= pow(10, d)
s = str(int(a + b))
p = s[:-d]
q = s[-d:]
while len(q) < d:
    q += '0'
ans = '{0}.{1}'.format(p, q)
if ans[-1] == '.':
    ans = ans[:-1]
print(ans)
