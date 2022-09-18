"""
・自力AC！
・pythonでdatetime使った。適当に2020年使ったら閏年で1ペナ…。
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

class Solution:
    def countDaysTogether(self, arriveAlice: str, leaveAlice: str, arriveBob: str, leaveBob: str) -> int:
        m1, d1 = map(int, arriveAlice.split('-'))
        m2, d2 = map(int, leaveAlice.split('-'))
        m3, d3 = map(int, arriveBob.split('-'))
        m4, d4 = map(int, leaveBob.split('-'))

        fr1 = datetime(2021, m1, d1)
        to1 = datetime(2021, m2, d2)
        fr2 = datetime(2021, m3, d3)
        to2 = datetime(2021, m4, d4)

        cur = datetime(2021, 1, 1)
        res = 0
        while cur.year == 2021:
            if fr1 <= cur <= to1 and fr2 <= cur <= to2:
                res += 1
            cur += timedelta(days=1)
        return res
