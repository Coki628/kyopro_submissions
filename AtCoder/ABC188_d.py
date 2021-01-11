"""
・自力AC！
・区間を管理する系、ソートして平面走査(イベントソート)っぽくやる。
・座圧いもすした人が結構いるみたいだけど、確かにそれは実装がつらそう。。
・今有効な期間をプリキューに突っ込んで、終了が来たやつは取り出す、みたいにやった。
・イベントソート的に考えると、期間の開始と終了を分けて、同じ列に突っ込んでソートするだから、
　それも確かに考えるべきだったかなーとかは思う。汎用性高いテクだし。
・でもまあ悩まず書いて詰まらず通せたからOK。
"""

import sys
from heapq import heappush, heappop

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
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

N, x = MAP()
D = set()
ABC = []
for i in range(N):
    a, b, c = MAP()
    a -= 1
    ABC.append((a, b, c))
    D.add(a)
    D.add(b)

D = sorted(D)
M = len(D)
ABC.sort(reverse=1)
que = []
cur = 0
ans = 0
for i in range(M-1):
    while que and que[0][0] <= D[i]:
        b, c = heappop(que)
        cur -= c
    while ABC and ABC[-1][0] <= D[i]:
        a, b, c = ABC.pop()
        cur += c
        heappush(que, (b, c))
    ans += (D[i+1]-D[i])*min(cur, x)
print(ans)
