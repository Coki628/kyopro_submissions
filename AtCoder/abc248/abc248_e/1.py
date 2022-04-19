"""
・自力ならず…。
・幾何、誤差対策、有理数
・直線y=ax+bを被りなく集めて、線上にある点の数を数える、
　ができればいいんだけど、これがまあ大変で…。
・最適化なら被りは適当でいいんだけど、数え上げなのでちゃんとやる必要がある。
　a,bの値は普通にやると実数になってしまうので、分数クラスを使う。とした。
・WAが取れなかったのはK=1の別処理をN=1でいいと思い込んでしまったミスで、
　これはまあ論外なんだけど、気付けなかったのでしょうがない。
・TLEなのは分数クラスFractionが結構重いから？と思って、
　終了後ゆっくりC++の分数クラスを自作してみることにした。
　そのうちやろうと思って、やってなかったやつの1つだしね…。
"""

import sys
from fractions import Fraction
from collections import Counter

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

# 2点を通る直線の式の係数a,b
def calc(p1, p2):
    x1, y1 = p1
    x2, y2 = p2
    a = (y2-y1) / (x2-x1)
    b = (x1*y2-x2*y1) / (x1-x2)
    return a, b

N, K = MAP()
XY = []
for i in range(N):
    x, y = map(Fraction, input().split())
    XY.append((x, y))

if K == 1:
    print('Infinity')
    exit()

AB = set()
zeros = Counter()
for i in range(N):
    # a == INFな直線は別処理
    zeros[XY[i][0]] += 1
    for j in range(i+1, N):
        if XY[i][0] == XY[j][0]:
            continue
        AB.add(calc(XY[i], XY[j]))

ans = 0
for a, b in AB:
    cnt = 0
    for i in range(N):
        x, y = XY[i]
        if y == a*x + b:
            cnt += 1
            if cnt >= K:
                ans += 1
                break
for y, cnt in zeros.items():
    if cnt >= K:
        ans += 1
print(ans)
