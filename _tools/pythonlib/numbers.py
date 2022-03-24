# -*- coding: utf-8 -*-

import sys
# from math import gcd
from functools import reduce

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

# MOD逆元で割り算(MODが素数の時のみ)
def div(x, y, MOD): return x * pow(y, MOD-2, MOD) % MOD

# 非再帰GCD(多分純正は再帰っぽいからこっちのが速いはず)
def gcd(a, b):
    while b: a, b = b, a % b
    return a

# 最小公倍数
def lcm(x, y): return (x * y) // gcd(x, y)
# reduce(使う関数, 足し合わせるリスト, 初期値)
def lcm_list(li): return reduce(lcm, li, 1)
def gcd_list(li): return reduce(gcd, li, 0)

# 素数冪LCM
def lcm(C1, C2):
    for k, v in C2.items():
        C1[k] = max(C1[k], v)
    return C1

# 1からnまでの等差数列の和
def get_sum(n): return (1+n)*n//2

def get_sum(a, l, n):
    """ 等差数列の和：(初項a, 末項l, 項数n) """
    return (a+l) * n // 2

def get_sum(a, d, n):
    """ 等差数列の和：(初項a, 公差d, 項数n) """
    return (2*a + (n-1)*d) * n // 2

# 数値として見れるくらいの値を10万とか100万回くらいやる時はこっち
def digit_sum(n):
    """ 桁和：O(logN) """

    ans = 0
    while n > 0:
        ans += n % 10
        n //= 10
    return ans

# 10万桁とかある時はこっち
def digit_sum(S):
    """ 桁和：O(|S|) """

    res = 0
    for s in S:
        res += int(s)
    return res

def is_prime(num):
    """ 素数判定 """
    from math import sqrt

    if num < 2: 
        return False
    if num in [2, 3, 5]: 
        return True
    if num % 2 == 0 or num % 3 == 0 or num % 5 == 0:
        return False
    # 疑似素数(2でも3でも割り切れない数字)で次々に割っていく
    prime = 7
    step = 4
    num_sqrt = sqrt(num)
    while prime <= num_sqrt:
        if num % prime == 0:
            return False
        prime += step
        step = 6 - step
    return True

def eratosthenes_sieve(n):
    """ 素数列挙(エラトステネスの篩) """

    table = [0] * (n+1)
    prime_list = []
    for i in range(2, n+1):
        if table[i] == 0:
            prime_list.append(i)
            for j in range(i+i, n+1, i):
                table[j] = 1
    return prime_list

def factorize(num: int) -> dict:
    """ 素因数分解 """
    from math import sqrt
    from collections import Counter

    d = Counter()
    # 終点はルート切り捨て+1
    for i in range(2, int(sqrt(num))+1):
        # 素因数分解：小さい方から割れるだけ割って素数をカウント
        while num % i == 0:
            num //= i
            d[i] += 1
        # 1まで分解したら終了
        if num == 1:
            break
    # 最後に残ったnumは素数(ただし1^1は1^0なので数に入れない)
    if num != 1:
        d[num] += 1
    return d

def divisors(N: int) -> set:
    """ 約数の列挙・個数 """
    from math import sqrt

    # 1とその数はデフォで入れとく
    s = {1, N}
    # 終点はルート切り捨て
    for i in range(2, int(sqrt(N))+1):
        # 割り切れるなら、iとN/iを追加
        if N % i == 0:
            s.add(i)
            s.add(N // i)
    return s

# N進数文字列Sを10進数に
def ntod(S, n):
    res = 0
    for k, s in enumerate(S[::-1]):
        res += n**k * int(s)
    return res

# 10進数をN進数文字列に
# def dton(num, n):
#     res = []
#     while num > 0:
#         num, m = divmod(num, n)
#         res.append(m)
#     res = ''.join(map(str, res))[::-1]
#     if res:
#         return res
#     else:
#         return '0'
# 負数対応版
def dton(num, n):
    res = []
    while abs(num) > 0:
        m = num % abs(n)
        num -= m
        res.append(m)
        num //= n
    res = ''.join(map(str, res))[::-1]
    if res:
        return res
    else:
        return '0'

def extgcd(a, b, x=1, y=0):
    """ 拡張ユークリッドの互除法(ax+by=gcd(a, b)の解を求める) """

    if b == 0:
        x = 1
        y = 0
        return (y, x)
    else:
        x, y = extgcd(b, a%b, y, x)
        y -= a // b * x
        return (y, x)

# MOD逆元で割り算(MODが素数でなくても、bとMODが互いに素なら可)
def div(a, b, MOD):
    _, x = extgcd(b, MOD)
    return a*x % MOD

# N以下の自然数でa+b=xを作る通り数
def f(N, x):
    return max(min(x-1, N*2+1-x), 0)
