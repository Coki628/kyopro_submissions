"""
・きっちり自力AC！
・確率系
・カードの種類は9つしかないので、両方がそれぞれ1~9を全部調べても9*9通り。
　カードを決めたら実際にシミュして先手が勝つならそうなる確率を足せばいい。
"""

import sys

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
sys.setrecursionlimit(10**6)
INF = 10**18
MOD = 10**9 + 7
EPS = 10**-10

N = 10
K = INT()
S = input()
T = input()
A = list(map(int, S[:4]))
B = list(map(int, T[:4]))
C = [0] * N
for a in A:
    C[a] += 1
for b in B:
    C[b] += 1

def check(A, B):
    C1 = [0] * N
    C2 = [0] * N
    for a in A:
        C1[a] += 1
    for b in B:
        C2[b] += 1
    cnt1 = 0
    cnt2 = 0
    for i in range(1, N):
        cnt1 += i*10**C1[i]
        cnt2 += i*10**C2[i]
    return cnt1 > cnt2

ans = 0
total = 9*K-8
for i in range(1, N):
    if C[i] == K:
        continue
    # 先手がカードiを引く確率
    p1 = (K-C[i])/total
    A.append(i)
    C[i] += 1
    total -= 1
    for j in range(1, N):
        if C[j] == K:
            continue
        B.append(j)
        if check(A, B):
            # 後手がカードjを引く確率
            p2 = (K-C[j])/total
            ans += p1*p2
        B.pop()
    # 適切に状態を戻す
    A.pop()
    C[i] -= 1
    total += 1
print(ans)
