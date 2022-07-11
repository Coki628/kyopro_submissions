"""
・C++幾何ライブラリの回転行列が何かバグっていて、Python時代のやつ引っ張り出してきてPythonでAC。
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

# 回転行列で座標s,tを回転
def rotate(s, t, dig):
    from math import sin, cos, radians

    x1, y1 = s
    x2, y2 = t
    # sを軸としてtを左回りにdig度回転させた座標(x3,y3)
    x3 = x1 + (x2-x1) * cos(radians(dig)) - (y2-y1) * sin(radians(dig))
    y3 = y1 + (x2-x1) * sin(radians(dig)) + (y2-y1) * cos(radians(dig))
    return (x3, y3)

a, b, d = MAP()
res = rotate((0, 0), (a, b), d)
print(*res)
