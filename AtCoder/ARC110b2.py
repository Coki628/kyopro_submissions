"""
参考：https://atcoder.jp/contests/arc110/editorial
　　　他、ツイートなど。
・強引に通した感じだったので、想定解に近い感じのを。
・とりあえず長さ2以下のOKケースは場合分け。
・基本的には3個ずつずらしてたくさん置けるので、Tの長さNによってKからどのくらい減らすかを考える。
・開始位置の110,101,011によって分けて、手前を削って全部110スタートっぽくして見通しをよくする。
・あとは後ろがどうなるか、手元で書いて試してみると、割る3切り上げでいけそう、となる。
・でもこれ本番で落ち着いて考察してちゃんと整えるの大変そう。。
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

N = INT()
T = input()

K = 10**10
mod = 3
S = '110'

if T == '1':
    print(K*2)
    exit()
if T == '11' or T == '10' or T == '0':
    print(K)
    exit()

def check(m):
    for i in range(N):
        if T[i] != S[(i+m)%mod]:
            return False
    return True

for m in range(mod):
    if check(m):
        # Tのプレフィックスを削る
        N -= 3-m
        # どちらも110スタートと考えて、残りのTの長さに応じて減らす
        ans = K - ceil(N, 3)
        print(ans)
        break
else:
    print(0)
