# -*- coding: utf-8 -*-

"""
・WA。。
"""

import sys
from collections import Counter
from heapq import heappop, heappush, heapify

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
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

S = input()

C = Counter(S)
que = []
evens = []
for k, v in C.items():
    if v%2 == 0:
        evens.append(v)
    else:
        que.append(v)

if not len(que):
    print(len(S))
    exit()

heapify(que)
evens.sort()
while len(evens):
    odd = heappop(que)
    even = evens.pop(-1)
    heappush(que, odd+even)

print(heappop(que))
