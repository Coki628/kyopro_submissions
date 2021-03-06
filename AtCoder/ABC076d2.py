# -*- coding: utf-8 -*-

"""
・速解き特訓ABC周回
・自力AC！
・愚直シミュレーション
・なんとなく方針覚えてたけど、実装だるかったー。
"""

import sys

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

N = INT()
# 0.5考慮のため*2、終了時0のため番兵
A = [a*2 for a in LIST()] + [1]
B = [b*2 for b in LIST()] + [0]

def check1(i, t):
    nxtt = cur
    for j in range(i+1, N+1):
        nxtt += A[j-1]
        dist = nxtt - t
        # 1つ先で+1の状態でいても大丈夫かどうか
        if spd + 2 - dist > B[j]:
            return False
    return True

def check2(i, t):
    nxtt = cur
    for j in range(i+1, N+1):
        nxtt += A[j-1]
        dist = nxtt - t
        # 1つ先で今と同じ(+-0)の状態でいても大丈夫かどうか
        if spd + 1 - dist > B[j]:
            return False
    return True

cur = spd = sm = 0
for i, a in enumerate(A[:N]):
    b = B[i]
    # 各時点tにおいて加速、維持が可能かどうか確認
    for t in range(cur, cur+a):
        # 加速OK
        if spd + 1 <= b and check1(i, t):
            # この瞬間の加算分は増減の半分にする
            sm += spd + 0.5
            spd += 1
        # 維持OK
        elif spd <= b and check2(i, t):
            sm += spd
        # 減速必須
        else:
            sm += spd - 0.5
            spd -= 1
    cur += a
print(sm / 4)
