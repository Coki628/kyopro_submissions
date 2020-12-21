# -*- coding: utf-8 -*-

"""
・累積和
・二分探索
・速攻自力AC！
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
def ceil(x, y=1): return int(-(-x // y))
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

N = INT()
A = LIST()
B = LIST()

good = []
bad = []
for i in range(N):
    need = A[i] - B[i]
    if need >= 0:
        good.append(need)
    else:
        bad.append(need)

if sum(good) + sum(bad) < 0:
    print(-1)
    exit()

good.sort(reverse=True)
# このあとの二分探索用に累積和にする
good.insert(0, 0)
for i in range(len(good)-1):
    good[i+1] += good[i]

# badを補填するために必要なgoodの数 + badの総数
print(bisect_left(good, -sum(bad)) + len(bad))
