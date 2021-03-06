"""
・dequeでシミュレーションやる。
"""

import sys
from collections import deque

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
INF = 10 ** 18
MOD = 10 ** 9 + 7

for _ in range(INT()):
    N = INT()
    A = LIST()

    que = deque(A)
    mx = 0
    cur = 0
    alice = 0
    bob = 0
    turn = 0
    while que:
        cur = 0
        if turn % 2 == 0:
            while que and cur <= mx:
                cur += que.popleft()
            mx = cur
            alice += cur
        else:
            while que and cur <= mx:
                cur += que.pop()
            mx = cur
            bob += cur
        turn += 1
    print(turn, alice, bob)
