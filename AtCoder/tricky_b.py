"""
・TLで話題になっていたので。
　絶対まだ穴ありそうと思って投げたけどやっぱりWA。。
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

# 2次方程式の解の公式
def dim2formula(a, b, c):
    from math import sqrt

    try:
        return (-b+sqrt(pow(b, 2)-4*a*c))/(2*a), (-b-sqrt(pow(b, 2)-4*a*c))/(2*a)
    # 解なしはNoneを返却
    except ValueError:
        return None, None

for _ in range(INT()):
    a, b, c = MAP()

    if a == 0:
        if b == 0 and c == 0:
            print(3)
        elif b == 0:
            print(0)
        else:
            print(1, -c/b)
        continue

    ans1, ans2 = dim2formula(a, b, c)
    if ans1 is None:
        print(0)
        continue

    if ans1 > ans2:
        ans1, ans2 = ans2, ans1
    if abs(ans1-ans2) < EPS:
        print(1, ans1)
    else:
        print(2, ans1, ans2)
