"""
・参戦しなかったけど、これだけやった。無事自力AC。
・前から貪欲、二分探索
・S,Tの0,1が異なるところでは、自分より右から1を1つ持ってくる必要がある。
　これが分かると、S内で1が次に出現する位置が分かれば一番近くから持ってくればいいので、
　必要な時に貪欲に取ってくる操作で大丈夫になる。
・こっちのが易しいと分かって解きにかかったから割とすんなり行けたけど、
　本番中でAむずくてテンパってる状態で果たして同じようにできただろうか。。。
"""

import sys
from bisect import bisect_right

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for k in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for k in range(c)] for k in range(b)] for i in range(a)]
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

N = INT()
S = list(input())
T = input()

A = []
for i, s in enumerate(S):
    if s == '1':
        A.append(i)
M = len(A)

ans = 0
j = 0
for i in range(N):
    if S[i] != T[i]:
        # 現在位置か使用済位置の大きい方より右から1を探す
        idx = bisect_right(A, max(i, j))
        # 1がもうない
        if idx == M:
            print(-1)
            exit()
        j = A[idx]
        # 使ったので0にしておく
        S[j] = '0'
        ans += j - i
print(ans)
