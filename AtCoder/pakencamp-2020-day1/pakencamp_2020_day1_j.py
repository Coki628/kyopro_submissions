"""
参考：https://mathwords.net/pitagorasusuu
・終了後自力AC？
・ピタゴラス数
・「直角三角形 整数」とかでググると情報が出る。
・ちょっと多めにループ回して、gcd取って互いに素なやつだけ答えに追加していけばOK。
"""

import sys
from math import gcd

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

N = 10**5

ans = []
for n in range(1, 1000, 2):
    for m in range(2, 1000, 2):
        a = abs(m**2-n**2)
        b = 2*m*n
        c = m**2+n**2
        if gcd(gcd(a, b), c) == 1:
            ans.append([a, b, c])
            ans[-1].sort()

for abc in ans[:N]:
    print(*abc)
