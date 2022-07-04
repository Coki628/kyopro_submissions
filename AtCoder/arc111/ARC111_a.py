"""
参考：https://twitter.com/tatyam_prime/status/1347913966530359297
　　　https://twitter.com/idat_50me/status/1347911865943277568
・自力ならず。。。
・一般に、mod A で管理している時に B で割りたい時は mod AB で管理しておけば良い。とのこと。
・色んな人が色んな解釈を説明してくれていたけど、とりあえず上記の一言を覚えておくとよさそう。
・あと、x/y の商が a で余りが r のときに x = ay + r と変形するテク、ってのがあるみたいで、
　これを元にうまいこと式変形するといいみたい。確かに使えそう。
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
sys.setrecursionlimit(10**9)
INF = 10**19
MOD = 10**9 + 7
EPS = 10**-10

N, M = MAP()

ans = pow(10, N, M**2) // M % M
print(ans)
