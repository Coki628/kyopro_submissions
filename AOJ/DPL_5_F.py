"""
・写像12相勉強会
・6相
・これもしっかり自力AC
・包除原理、重複組み合わせ
・基本方針は3相と全く同じ。ボールの並びが関係なくなるので、そこだけ数え方が変わる。
　これも、3相でのその部分がほぼ1相だったのと同じように、4相と同じ重複組み合わせになる。
"""

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
EPS = 10 ** -10

class ModTools:
    """ 階乗・逆元用のテーブルを構築する """

    def __init__(self, MAX, MOD):
        
        MAX += 1
        self.MAX = MAX
        self.MOD = MOD
        factorial = [1] * MAX
        factorial[0] = factorial[1] = 1
        for i in range(2, MAX):
            factorial[i] = factorial[i-1] * i % MOD
        inverse = [1] * MAX
        inverse[MAX-1] = pow(factorial[MAX-1], MOD-2, MOD)
        for i in range(MAX-2, -1, -1):
            inverse[i] = inverse[i+1] * (i+1) % MOD
        self.fact = factorial
        self.inv = inverse
    
    def nCr(self, n, r):
        """ 組み合わせ """

        if n < r: return 0
        r = min(r, n-r)
        numerator = self.fact[n]
        denominator = self.inv[r] * self.inv[n-r] % self.MOD
        return numerator * denominator % self.MOD

    def nHr(self, n, r):
        """ 重複組み合わせ """

        return self.nCr(r+n-1, r)

    def nPr(self, n, r):
        """ 順列 """

        if n < r: return 0
        return self.fact[n] * self.inv[n-r] % self.MOD

    def div(self, x, y):
        """ MOD除算 """

        return x * pow(y, self.MOD-2, self.MOD) % self.MOD

N, K = MAP()

mt = ModTools(N+K+1, MOD)
ans = 0
# 使わない箱がi個ある場合を順番にやる
for i in range(K+1):
    if i % 2 == 0:
        # K個の箱から使わないi個を選ぶ * K-i個の箱にN個のボールを割り当てる
        ans += mt.nCr(K, i) * mt.nHr(K-i, N) % MOD
    else:
        ans -= mt.nCr(K, i) * mt.nHr(K-i, N) % MOD
print(ans%MOD)
