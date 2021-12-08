"""
参考：https://img.atcoder.jp/intro-heuristics/editorial.pdf
・マラソン、局所探索法(焼きなまし法)
・山登りは基本的に結果が良くなった時しか採用しないが、
　焼きなましは結果が悪くなっても確率で採用する。
　この確率というのが、時間制限までの時間が長いほど高く、
　短くなると低くなって山登りに近くなる。
　こうすることで、前半で中途半端な局所解にハマって抜けなくなるケースを減らせるそう。
・これでスコアが1億2200万くらい。
"""

import sys
from time import time
from random import randrange, random
from bisect import bisect_left
from math import exp

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
INF = 10 ** 19
MOD = 10 ** 9 + 7
EPS = 10 ** -10

def deepcopy(li): return [x[:] for x in li]

def get_sum(a, d, n):
    """ 等差数列の和：(初項a, 公差d, 項数n) """
    return (2*a + (n-1)*d) * n // 2

TL = 1.8
start = time()

D = INT()
M = 26
C = LIST()
S = [[]] * (D+1)
S[0] = [0] * M
for i in range(1, D+1):
    S[i]  = LIST()

def check(i, score, t, last):
    score += S[i][t]
    for j in range(M):
        last[j] += 1
    last[t] = 0
    for j in range(M):
        score -= C[j] * last[j]
    return score

# 初期状態を貪欲で生成
last = [0] * M
T = [0]
adjli = [[0] for i in range(M)]
score = 0
for i in range(D):
    mx = -INF
    idx = -1
    for t in range(M):
        res = check(i, score, t, last[:])
        if res > mx:
            mx = res
            idx = t
    t = idx
    score += S[i][t]
    for j in range(M):
        last[j] += 1
    last[t] = 0
    for j in range(M):
        score -= C[j] * last[j]
    T.append(t)
for d, t in enumerate(T[1:], 1):
    adjli[t].append(d)
for i in range(M):
    adjli[i].append(D+1)

# day日目のコンテストをaからbに変更する
def change(day, a, b):
    res = 0
    # コンテストaのコストを再計算
    res -= S[day][a]
    di = adjli[a].index(day)
    for i in range(di, di+2):
        curd = adjli[a][i-1]
        nxtd = adjli[a][i]
        cnt = nxtd - curd
        res += C[a] * get_sum(0, 1, cnt)
    adjli[a].pop(di)
    curd = adjli[a][di-1]
    nxtd = adjli[a][di]
    cnt = nxtd - curd
    res -= C[a] * get_sum(0, 1, cnt)

    # コンテストbのコストを再計算
    res += S[day][b]
    di = bisect_left(adjli[b], day)
    curd = adjli[b][di-1]
    nxtd = adjli[b][di]
    cnt = nxtd - curd
    res += C[b] * get_sum(0, 1, cnt)
    adjli[b].insert(di, day)
    for i in range(di, di+2):
        curd = adjli[b][i-1]
        nxtd = adjli[b][i]
        cnt = nxtd - curd
        res -= C[b] * get_sum(0, 1, cnt)

    return res

# d1日目とd2日目のコンテストを入れ替える
def swap(d1, d2):
    res = 0
    res += change(d1, T[d1], T[d2])
    res += change(d2, T[d2], T[d1])
    return res

# 焼きなましに使う温度の計算
T0 = 2000
T1 = 600
def calc_temp():
    t = (time()-start) / TL
    if t >= 1:
        return -1
    return T0**(1-t)*T1**t

# 焼きなましを踏まえた採用確率の計算
def calc_prob(score, t):
    if score > 0:
        return 1
    return exp(score/t)

# 時間ギリギリまでランダムな交換を試す
cnt = 0
temp = T0
while 1:
    cnt += 1
    if cnt%100 == 0:
        # 温度の更新
        temp = calc_temp()
        if temp == -1:
            break

    # 1点更新と2点スワップのどちらかをやる
    p = randrange(0, 2)
    if p:
        d, q = randrange(1, D+1), randrange(0, M)
        if T[d] == q:
            continue

        tmp = deepcopy(adjli)
        res = change(d, T[d], q)
        # 焼きなましの評価によって採用を決める
        if calc_prob(res, temp) >= random():
            score += res
            T[d] = q
        # 悪ければ状態を戻す
        else:
            adjli = tmp
    else:
        # 離れる最大日数
        mxdiff = 16
        d1 = randrange(1, D+1)
        d2 = randrange(d1, min(d1+mxdiff, D+1))
        if d1 == d2:
            continue

        tmp = deepcopy(adjli)
        res = swap(d1, d2)
        if calc_prob(res, temp) >= random():
            score += res
            T[d1], T[d2] = T[d2], T[d1]
        else:
            adjli = tmp

for t in T[1:]:
    print(t+1)
