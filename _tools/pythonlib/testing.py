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
INF = 2**63 - 1
MOD = 10**9 + 7
EPS = 10**-10

def mk_int(N, lo, hi):
    from random import randint

    return [randint(lo, hi) for i in range(N)]

def mk_perm(N):
    from random import sample

    return sample(range(1, N+1), k=N)

# 直線グラフ
def mk_g1(N):
    nodes = [[] for i in range(N)]
    for i in range(N-1):
        nodes[i].append(i+1)
        nodes[i+1].append(i)
    return nodes

# 完全二分木
def mk_g2(N):
    nodes = [[] for i in range(N)]
    for i in range(1, N):
        j = (i-1) // 2
        nodes[i].append(j)
        nodes[j].append(i)
    return nodes

# スターグラフ
def mk_g3(N):
    nodes = [[] for i in range(N)]
    for i in range(1, N):
        nodes[0].append(i)
        nodes[i].append(0)
    return nodes

# 完全グラフ
def mk_g4(N):
    nodes = [[] for i in range(N)]
    for i in range(N):
        for j in range(i+1, N):
            nodes[i].append(j)
            nodes[j].append(i)
    return nodes

# その他一般グラフ(連結、2重辺・自己ループなし)
def mk_g5(N, M):
    from random import randrange

    nodes = [[] for i in range(N)]
    for i in range(N-1):
        nodes[i].append(i+1)
        nodes[i+1].append(i)
    m = N - 1
    while m < M:
        a, b = randrange(0, N), randrange(0, N)
        if a == b or a in nodes[b]:
            continue
        nodes[a].append(b)
        nodes[b].append(a)
        m += 1
    return nodes

# その他一般グラフ(連結、2重辺・自己ループなし、重み付き)
def mk_g6(N, M, C):
    from random import randrange

    nodes = [[] for i in range(N)]
    for i in range(N-1):
        c = randrange(0, C+1)
        nodes[i].append((i+1, c))
        nodes[i+1].append((i, c))
    m = N - 1
    while m < M:
        a, b, c = randrange(0, N), randrange(0, N), randrange(0, C+1)
        if a == b or a in nodes[b]:
            continue
        nodes[a].append((b, c))
        nodes[b].append((a, c))
        m += 1
    return nodes

# N = INT()
# A = mk_int(N, 0, 20)
# A = mk_perm(N)
# print(A)

# res = mk_g5(4, 6)
# print()
