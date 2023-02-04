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

N, M, T = MAP()

curt = 0
curn = N
for i in range(M):
    a, b = MAP()

    time = a - curt
    curn -= time
    if curn <= 0:
        No()
        break
    time = b - a
    curn += time
    curn = min(curn, N)
    curt = b
else:
    time = T - curt
    curn -= time
    if curn <= 0:
        No()
    else:
        Yes()
