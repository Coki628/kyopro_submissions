"""
・さくっと自力AC。1ペナしたけど。。
・操作をした時の価値の変化量的なものを重みにしてソートするといいやつ。
　最初a+bにしちゃったけど、aの分は相手から減って自分に増えるから*2だね。
・とはいえそれもお気持ちでぶん投げる感じではあったけどね。。
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

N = INT()
AB = []
asm = bsm = 0
for i in range(N):
    a, b = MAP()
    asm += a
    AB.append((a*2+b, a, b))

AB.sort(reverse=1)
ans = 0
i = 0
while asm >= bsm:
    asm -= AB[i][1]
    bsm += AB[i][1] + AB[i][2]
    i += 1
    ans += 1
print(ans)
