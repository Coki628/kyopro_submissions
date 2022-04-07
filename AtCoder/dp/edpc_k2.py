# -*- coding: utf-8 -*-

"""
参考：https://kyopro-friends.hatenablog.com/entry/2019/01/12/231000
　　　https://www.hamayanhamayan.com/entry/2019/01/09/002200
・ゲームDP
・後退解析：負け状態を押し付けられるかどうか
・pypyで0.4秒くらいでAC
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

N, K = MAP()
aN = LIST()

# メモ[山の残数] = 今の手番が勝てるか
dp = [False] * (K+1)
# 残数0は負け確定
dp[0] = False

for i in range(1, K+1):
    for j in range(N):
        # j枚取った時、負け状態に出来るなら、それを取ればいいので今の手番は勝てる
        if i-aN[j] >= 0 and dp[i-aN[j]] == 0:
            dp[i] = True
            break
if dp[K]:
    print('First')
else:
    print('Second')
