# -*- coding: utf-8 -*-

"""
・蟻本演習3-5-9
・最大流、点素パス
・辺への到達がゴールなので、辺の真ん中を表すような頂点を作る。
・各頂点1回しか通れないので、in,out分割して容量は1にする。
・毎回新たにフローの確認を取りたいので、流す前にコピーを作成しておく。
・計算量が最大で約5000回近く、最大5000辺へのフローを流す。毎回配列コピーもある。つらい。
・コピーを標準ライブラリのdeepcopyから手製のに変えたらだいぶ速くなったけど、それでもTLE。。
・とりあえず後半のテストケースまでWAなしで通ってはいるから、ロジックは間違ってないとは思う。
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

class Dinic:
    """ 最大流(Dinic) """

    INF = 10 ** 18

    def __init__(self, n):
        self.n = n
        self.links = [[] for _ in range(n)]
        self.depth = None
        self.progress = None
    
    def copy(self):
        res = Dinic(self.n)
        res.links = [[a[:] for a in b] for b in self.links]
        return res
 
    def add_link(self, _from, to, cap):
        self.links[_from].append([cap, to, len(self.links[to])])
        self.links[to].append([0, _from, len(self.links[_from]) - 1])
 
    def bfs(self, s):
        from collections import deque

        depth = [-1] * self.n
        depth[s] = 0
        q = deque([s])
        while q:
            v = q.popleft()
            for cap, to, _ in self.links[v]:
                if cap > 0 and depth[to] < 0:
                    depth[to] = depth[v] + 1
                    q.append(to)
        self.depth = depth
 
    def dfs(self, v, t, flow):
        if v == t:
            return flow
        links_v = self.links[v]
        for i in range(self.progress[v], len(links_v)):
            self.progress[v] = i
            cap, to, rev = link = links_v[i]
            if cap == 0 or self.depth[v] >= self.depth[to]:
                continue
            d = self.dfs(to, t, min(flow, cap))
            if d == 0:
                continue
            link[0] -= d
            self.links[to][rev][0] += d
            return d
        return 0
 
    def max_flow(self, s, t):
        INF = Dinic.INF
        flow = 0
        while True:
            self.bfs(s)
            if self.depth[t] < 0:
                return flow
            self.progress = [0] * self.n
            current_flow = self.dfs(s, t, INF)
            while current_flow > 0:
                flow += current_flow
                current_flow = self.dfs(s, t, INF)

N, M = MAP()

dinic = Dinic(N*2+M)
for i in range(N):
    # 各頂点のin -> out
    dinic.add_link(i, N+i, 1)

for i in range(M):
    a, b = MAP()
    a -= 1; b -= 1
    # 頂点a <-> 辺i
    dinic.add_link(N+a, N*2+i, 1)
    dinic.add_link(N*2+i, a, 1)
    # 頂点b <-> 辺i
    dinic.add_link(N+b, N*2+i, 1)
    dinic.add_link(N*2+i, b, 1)
    tmp = dinic.copy()
    # 頂点0-out -> 辺i への最大流を確認
    res = dinic.max_flow(N, N*2+i)
    if res >= 2:
        Yes()
    else:
        No()
    # フローをリセット
    dinic = tmp
