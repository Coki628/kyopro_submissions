"""
・途中、多倍長で色々試したかったのでこっちでやってた。
　最終的にこっちを修正して時間内に通せた。
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
MOD = 998244353
EPS = 10**-10

N, K, M = MAP()

ans = pow(M, pow(K, N, MOD-1) if pow(K, N, MOD-1) != 0 else MOD-1, MOD)
print(ans)
