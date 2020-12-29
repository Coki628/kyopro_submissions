"""
参考：https://atcoder.jp/contests/past202012-open/editorial
　　　他の人の提出とか
・区間DP
・iwiとほぼ一緒は確かにそう。解説見ても、方針に概ね間違いはなさそう。何が間違っていたか。
・iwiは(多分)1文字目と3文字目が同じだから、iw***iとi***wiの形だけ見ればよかったけど、
　今回は文字にそういう定めはないので、a***b***cという形があり得る。ここが違った。
・なのである区間を定める時、真ん中の文字として区間内を全部チェックする必要があったんだね。
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
S = input()
T = input()

memo = list2d(N+1, N+1, -1)
def rec(l, r):
    if memo[l][r] != -1: 
        return memo[l][r]

    # 区間が3以下の場合はすぐ結果を返す
    if r-l == 3:
        if S[l:r] == T:
            memo[l][r] = 1
            return 1
        else:
            memo[l][r] = 0
            return 0
    elif r-l < 3:
        memo[l][r] = 0
        return 0
    
    # [l,m)と[m,r)の全てから最適な値を集めてくる
    res = -INF
    for m in range(l+1, r):
        res = max(res, rec(l, m)+rec(m, r))
    
    # 連鎖の可能性がある場合
    for m in range(l+1, r-1):
        # T[0]***(全消し)***T[1]***(全消し)***T[2]が成立するなら+1
        if (r-l) % 3 == 0 and S[l] == T[0] and S[m] == T[1] and S[r-1] == T[2] \
                and (r-l)//3-1 == rec(l+1, m) + rec(m+1, r-1):
            res = max(res, rec(l+1, m) + rec(m+1, r-1) + 1)

    memo[l][r] = res
    return res

print(rec(0, N))
