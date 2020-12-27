"""
・蟻本演習4-4-3
・個数制限付きナップザック、スライド最小値
・これはまあほぼ蟻本写経しただけ。
・スライド最小値は、区間が連続してなくても、MOD累積和みたいに等間隔に空いたところからのmin/max取得もできるんだな。
　なんか使いやすくうまいこと関数に切り出したりできないかなー。。
・やってみた。結構うまく切り出せたと思う！
"""

import sys
from collections import deque

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

# スライド最小値(比較関数、元の数列、遷移回数、遷移幅、遷移の重み)
def slide_min(func, A, k, w=1, v=0):
    from collections import deque

    N = len(A)
    res = A[:]
    for a in range(w):
        que = deque()
        i = 0
        while i*w+a < N:
            val = A[i*w+a] - i*v
            while que and func(que[-1][1], val) == val:
                que.pop()
            que.append((i, val))
            res[i*w+a] = que[0][1] + i*v
            if que[0][0] == i-k:
                que.popleft()
            i += 1
    return res

N, W = MAP()
VWM = []
for i in range(N):
    v, w, m = MAP()
    VWM.append((v, w, m))

dp = list2d(N+1, W+1, 0)
for i, (v, w, m) in enumerate(VWM):
    dp[i+1] = slide_min(max, dp[i], m, w, v)
ans = dp[N][W]
print(ans)
