"""
・すごく考えて、自力AC？自信ない。問題公開されたら投げる。
・周期系、逆操作
・数字が来た時は、現在の文字列がそのまま2〜10倍に増える感じになる。
　この増えた時にKをオーバーしたら、その増やす前の文字列の周期の中に該当位置があることになる。(多分)
・なので後ろから見ていって周期の範囲を狭めていって、ぴったりの位置に来た文字が答え。(多分)
　→TLEなので、再考する。。
・ちょっと直してAC。明らかにでかすぎる値が来る時もあるので、
　K番目を過ぎたところで合計数えるのを途中で打ち切って、そこから戻って探すようにしたらAC。
"""

import sys
from string import digits

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

S = input()
K = INT()
N = len(S)

K -= 1
total = 0
for i, s in enumerate(S):
    if s in digits:
        s = int(s) + 1
        total *= s
    else:
        total += 1
    if total > K:
        end = i + 1
        break
else:
    end = N

cur = total
for i in range(end-1, -1, -1):
    if S[i] in digits:
        a = int(S[i]) + 1
        cur //= a
        if K >= cur:
            K %= cur
    else:
        cur -= 1
        if cur == K:
            print(S[i])
            break
