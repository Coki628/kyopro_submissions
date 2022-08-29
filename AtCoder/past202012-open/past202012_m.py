"""
・自力AC？問題公開されたら投げてみる。
・累積和、BIT、二分探索
・ある位置から見て、直前をどこから切ってこれるかの長さの上限はLと決まってる。
　ここで下限をxに定めて、この範囲でいけるかを二分探索してみる。
・ある範囲から遷移してこれるかはBITで持っておく。
・20万にlog2つ乗ってるから、合ってたとしても間に合うか微妙かなぁー。。
　→TLEだった。。C++にする。
"""

import sys
from itertools import accumulate

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

class BIT:
    """ Binary Indexed Tree """

    def __init__(self, n):
        self.n = n
        # 0-indexed
        n += 1
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

    def query(self, l, r):
        """ 区間和の取得 [l, r) """
        return self.sum(r-1) - self.sum(l-1)
    
    def get(self, i):
        """ 一点取得 """
        return self.query(i, i+1)

    def update(self, i, x):
        """ 値の更新：添字i, 値x """
        self.add(i, x - self.get(i))

    def print(self):
        for i in range(self.n):
            print(self.get(i), end=' ')
        print()

def bisearch_min(mn, mx, func):
    """ 条件を満たす最小値を見つける二分探索 """

    ok = mx
    ng = mn
    while ng+1 < ok:
        mid = (ok+ng) // 2
        if func(mid):
            ok = mid
        else:
            ng = mid
    return ok

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

N, L = MAP()
A = LIST()
acc = [0] + list(accumulate(A))

def check(x):
    # bit[i] := 位置iまで見て、条件を満たす切り方にできるか
    bit = BIT(N+1)
    bit.add(0, 1)

    for i in range(1, N+1):
        # 区間和[m,i)がL以下になる最小index
        lo = bisearch_min(-1, i, lambda m: acc[i]-acc[m] <= L)
        # 区間和[m,i)がx以上になる最大index
        hi = bisearch_max(-1, i, lambda m: acc[i]-acc[m] >= x)
        if hi < lo:
            continue
        if bit.query(lo, hi+1) > 0:
            bit.add(i, 1)
    return bit.get(N) > 0
res = bisearch_max(0, L+1, check)
print(res)
