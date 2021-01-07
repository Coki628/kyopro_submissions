"""
参考：https://atcoder.jp/contests/pakencamp-2020-day1/editorial
・自力ならず。
・実はよくよく考えると、その時にどれくらい増えるのかは、全要素分まとめて計算できる。
・加算部分は全要素に+A[i]したいので、その時点での要素数2^iをA[i]に掛ければいいし、
　のびたすの桁ずらし部分は全要素に*10^|A[i]|したいので、10^|A[i]|をその時点での総和に掛ければいい。
・なんとなく桁ずらし部分は前の状態に絡むので、個々の状態をまとめられないような気がしてしまったけど、
　全ての要素に対して桁ずらしの掛け算をやるので、総和に対してやっても同じだった。
　こういう考察ちゃんとできるようにしないとなー。。
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

Q, x = MAP()
A = LIST(Q)

dp = [0] * (Q+1)
dp[0] = x
for i in range(Q):
    # 前の状態 + 普通の加算 + のびたすの桁ずらし + のびたすの加算
    dp[i+1] = dp[i] + A[i]*pow(2, i, MOD) + pow(10, len(str(A[i])), MOD)*dp[i] + A[i]*pow(2, i, MOD)
    dp[i+1] %= MOD
ans = dp[Q]
print(ans)
