# -*- coding: utf-8 -*-

"""
参考：https://scrapbox.io/snuke/Codeforces_Round_%23606
・別解。UnionFind。
・DFS解のが考え方は素直な気がするけど、これのが綺麗にまとまった感はあるかも。
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

class UnionFind:

    def __init__(self, n):
        self.n = n
        self.par = [i for i in range(n+1)]
        self.rank = [0] * (n+1)
        self.size = [1] * (n+1)
        self.tree = [True] * (n+1)

    def find(self, x):
        if self.par[x] == x:
            return x
        else:
            self.par[x] = self.find(self.par[x])
            return self.par[x]

    def union(self, x, y):
        x = self.find(x)
        y = self.find(y)

        if x == y:
            self.tree[x] = False
            return
        if not self.tree[x] or not self.tree[y]:
            self.tree[x] = self.tree[y] = False

        if self.rank[x] < self.rank[y]:
            self.par[x] = y
            self.size[y] += self.size[x]
        else:
            self.par[y] = x
            self.size[x] += self.size[y]
            if self.rank[x] == self.rank[y]:
                self.rank[x] += 1

    def is_same(self, x, y):
        return self.find(x) == self.find(y)

    def get_size(self, x=None):
        if x is not None:
            return self.size[self.find(x)]
        else:
            res = set()
            for i in range(self.n+1):
                res.add(self.find(i))
            return len(res) - 1
    
    def is_tree(self, x):
        return self.tree[self.find(x)]

for _ in range(INT()):
    N, M, a, b = MAP()
    # bに関わる辺を除いたUnionFind
    uf1 = UnionFind(N)
    # aに関わる辺を除いたUnionFind
    uf2 = UnionFind(N)
    for i in range(M):
        x, y = MAP()
        if a in [x, y] and b in [x, y]:
            continue
        elif a in [x, y]:
            uf1.union(x, y)
        elif b in [x, y]:
            uf2.union(x, y)
        else:
            uf1.union(x, y)
            uf2.union(x, y)
    # aへ行くのにbを絶対通る頂点数
    cnt1 = N - uf1.get_size(a) - 1
    # bへ行くのにaを絶対通る頂点数
    cnt2 = N - uf2.get_size(b) - 1
    print(cnt1 * cnt2)
