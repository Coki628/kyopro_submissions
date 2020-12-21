"""
・自力AC！
・数列数え上げ、パスカルの三角形
・題意の操作を考えると、パスカルの三角形みたいな動きになると気づく。
・するとそれぞれの値は、左に足されるか右に足されるかで、ちょうど経路の通り数で
　矢印の向き2方向でやる時みたいなnCrを使って、合計何回使われるかを求められる。
・各使用回数が分かれば、後は元の値と掛けるだけ。
・このパスカルの三角形を経路の通り数の考え方を結びつけるのは、いつかのAGCでやった。(AGC043B)
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
INF = 10 ** 19
MOD = 10 ** 9 + 7
EPS = 10 ** -10

class ModTools:
    """ 階乗・逆元用のテーブルを構築する """

    def __init__(self, MAX, MOD):

        # nCrならn、nHrならn+rまで作る
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

N = INT()
A = LIST()

C = [0] * N
mt = ModTools(N, MOD)
for i in range(N):
    C[i] = mt.nCr(N-1, i)

ans = 0
for i in range(N):
    ans += A[i] * C[i]
    ans %= MOD
print(ans)
