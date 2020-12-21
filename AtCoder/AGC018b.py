# -*- coding: utf-8 -*-

"""
参考：https://img.atcoder.jp/agc018/editorial.pdf
・意外と愚直シミュレーションで間に合う。
・計算量は最大300^3=2700万だけど、実際は外ループのカウンタが2以上増えたりするのでもっと少ない。
・pypyAC0.5秒。
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

N, M = MAP()
A = list2d(N, M, 0)
for i in range(N):
    for j, a in enumerate(LIST()):
        # データの持ち方を変えておく
        A[i][a-1] = j

k = 0
valid = [1] * M
ans = INF
while k < M:
    cnt = [0] * M
    for i in range(N):
        mn = INF
        idx = -1
        for j in range(M):
            if valid[j] and A[i][j] < mn:
                mn = A[i][j]
                idx = j
        # 一番順位が高いスポーツにカウント追加
        cnt[idx] += 1
    mx = max(cnt)
    ans = min(ans, mx)
    for i in range(M):
        # 票が最も集まったものは次から選ばないようにする
        if cnt[i] == mx:
            valid[i] = 0
            k += 1
print(ans)
