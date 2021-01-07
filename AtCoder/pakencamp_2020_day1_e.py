"""
参考：https://atcoder.jp/contests/pakencamp-2020-day1/editorial
・自力ならず。。
・実験、場合分け、MODの性質
・実験すると何とか特徴は見えてくる。
　それでもすごい頑張って場合分けしないといけなかった。。
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

# ・実験より、以下の特徴が分かってくる。
# ・簡単のためa<=bとして
# 　・x,yともにaより大きくはならない
# 　・基本的には x=a, y=(b-a)%a
# 　・ただしa=bなら常にx,y両方0
# ・よって、x>yとして
# 　・a=xにして、差分がyになるようなbにする
# 　・つまりy=b-xを移項してb=x+y
# 　・ただしx=yは0の時しかできない
# 　・ただしx,yどちらかだけ0の時はこのルール通りに行ってくれないのでさらに場合分け

# for a in range(1, 41):
#     for b in range(a, 41):
#         x = a % b
#         y = b % a
#         print('a: {0}, b: {1}, x: {2}, y: {3}'.format(a, b, x, y))

x, y = MAP()

if x == y == 0:
    print(1, 1)
elif x == y:
    print(-1)
elif y == 0:
    a = x
    b = x*2
    print(a, b)
elif x == 0:
    b = y
    a = y*2
    print(a, b)
elif x > y:
    a = x
    b = x+y
    print(a, b)
else:
    b = y
    a = x+y
    print(a, b)
