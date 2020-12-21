# -*- coding: utf-8 -*-

import sys
def input(): return sys.stdin.readline().strip()
sys.setrecursionlimit(10 ** 9)
INF = float('inf')
MOD = 10 ** 9 + 7

# Union-Find木
class UnionFind:
    def __init__(self, n):
        # 親要素のノード番号を格納。par[x] == xの時そのノードは根
        # 1-indexedのままでOK、その場合は[0]は未使用
        self.par = [i for i in range(n+1)]
        # 木の高さを格納する（初期状態では0）
        self.rank = [0] * (n+1)

    # 検索
    def find(self, x):
        # 根ならその番号を返す
        if self.par[x] == x:
            return x
        else:
            # 走査していく過程で親を書き換える
            self.par[x] = self.find(self.par[x])
            return self.par[x]

    # 併合
    def union(self, x, y):
        # 根を探す
        x = self.find(x)
        y = self.find(y)
        # 木の高さを比較し、低いほうから高いほうに辺を張る
        if self.rank[x] < self.rank[y]:
            self.par[x] = y
        else:
            self.par[y] = x
            # 木の高さが同じなら片方を1増やす
            if self.rank[x] == self.rank[y]:
                self.rank[x] += 1

    # 同じ集合に属するか判定
    def same(self, x, y):
        return self.find(x) == self.find(y)

# 道路についてのUnion-Find木
N, K, L = map(int, input().split())
uf = UnionFind(N)
for i in range(K):
    p, q = map(int, input().split())
    uf.union(p, q)

# グループ毎にカウントする準備
group = dict(zip(set(uf.par), [1]*len(set(uf.par))))
group.pop(0)
for i in range(L):
    p, q = map(int, input().split())
    # 鉄道について、既に道路で繋がっている場所なら数を足す
    if uf.same(p, q):
        group[uf.par[p]] += 1

ans = [0] * N
for i in range(N):
    ans[i] = group[uf.par[i+1]]
print(*ans)

# ダメだ。これじゃ余計なやつにまで足しちゃう…。
