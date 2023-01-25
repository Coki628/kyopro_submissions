"""
・なんとか自力AC！
・実験、二分探索、オーバーフロー、場合分け
・何かと罠が多い。危なかった。
・実験から、基本的に同値はなく単調増加していく様子が分かる。二分探索をする。
・ただし、Xが1桁だとずっとXになるので、M以下かどうかで場合分けして0か1。ここに2通りあるのも罠。
・それだけじゃない。Mの最大が10^18あって、実はにぶたんの最大値INFが10^18だと足りない。
　0,1の場合分けを整えた時、その可能性に気付いて10^20に上限を上げたのはファインプレーだった。
　pythonで手軽にやれるからできた。C++だったら型とか変えなきゃだし、サボってもう1ペナしてたと思う。
　ちなみにびびって10^20にしたけど、10^19でも大丈夫だった。
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
INF = 10**19
MOD = 10**9 + 7
EPS = 10**-10

def bisearch_max(mn, mx, func):
    """ 条件を満たす最大値を見つける二分探索 """

    ok = mn
    ng = mx
    while ok+1 < ng:
        mid = (ok+ng) // 2
        if func(mid):
            ok = mid
        else:
            ng = mid
    return ok

def ntod(S, n):
    res = 0
    for k, s in enumerate(S[::-1]):
        res += n**k * int(s)
    return res

X = input()
M = INT()

mx = int(max(X))
if len(X) == 1:
    if int(X) <= M:
        print(1)
    else:
        print(0)
    exit()

# A = []
# for i in range(mx+1, 20):
#     A.append(ntod(X, i))
# print(*A)

# N = len(A)
# for i in range(N-1):
#     print(A[i+1]-A[i])

def check(m):
    return ntod(X, m) <= M

res = bisearch_max(mx, INF, check)
ans = res-mx
print(ans)
