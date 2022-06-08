"""
参考：https://atcoder.jp/contests/pakencamp-2020-day1/editorial
・自力ならず。終了後頑張ったけどWA取れなくて解説見た。結局自分の方針のまま通したけど。
・ビット毎に見る
・それぞれにビットについて、
　・Aで立っていたら最低1要素は立つ、寝ていたら全要素寝る
　・Bで立っていたら全要素立つ、寝ていたら最低1要素は寝る
　・Cで立っていたら奇数個の要素で立つ、寝ていたら偶数個の要素で立つ
　が言える。
・各ビットでA,B,Cどれが立っているかが8通りのどれなのかを出して、
　全要素立つかつ全要素寝る、みたいな矛盾した組があったらその時点で即NG確定、
　XORとの兼ね合いで要素数の偶奇が固定される場合があるので、
　その要素数偶奇の固定が矛盾するビットがあったら、最後にチェックしてNG判定。それ以外はOK。
・8通りのパターンの内訳は自分ノート参照。
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
sys.setrecursionlimit(10**6)
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

MXLOG = 60

for _ in range(INT()):
    abc = LIST()

    ok = 1
    ln = set()
    for k in range(MXLOG):
        bit = 0
        for i in range(3):
            if abc[i]>>k & 1:
                bit |= 1<<i
        # 明らかに無理なパターン
        if bit in [2, 4, 6]:
            ok = 0
            break
        # このビットは[1,1,1,1]にしたいので要素数は4確定
        elif bit == 3:
            ln.add(4)
        # このビットは[1,1,1]にしたいので要素数は3確定
        elif bit == 7:
            ln.add(3)
    if not ok or len(ln) >= 2:
        No()
    else:
        Yes()
