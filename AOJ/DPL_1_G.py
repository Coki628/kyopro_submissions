"""
・蟻本演習4-4-3
・個数制限付きナップザック、スライド最小値
・これはまあほぼ蟻本写経しただけ。
・スライド最小値は、区間が連続してなくても、MOD累積和みたいに等間隔に空いたところからのmin/max取得もできるんだな。
　なんか使いやすくうまいこと関数に切り出したりできないかなー。。
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

N, W = MAP()
VWM = []
for i in range(N):
    v, w, m = MAP()
    VWM.append((v, w, m))

dp = list2d(N+1, W+1, 0)
for i, (v, w, m) in enumerate(VWM):
    for a in range(w):
        que = deque()
        j = 0
        while j*w+a <= W:
            val = dp[i][j*w+a] - j*v
            while que and que[-1][1] <= val:
                que.pop()
            que.append((j, val))
            dp[i+1][j*w+a] = que[0][1] + j*v
            if que[0][0] == j-m:
                que.popleft()
            j += 1
ans = dp[N][W]
print(ans)
