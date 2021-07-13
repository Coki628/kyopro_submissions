"""
参考：https://www.geisya.or.jp/~mwm48961/kou2/base_change1j.htm
・E8さん典型90問埋め
・自力AC！
・誤差、log、底の変換公式
・この誤差ゲーはDecimalで殴るしかない！
　と思ったらDecimalのlogがlog10とlogeしかなくて詰んだー。。
　と思ったら底は変換できるのいうのがググって判明し、事なきを得る。
"""

import sys
from decimal import Decimal

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

# logaのbを返す
def log(a: int, b: Decimal):
    # 底の変換
    return b.log10()/Decimal(a).log10()

a, b, c = map(Decimal, input().split())

if log(2, a) < b*log(2, c):
    Yes()
else:
    No()
