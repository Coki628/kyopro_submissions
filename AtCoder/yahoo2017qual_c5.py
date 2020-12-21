# -*- coding: utf-8 -*-

"""
・二分探索、公式解ではないがAC。(答え見た後なので自力ACではない)
・WAだったやつ、意外とあと一歩だった。
　答えの比較の前にソートするだけだった。
・プレフィックスに対してヒット数は単純減少(単純増加ではない)だったから、
　いつもの増加の時と境界の扱いが違くて調整悩んだけど、
　減少でもちゃんと出来るっていうのが分かって良かった。
・ソートして比較じゃなくてsetにした。こっちの0.04秒くらい速い。
・setのとこ、もうちょい編集。全要素の一致比較はset==setがシンプルで良さそう。
"""

import sys

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
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

N,K=MAP()
A=LIST()
S=[input() for i in range(N)]
S2=[S[A[i]-1] for i in range(K)]
S2.sort()
mxlen=len(S2[0])

# ヒットする文字列の数が最初にK以下になる
# プレフィックス位置を探す
def calc(idx):
    s=S2[0][:idx]
    cnt=0
    for i in range(N):
        if S[i].startswith(s):
            cnt+=1
    return cnt<=K

# 二分探索
hi=mxlen
low=-1
while low+1<hi:
    mid=(hi+low)//2
    if calc(mid):
        # ヒット数がK以下なら下を探しに行く
        hi=mid
    else:
        # ヒット数がK超なら上を探しに行く
        low=mid

# 位置を見つけたらそのプレフィックスでヒットする要素をansに集める
s=S2[0][:hi]
ans=set()
for i in range(N):
    if S[i].startswith(s):
        ans.add(i+1)

# Aとansで各要素の一致を確認する
if set(A)==ans:
    # OKなら使用したプレフィックスを出力
    print(s)
else:
    print(-1)
