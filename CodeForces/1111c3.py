# -*- coding: utf-8 -*-

"""
参考：https://codeforces.com/blog/entry/64989
・二分探索を公式解に寄せた版
・累積和とか取らなくてもindexそのまま使えたね…。
・C++でAC、python、pypy共にTLE
・あとメモ取らないと速かった。
"""

import sys, re
from collections import deque, defaultdict, Counter
from math import sqrt, hypot, factorial, pi, sin, cos, radians
if sys.version_info.minor >= 5: from math import gcd
else: from fractions import gcd 
from heapq import heappop, heappush, heapify, heappushpop
from bisect import bisect_left, bisect_right
from itertools import permutations, combinations, product
from operator import itemgetter, mul
from copy import deepcopy
from functools import reduce, partial
from fractions import Fraction
from string import ascii_lowercase, ascii_uppercase, digits

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def ceil(a, b=1): return int(-(-a // b))
def round(x): return int((x*2+1) // 2)
def fermat(x, y, MOD): return x * pow(y, MOD-2, MOD) % MOD
def lcm(x, y): return (x * y) // gcd(x, y)
def lcm_list(nums): return reduce(lcm, nums, 1)
def gcd_list(nums): return reduce(gcd, nums, nums[0])
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(): return list(map(int, input().split()))
sys.setrecursionlimit(10 ** 9)
INF = float('inf')
MOD = 10 ** 9 + 7

N, K, A, B = MAP()
aN = sorted(LIST())

def rec(l, r):

    mn = INF
    baselen = r-l+1
    avgs = bisect_right(aN, r) - bisect_left(aN, l)
    if avgs == 0:
        mn = min(mn, A)
    else:
        mn = min(mn, B * avgs * baselen)
    if baselen >= 2 and avgs != 0:
        mn = min(mn, rec(l+baselen//2, r) + rec(l, r-baselen//2))
    return mn

print(rec(1, 2**N))
