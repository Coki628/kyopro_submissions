"""
参考：https://www.youtube.com/watch?v=dhhldocM--0&feature=youtu.be
・自力ならず。。全く方針立たなかった。
・順列全探索、DP、二分探索
・いやーきつい。このレベル感を自力で解けるようになりたいけど、なかなか難しいね。。
　解説動画しっかり見て、自分なりによく噛み砕いて、頑張って実装してやっと通す、って感じ。。
　でもDみたいなのよりは、こういう方がトレーニングと経験値で通せるような気がするから、
　しっかり鍛えていきたいなー、と思ってる。
"""

import sys
from itertools import permutations, accumulate
from bisect import bisect_left

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c for j in range(b)] for i in range(a)]
def list3d(a, b, c, d): return [[[d for k in range(c)] for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e for l in range(d)] for k in range(c)] for j in range(b)] for i in range(a)]
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
W = LIST()
VL = [(0, 0)]
for i in range(M):
    l, v = MAP()
    VL.append((v, l))

# にぶたん用の前準備
VL.sort()
V = [0] * (M+1)
L = [0] * (M+1)
for i in range(1, M+1):
    V[i] = VL[i][0]
    # ある耐荷重より弱い部分の長さを累積maxしておく
    L[i] = max(VL[i][1], L[i-1])

# 例外処理
if max(W) > min(V[1:]):
    print(-1)
    exit()

ans = INF
for perm in permutations(W):
    acc = [0] + list(accumulate(perm))
    # dp[i] := iまでにかかる最大距離
    dp = [0] * N
    # ラクダの並びを区間とみなして、区間[l,r]を全部見る
    for l in range(N):
        for r in range(l+1, N):
            # この区間でかかるラクダの重さ
            sm = acc[r+1] - acc[l]
            # 耐荷重がsmより弱い場所を見つける
            idx = bisect_left(V, sm) - 1
            # その中で一番距離長い場所は累積maxしてあるので、それを足す
            dp[r] = max(dp[r], dp[l] + L[idx])
    ans = min(ans, dp[N-1])
print(ans)
