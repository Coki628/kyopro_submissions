# -*- coding: utf-8 -*-

import sys

def input(): return sys.stdin.readline().strip()
def list2d(a, b, c): return [[c] * b for i in range(a)]
def list3d(a, b, c, d): return [[[d] * c for j in range(b)] for i in range(a)]
def list4d(a, b, c, d, e): return [[[[e] * d for j in range(c)] for j in range(b)] for i in range(a)]
def ceil(x, y=1): return int(-(-x // y))
def INT(): return int(input())
def MAP(): return map(int, input().split())
def LIST(N=None): return list(MAP()) if N is None else [INT() for i in range(N)]
def Yes(): print('Yes')
def No(): print('No')
def YES(): print('YES')
def NO(): print('NO')
sys.setrecursionlimit(10 ** 9)
INF = 10 ** 18
MOD = 10 ** 9 + 7

S = input()
N = len(S)

ans = INF
for i in range(1, N-1):
    if S[i] == 'w':
        cnt = 0
        for j in range(i-1, -1, -1):
            if S[j] == 'c':
                cnt += i - j
                break
        else:
            cnt = INF
        for j in range(i+1, N):
            if S[j] == 'w':
                cnt += j - i
                break
        else:
            cnt = INF
        ans = min(ans, cnt + 1)
if ans == INF:
    print(-1)
else:
    print(ans)
