# -*- coding: utf-8 -*-

"""
参考：https://img.atcoder.jp/abc139/editorial.pdf
・数学系、角度でソート
・方針が分かったら、実装はすんなり書けた。
・ABC033dでやったのを簡単にした感じ。
"""

import sys
from math import atan2, degrees, hypot

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(): return list(map(int, input().split()))
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10 ** 9)
INF = float('inf')
MOD = 10 ** 9 + 7
EPS = 10 ** -9

N = INT()

degs = []
XY = []
for i in range(N):
    x, y = MAP()
    XY.append((x, y))
    deg = degrees(atan2(y, x))
    if deg < 0:
        # 負の数なら時計回り側にあるので逆向きにする
        deg += 360
    degs.append((deg, i))
# 角度でソート
degs.sort()
# 2周目をつける
degs += [(deg+360, i) for deg, i in degs]

ans = 0
for i in range(N):
    deg, idx = degs[i]
    xsm, ysm = XY[idx]
    ans = max(ans, hypot(xsm, ysm))
    j = i + 1
    # 始点から180度未満の方向に向かうものを全て追加しながら最大を取る
    while degs[j][0] < deg+180:
        _, idx = degs[j]
        x, y = XY[idx]
        xsm += x
        ysm += y
        ans = max(ans, hypot(xsm, ysm))
        j += 1
print(ans)
