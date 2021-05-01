"""
・なんとか自力AC！
・二分探索、多倍長整数
・C++でダメだった理由分かった。これ、最大多分100桁くらいになりうるから、
　llでもオーバーフローするんだきっと。
・pythonで書き直して無事AC。
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
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

def bisearch_min(mn, mx, func):
    ok = mx
    ng = mn
    while ng+1 < ok:
        mid = (ok+ng) // 2
        if func(mid):
            ok = mid
        else:
            ng = mid
    return ok

for c in range(1, INT()+1):
    N = INT()
    A = LIST()

    S = ['']*N
    for i in range(N):
        S[i] = str(A[i])
    
    ans = 0
    for i in range(1, N):
        s = S[i-1]
        t = S[i]
        len_diff = len(s)-len(t)
        if len_diff > 0:
            M = pow(10, len_diff)
            res = bisearch_min(-1, M, lambda m: t+str(m).zfill(len_diff) > s)
            if res == M:
                S[i] += '0'*(len_diff+1)
                ans += len_diff+1
            else:
                S[i] = t+str(res).zfill(len_diff)
                ans += len_diff
        elif len_diff == 0:
            if t <= s:
                S[i] += '0'
                ans += 1

    ans = 'Case #{0}: {1}'.format(c, ans)
    print(ans)
