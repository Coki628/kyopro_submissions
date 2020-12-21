# -*- coding: utf-8 -*-

"""
参考：submission:49577168
・ビットが全1だったら、xorの結果とandの結果で各ビットを分け合うことになる。
・xorの結果 => a-b andの結果 => b
・aをなるべく大きく割り切れるように分けると最適なbを作れる。
・探す範囲は約数列挙の時とかと一緒で、√aまででOK。
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

Q = INT()
for i in range(Q):
    a = INT()
    bin_a = format(a, 'b')
    if '0' in bin_a:
        bin_a = bin_a.replace('0', '1')
        print(int(bin_a, 2))
    else:
        # ビットが全1だったら、aをなるべく大きく分割する
        for i in range(2, int(sqrt(a))+2):
            if a % i == 0:
                print(a // i)
                break
        else:
            print(1)
