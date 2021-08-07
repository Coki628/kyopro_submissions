"""
・その他埋めAC数上げ
・自力AC
・結局C++でAC取れないのでこっちで。
　Pythonの整数除算切り捨ては負の方向に丸めるので、
　絶対値でやって後から符号付ける。
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
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

for _ in range(INT()):
    a, b = MAP()

    is_neg = (a < 0)^(b < 0)
    ans = abs(a)//abs(b)
    if is_neg: ans = -ans
    print(ans)
