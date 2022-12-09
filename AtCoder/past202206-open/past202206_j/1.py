"""
・きっちり自力AC。
・日付管理
・ちょっとC++で頑張ってみようか考えたけど不毛に思えてpythonのdatetimeとtimedelta。
"""

import sys
from datetime import datetime, timedelta

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

S = input()
T = input()

y1, m1, d1 = map(int, S.split('-'))
y2, m2, d2 = map(int, T.split('-'))

cur = datetime(y1, m1, d1)
goal = datetime(y2, m2, d2)
ans = 0
while 1:
    wd = cur.weekday()
    if wd == 5 or wd == 6:
        ans += 1
    if cur == goal:
        break
    cur += timedelta(days=1)
print(ans)
