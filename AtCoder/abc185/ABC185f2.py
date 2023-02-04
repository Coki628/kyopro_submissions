"""
・速攻自力AC。びっくりするくらいライブラリVerifyな問題。
・区間XOR取得、1点更新ができればOK。BITでも+を^にすればできるみたいだね。
・BITでもやってみた版。かなり速くなると思ったんだけどそうでもなくて、pypyAC0.58秒→0.43秒。
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

class BIT:
    """ Binary Indexed Tree """

    def __init__(self, n, f=lambda a, b: a + b, g=lambda a, b: a - b):
        self.n = n
        self.f = f
        self.g = g
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
            s = self.f(s, self.tree[i-1])
            i -= i & -i
        return s

    def add(self, i, x):
        """ 値の追加：添字i, 値x """
        i += 1
        while i <= self.size:
            self.tree[i-1] = self.f(self.tree[i-1], x)
            i += i & -i

    def query(self, l, r):
        """ 区間和の取得 [l, r) """
        return self.g(self.sum(r-1), self.sum(l-1))
    
    def get(self, i):
        """ 一点取得 """
        return self.query(i, i+1)

    def update(self, i, x):
        """ 値の更新：添字i, 値x """
        self.add(i, self.g(x, self.get(i)))

    def print(self):
        for i in range(self.n):
            print(self.get(i), end=' ')
        print()

N, Q = MAP()
A = LIST()
bit = BIT(N, lambda a, b: a ^ b, lambda a, b: a ^ b)
for i in range(N):
    bit.add(i, A[i])

for i in range(Q):
    t, x, y = MAP()
    x -= 1
    if t == 1:
        bit.add(x, y)
    else:
        res = bit.query(x, y)
        print(res)
