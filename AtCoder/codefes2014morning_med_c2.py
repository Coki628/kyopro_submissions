"""
・試験管青diff残埋め
・きっちり自力AC！
・行列累乗、誤差対策
・C++がldでも落ちるのでこっちで。多分行列累乗にDecimalで実数乗せたのは初めてだけど、
　さすがDecimalの精度は信頼できる。きっちりAC。
　Decimalは速度面が心配だけど、今回はTLもきつくない2^3*log(N^18)の一発だけなので余裕。
"""

import sys
from decimal import Decimal

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

def mat_pow(mat, init, K):
    """ 行列累乗 """

    def mat_dot(A, B):
        """ 行列の積 """

        # 1次元リストが来たら2次元の行列にする
        if not isinstance(A[0], list) and not isinstance(A[0], tuple):
            A = [A]
        if not isinstance(B[0], list) and not isinstance(A[0], tuple):
            B = [[b] for b in B]
        n1 = len(A)
        n2 = len(A[0])
        _ = len(B)
        m2 = len(B[0])
        res = list2d(n1, m2, 0)
        for i in range(n1):
            for j in range(m2):
                for k in range(n2):
                    res[i][j] += A[i][k] * B[k][j]
        return res

    def _mat_pow(mat, k):
        """ 行列matをk乗する """

        n = len(mat)
        res = list2d(n, n, 0)
        for i in range(n):
            res[i][i] = 1
        # 繰り返し二乗法
        while k > 0:
            if k & 1:
                res = mat_dot(res, mat)
            mat = mat_dot(mat, mat)
            k >>= 1
        return res

    # 行列累乗でK項先へ    
    res = _mat_pow(mat, K)
    # 最後に初期値と掛ける
    res = mat_dot(res, init)
    return [a[0] for a in res]

p, N = map(Decimal, input().split())

mat = [
    [1-p, p],
    [p, 1-p],
]
init = [1, 0]

res = mat_pow(mat, init, int(N))
ans = res[1]
print(ans)
