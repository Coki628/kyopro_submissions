"""
参考：https://ei1333.github.io/luzhiled/snippets/dp/slide-min.html
・蟻本演習4-4-2
・スライド最小値
・そのうちやってみよう言ってたやつ、やってみた。
・とりあえず特徴として、
　・計算量はO(N)
　・演算はmin,maxどっちもOK、多分セグ木に乗るやつならだいたいOKなのかな
　・更新は無理
　・取得したい区間長が固定の場合のみ使える
　って感じかー。
・pypyのdequeが多分そんなに速くないっぽいのもあって、セグ木と速度比較したけど、
　0.26秒 -> 0.18秒って感じ。うーん、やっぱ使うならC++で速度攻めたい時だろうか。
・個数制限ナップザック対応版をこっちでもverifyした。
"""

import sys
from itertools import accumulate

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

def slide_min(func, A, k, w=1, v=0):
    from collections import deque

    que = deque()
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

N, K = MAP()
A = LIST()

slidemn = slide_min(min, A, K)
slidemx = slide_min(max, A, K)
total = N - K + 1
dup = 0
for i in range(N-K):
    mn = slidemn[i+K]
    mx = slidemx[i+K]
    if mn == A[i] and mx == A[i+K]:
        dup += 1

B = [0] * N
for i in range(N-1):
    if A[i] < A[i+1]:
        B[i+1] = 1
B = list(accumulate(B))
prev = INF
for i in range(N-K+1):
    if B[i+K-1] - B[i] == K - 1:
        if prev + K - 1 < i:
            dup += 1
        prev = i

print(total - dup)
