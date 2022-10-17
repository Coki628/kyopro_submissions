"""
・四捨五入
・つらい。C++で下位桁から決めようとしたら繰り上がりが連続した時どうなるかで脳が破壊されて、
　PythonのDecimalでやろうとしたら桁指定が小数点以下しかできなくて、たまらず後回しに。
　最後に戻ってきて、小数側に20桁くらいずらしてやって戻した。
"""

import sys
from decimal import Decimal, ROUND_HALF_UP

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

x, k = MAP()

x = Decimal(x)
x /= pow(10, 20)
for i in range(k):
    x = x.quantize(Decimal(str(pow(10, i+1-20))), ROUND_HALF_UP)
x *= pow(10, 20)
x = int(x)
print(x)
