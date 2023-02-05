"""
・自力AC！
・座標変換
・45度回転させると、縦横の区別を考えないでマンハッタン距離が計れるやつ。
　大昔にABC111Dで初めて知ったけど、実際活用してACに繋げたのは今回が初めてかも。
・皆さんググって結構通していたらしい。ググって出るかどうかの嗅覚はなんかまだ養えないなー。
　正攻法でちゃんと通せたのは良かったけど、それでスピード負けしてるからね。。。
"""

import sys

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

N = INT()
U = []
V = []
for i in range(N):
    x, y = MAP()
    U.append(x+y)
    V.append(x-y)

U.sort()
V.sort()
ans = max(U[-1]-U[0], V[-1]-V[0])
print(ans)
