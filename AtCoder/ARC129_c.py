"""
参考：みんなのツイートとか
・自力ならず。。
・三角数定理
・三角数(a*(a+1)/2とかで出る数)について、3つ以下(重複はあり)で任意の正整数を表せる。
　ちゃんと3つでやるにはもっと工夫が要るっぽいけど、
　今回の条件なら構築方法は2冪でやる時と一緒で大きい方から貪欲でOK。
　それでも大した数にならないそう。(なんか最大7回って誰かが言ってた気がする。)
　これが分かると、この問題も7を連続させてできるだけ稼いで、間に適当な数を挟む、でいける。
　適当な数は、本当はちゃんと正しく決める方法があるっぽいけど、
　そもそも7回くらいしかやらないのであれば、区切る都度、1～9までの数で、
　その数を付けた時に新しく発生する部分列を全探索しても間に合ってしまう。
　これで大丈夫だった数を使う。この探索で雑にでかい桁への演算を扱うためにpythonでやった。
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

def calc(a):
    return (a+1)*a//2

N = INT()

cur = 0
ans = ''
i = 2000
while cur < N:
    while cur+calc(i) > N:
        i -= 1
    ans += '7'*i
    cur += calc(i)
    for d in range(1, 10):
        if d == 7:
            continue
        ok = True
        for j in range(len(ans)):
            num = int(ans[j:]+str(d))
            if num%7 == 0:
                ok = False
                break
        if ok:
            ans += str(d)
            break
print(ans)

# M = len(ans)
# cnt = 0
# for i in range(M):
#     for j in range(i+1, M+1):
#         num = int(ans[i:j])
#         if num%7 == 0:
#             if num != 7 and list(set(str(num))) != ['7']:
#                 print(num)
#             cnt += 1
# print(ans)
# if cnt == N:
#     Yes()
# else:
#     No()
#     print(cnt)
