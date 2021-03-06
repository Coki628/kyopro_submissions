"""
・VisibleはAC！
・最初Hiddenも考えてて、オーバーフロー気にしないで雑に操作できるように
　pythonで書いてたのをそのまま使った。
・答えとなりうる数を必要な最大値まで全列挙。
　pythonは値と文字列の変換が雑にできるのは楽でいいよね。
"""

import sys
from bisect import bisect_right

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
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

MX = 10**9
li = []
for d in range(2, 10):
    i = 1
    while 1:
        num = ''
        for j in range(d):
            num += str(i+j)
        num = int(num)
        if num > MX: break
        li.append(num)
        i += 1
li.sort()

for c in range(1, INT()+1):
    y = INT()

    x = bisect_right(li, y)
    ans = li[x]
    ans = 'Case #{0}: {1}'.format(c, ans)
    print(ans)
