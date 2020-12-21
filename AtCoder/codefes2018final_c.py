# -*- coding: utf-8 -*-

"""
・二分探索
・速攻自力AC、やっぱ300点はこうでないとね。
"""

import sys, re
from collections import deque, defaultdict, Counter
from math import sqrt, hypot, factorial, pi, sin, cos, radians, log10
if sys.version_info.minor >= 5: from math import gcd
else: from fractions import gcd 
from heapq import heappop, heappush, heapify, heappushpop
from bisect import bisect_left, bisect_right
from itertools import permutations, combinations, product
from operator import itemgetter, mul
from copy import copy, deepcopy
from functools import reduce, partial
from fractions import Fraction
from string import ascii_lowercase, ascii_uppercase, digits

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def round(x): return int((x*2+1) // 2)
def fermat(x, y, MOD): return x * pow(y, MOD-2, MOD) % MOD
def prod(nums): return reduce(mul, nums, 1)
def lcm(x, y): return (x * y) // gcd(x, y)
def lcm_list(nums): return reduce(lcm, nums, 1)
def gcd_list(nums): return reduce(gcd, nums, nums[0])
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(): return list(map(int, input().split()))
sys.setrecursionlimit(10 ** 9)
INF = float('inf')
MOD = 10 ** 9 + 7

N = INT()
plans = [[0] * 2 for i in range(N)]
for i in range(N):
    plans[i][0], plans[i][1] = MAP()

plans.sort(key=itemgetter(0))

def calc(idx):
    return plans[idx][1] + max((m - plans[idx][0]), 0)

M = INT()
for _ in range(M):
    m = INT()
    idx = bisect_left(plans, [m, 0])
    if idx == N:
        print(calc(idx-1))
    elif idx == 0:
        print(calc(idx))
    else:
        print(min(calc(idx), calc(idx-1)))
