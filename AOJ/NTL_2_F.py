"""
・AOJコース埋め
・多倍長でぶん殴る。
・今度は20万桁*20万桁=400億桁くらいになるので、
　時間もそうだけど出力とか色々やばくないか？と思いながらも
　そのままぶん投げたけど無事AC2.37秒。(制約2秒だけどAOJはPythonのTL結構長いんだよね。)
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

a, b = MAP()

ans = a*b
print(ans)
