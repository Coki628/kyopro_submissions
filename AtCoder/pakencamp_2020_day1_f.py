"""
・自力AC
・周期にぶつかると信じて適当にDPした。
　P=1はDP始まる前だから場合分け。これでWA。。
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

P = INT()

if P == 1:
    print(1)
    exit()

N = 1000007
dp = [0] * N
dp[1] = 1
dp[2] = 1
for i in range(3, N):
    dp[i] = (dp[i-1] + dp[i-2]) % P
    if dp[i] == 0:
        print(i)
        break
else:
    print(-1)
