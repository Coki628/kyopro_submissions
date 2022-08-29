"""
・さくっと自力AC
・N進法
・今回は36進法。36個の割り当てを先に作って、後は作ってあるやつ持ってきて中身ちょっといじる。
"""

import sys
from string import digits, ascii_uppercase

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

nums = digits + ascii_uppercase

def dton(num, n):
    res = []
    while abs(num) > 0:
        m = num % abs(n)
        num -= m
        res.append(nums[m])
        num //= n
    res = ''.join(map(str, res))[::-1]
    if res:
        return res
    else:
        return '0'

N = INT()
ans = dton(N, 36)
print(ans)
