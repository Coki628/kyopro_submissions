"""
・さくっと自力AC
・ビット全探索
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

def popcount(i):
    i = i - ((i >> 1) & 0x55555555)
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333)
    i = (i + (i >> 4)) & 0x0f0f0f0f
    i = i + (i >> 8)
    i = i + (i >> 16)
    return i & 0x3f

N, M = MAP()
ABC = []
for i in range(M):
    a, b, c = MAP()
    a -= 1; b -= 1; c -= 1
    ABC.append((a, b, c))

ans = 0
for bit in range(1<<N):
    if popcount(bit) < 2:
        continue
    ok = 1
    se = set()
    for a, b, c in ABC:
        if bit>>a & 1 and bit>>b & 1 and bit>>c & 1:
            ok = 0
            break
        elif bit>>a & 1 and bit>>b & 1:
            se.add(c)
        elif bit>>b & 1 and bit>>c & 1:
            se.add(a)
        elif bit>>a & 1 and bit>>c & 1:
            se.add(b)
    if not ok:
        continue
    ans = max(ans, len(se))
print(ans)
