# -*- coding: utf-8 -*-

"""
・15パズル
・8パズルと同じやつで取りあえず投げたら当然のTLE
"""

import sys
from collections import deque

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

N = 4
# グリッドを最初から文字列として1次元で保持する
grid = '*' * (N+2)
for i in range(N):
    row = list(input().split())
    for j, num in enumerate(row):
        row[j] = format(int(num), 'x')
    grid += '*' + ''.join(row) + '*'
grid += '*' * (N+2)
start = grid.find('0')

# 完成形の盤面
goal = '*******1234**5678**9abc**def0*******'
que = deque()
que.append((grid, 0, start))
# その盤面に至る移動コスト
memo = {}
while len(que):
    grid, cost, cur = que.popleft()
    if grid in memo:
        continue
    memo[grid] = cost
    grid = list(grid)
    # 4方向見る
    for direction in (-1, 1, -(N+2), N+2):
        nxt = cur + direction
        if grid[nxt] != '*':
            grid[cur], grid[nxt] = grid[nxt], grid[cur]
            que.append((''.join(grid), cost+1, nxt))
            grid[cur], grid[nxt] = grid[nxt], grid[cur]

print(memo[goal])
