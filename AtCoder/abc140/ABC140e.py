# -*- coding: utf-8 -*-

"""
参考：https://img.atcoder.jp/abc140/editorial.pdf
　　　https://maspypy.com/atcoder-参加感想-2019-09-07abc-140
・AGC005bの発展問題
・BIT上の二分探索
・pythonTLEでpypyAC1.2秒。
・計算量は10万のNに二分探索とBITの区間取得でO(NlogNlogN)=10万*300弱で3000万、よく通ったなー。
"""

import sys

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for j in range(c)] for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(): return list(map(int, input().split()))
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10 ** 9)
INF = float('inf')
MOD = 10 ** 9 + 7

class BIT:

    def __init__(self, n):
        # 0-indexed
        nv = 1
        while nv < n:
            nv *= 2
        self.size = nv
        self.tree = [0] * nv

    def sum(self, i):
        """ [0, i]を合計する """
        s = 0
        i += 1
        while i > 0:
            s += self.tree[i-1]
            i -= i & -i
        return s

    def add(self, i, x):
        """ 値の追加：添字i, 値x """
        i += 1
        while i <= self.size:
            self.tree[i-1] += x
            i += i & -i

    def get(self, l, r=None):
        """ 区間和の取得 [l, r) """
        # 引数が1つなら一点の値を取得
        if r is None: r = l + 1
        res = 0
        if r: res += self.sum(r-1)
        if l: res -= self.sum(l-1)
        return res

def bisearch_min(mn, mx, func):
    """ 条件を満たす最小値を見つける二分探索 """
    ok = mx
    ng = mn
    while ng+1 < ok:
        mid = (ok+ng) // 2
        if func(mid):
            # 下を探しに行く
            ok = mid
        else:
            # 上を探しに行く
            ng = mid
    return ok

def bisearch_max(mn, mx, func):
    """ 条件を満たす最大値を見つける二分探索 """
    ok = mn
    ng = mx
    while ok+1 < ng:
        mid = (ok+ng) // 2
        if func(mid):
            # 上を探しに行く
            ok = mid
        else:
            # 下を探しに行く
            ng = mid
    return ok

# m~idxの間に出現済がない(この範囲の中で自分が最大値)かどうか
def calc1(m):
    cnt = lend - bit.sum(m-1)
    return cnt == 0

# m~idxの間に出現済が1つ以下(この範囲の中で自分が最大値か2番目)かどうか
def calc2(m):
    cnt = lend - bit.sum(m-1)
    return cnt <= 1

# idx~mの間に出現済がない(この範囲の中で自分が最大値)かどうか
def calc3(m):
    cnt = bit.sum(m) - rstart
    return cnt == 0

# idx~mの間に出現済が1つ以下(この範囲の中で自分が最大値か2番目)かどうか
def calc4(m):
    cnt = bit.sum(m) - rstart
    return cnt <= 1

N = INT()
A = LIST()
# aの昇順に処理できるようにindexで並べておく
idxs = [0] * (N+1)
for i, a in enumerate(A):
    idxs[a] = i + 1

bit = BIT(N+2)
# 先頭と末尾に番兵を仕込む
bit.add(0, 2)
bit.add(N+1, 2)
ans = [0] * (N+1)
# 大きいaから見ていく
for a in range(N, 0, -1):
    # a(N~1)が格納されているindex
    idx = idxs[a]
    # 左の終点と右の始点は各回固定なので先に取っておく
    lend = bit.sum(idx)
    rstart = bit.sum(idx-1)
    # 自分より小さいindexで2回目に自分より大きい値がある直前の場所
    p = bisearch_min(0, idx+1, calc2)
    # 自分より小さいindexで最初に自分より大きい値がある直前の場所
    q = bisearch_min(0, idx+1, calc1)
    # 自分より大きいindexで最初に自分より大きい値がある直前の場所
    r = bisearch_max(idx, N+1, calc3)
    # 自分より大きいindexで2回目に自分より大きい値がある直前の場所
    s = bisearch_max(idx, N+1, calc4)
    # aを使う回数 * a = (左に自分より大きい値がある時の通り数 + 右に自分より大きい値がある時の通り数) * a
    ans[a] = ((q-p)*(r-idx+1) + (idx-q+1)*(s-r)) * a
    # aを出現済とする
    bit.add(idx, 1)
# 全てのaについての合計
print(sum(ans))
