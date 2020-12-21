# -*- coding: utf-8 -*-

"""
・400点自力AC
・XOR系
・各桁を分けて計算
"""

import sys, re
from collections import deque, defaultdict, Counter
from math import sqrt, hypot, factorial, pi, sin, cos, radians, log10
if sys.version_info.minor >= 5: from math import gcd
else: from fractions import gcd 
from heapq import heappop, heappush, heapify, heappushpop
from bisect import bisect_left, bisect_right
from itertools import permutations, combinations, product, accumulate
from operator import itemgetter, mul, xor
from copy import copy, deepcopy
from functools import reduce, partial
from fractions import Fraction
from string import ascii_lowercase, ascii_uppercase, digits
from datetime import date

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def round(x): return int((x*2+1) // 2)
def fermat(x, y, MOD): return x * pow(y, MOD-2, MOD) % MOD
def lcm(x, y): return (x * y) // gcd(x, y)
def lcm_list(nums): return reduce(lcm, nums, 1)
def gcd_list(nums): return reduce(gcd, nums, nums[0])
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(): return list(map(int, input().split()))
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10 ** 9)
INF = float('inf')
MOD = 10 ** 9 + 7

A,B=MAP()
A-=1
# A-1での各ビットが立つ回数
A2=[0]*50
# Bでの各ビットが立つ回数
B2=[0]*50
ans=0
# ビット毎でループする
for i in range(1, 50):
    T=2**i
    # 循環する分を足す
    A2[i]+=A//T*(T//2)
    # 最後の部分を足す
    A2[i]+=max(A%T-(T//2-1), 0)
    B2[i]+=B//T*(T//2)
    B2[i]+=max(B%T-(T//2-1), 0)
    # A-1で立った数-Bで立った数で[A,B]の区間で立った数にする
    if (B2[i]-A2[i])%2==1:
        # 奇数個立っていたビットの分を足していく
        ans+=2**(i-1)
print(ans)
