"""
・bit全探索
・Cにしてはそこそこー、とか思ったけどこれでも茶diff下位なんだねー。
"""

import sys

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for j in range(c)] for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(N=None): return list(MAP()) if N is None else [INT() for i in range(N)]
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10 ** 9)
INF = 10 ** 18
MOD = 10 ** 9 + 7

N, M, X = MAP()
C = [0] * N
A = [[]] * N
for i in range(N):
    C[i], *A[i] = MAP()

ans = INF
for bit in range(1<<N):
    skills = [0] * M
    cost = 0
    for i in range(N):
        if bit>>i & 1:
            cost += C[i]
            for j in range(M):
                skills[j] += A[i][j]
    if min(skills) >= X:
        ans = min(ans, cost)
if ans == INF:
    print(-1)
else:
    print(ans)
