# -*- coding: utf-8 -*-

"""
・600点自力AC！
・AとBだけなので2値化して累積和すれば、任意の区間にA,BがいくつあるかO(1)で分かる。
・最終的にどの文字列も3つのタイプのどれかに帰着する。同タイプなら同じ文字列にできる。
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

S = [ord(s)-65 for s in input()]
T = [ord(t)-65 for t in input()]

acc1 = [0] + list(accumulate(S))
acc2 = [0] + list(accumulate(T))

# 3つのタイプを判定(0: aが残る, 1: bが残る, 2: 何も残らない)
def check(cnta, cntb):
    if cnta == cntb:
        return 2
    elif cnta < cntb:
        cntb -= cnta
        if cntb % 3 == 0:
            return 2
        elif cntb % 3 == 1:
            return 1
        else:
            return 0
    else:
        cnta -= cntb
        if cnta % 3 == 0:
            return 2
        elif cnta % 3 == 1:
            return 0
        else:
            return 1

Q = INT()
for _ in range(Q):
    l1, r1, l2, r2 = MAP()

    ln1 = r1 - l1 + 1
    ln2 = r2 - l2 + 1
    # 累積和を使ってO(1)でAとBの個数を取得
    cntb1 = acc1[r1] - acc1[l1-1]
    cnta1 = ln1 - cntb1
    cntb2 = acc2[r2] - acc2[l2-1]
    cnta2 = ln2 - cntb2
    # 同じタイプかどうか判定する
    if check(cnta1, cntb1) == check(cnta2, cntb2):
        YES()
    else:
        NO()
