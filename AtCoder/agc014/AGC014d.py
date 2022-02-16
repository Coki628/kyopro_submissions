"""
・蟻本演習4-2-2
・木上のゲーム
・葉の親で同じのが1つでもあれば勝ち、かと思ったけどそこそこ合っててWA。
　さすがに黄diffがそんな自分が簡単に思いつけるほど甘い訳ないか。。
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
sys.setrecursionlimit(10**9)
INF = 10**19
MOD = 10**9 + 7
EPS = 10**-10

N = INT()
nodes = [[] for i in range(N)]
for _ in range(N-1):
    a, b = MAP()
    a -= 1; b -= 1
    nodes[a].append(b)
    nodes[b].append(a)

pars = set()
for i in range(N):
    if len(nodes[i]) == 1:
        if nodes[i][0] in pars:
            print('First')
            exit()
        else:
            pars.add(nodes[i][0])
print('Second')
