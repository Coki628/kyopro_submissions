"""
参考：http://w3e.kanazawa-it.ac.jp/math/category/kansuu/iroiro-kansu/henkan-tex.cgi?target=/math/category/kansuu/iroiro-kansu/ennohouteisiki.html
・自力ならず。。
・円の方程式、式変形、誤差
・ぱっと見、方針が生えなくて飛ばした。解いてる人少なかったし。
　でもTLの話聞いたあと冷静に見たらほぼ式変形するだけだった。。
・x位置を決め打てば、その円の上下のy位置も定まるので、その間を差分取って数える。
・普通は誤差対策で10000倍して解くみたいだけど、変換で頭バグりそうになったので、
　とりあえずDecimalで殴ってみた。それで通ってしまった。
・10万回はDecimal演算きついと思ったんだけど、pypyTLEでpythonAC1.04秒だった。
　Decimalで殴りたい時はpypyよりpython使うのがいいっぽいね。
"""

import sys
from decimal import Decimal, ROUND_FLOOR, ROUND_CEILING

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

x, y, r = map(Decimal, input().split())

lx = int((x-r).quantize(Decimal('1'), rounding=ROUND_CEILING))
rx = int((x+r).quantize(Decimal('1'), rounding=ROUND_FLOOR))
ans = 0
for cx in range(lx, rx+1):

    # (x-a)^2+(y-b)^2=r^2
    # y=+-√(r^2-(x-a)^2)+b
    ry = Decimal(r**2-(cx-x)**2).sqrt()
    ly = -ry
    ry += y
    ly += y
    ly = ly.quantize(Decimal('1'), rounding=ROUND_CEILING)
    ry = ry.quantize(Decimal('1'), rounding=ROUND_FLOOR)
    ans += max(ry-ly+1, 0)
print(ans)
