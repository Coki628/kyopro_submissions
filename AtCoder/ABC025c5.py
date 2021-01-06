"""
参考：https://ja.wikipedia.org/wiki/%E3%82%A2%E3%83%AB%E3%83%95%E3%82%A1%E3%83%BB%E3%83%99%E3%83%BC%E3%82%BF%E6%B3%95#:~:text=%E3%82%A2%E3%83%AB%E3%83%95%E3%82%A1%E3%83%BB%E3%83%99%E3%83%BC%E3%82%BF%E6%B3%95%EF%BC%88%E2%80%94%20%E3%81%BB%E3%81%86,%E6%9E%9D%E5%88%88%E3%82%8A%E3%81%97%E3%81%A6%E3%81%84%E3%82%8B%E3%80%82
・蟻本演習4-5-2
・ゲームDP、ミニマックス法、枝刈り探索、α-β法
・wikiにいい感じの疑似コードがあったのでそっちに合わせたけど、
　基本的にはABC078dで試したのと同じことをしてる。
・これがメモ化再帰と合わせると答え合わない。なんでかなーって思ったけど、
　確かに盤面が一緒でも、その時点でのα-βが違えば枝刈り具合が変わってくるはずなので、
　同じ局面だからといってメモ通りに省略しちゃうとまずいケースがあるのかなってお気持ち。
　α-βの値までメモに入れたらうまくいきそうな気もするけど、
　そこまでメモしちゃったら本末転倒っぽいのでやってない。
・速度的には、メモなし愚直：0.95秒、メモ化再帰：0.05秒、メモなしα-β枝刈り：0.14秒って感じで、
　メモ化するよりは遅いけど、かなり速くはなるって感じ。併用できたらよかったのになー。
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
INF = float('inf')
MOD = 10 ** 9 + 7

B = []
B.append(LIST())
B.append(LIST())
C = []
C.append(LIST())
C.append(LIST())
C.append(LIST())

total = sum(B[0]+B[1]+C[0]+C[1]+C[2])

def calc(state):
    res = 0
    for j in range(3):
        for i in range(2):
            if state[i*3+j] == state[(i+1)*3+j]:
                res += B[i][j]
    for i in range(3):
        for j in range(2):
            if state[i*3+j] == state[i*3+(j+1)]:
                res += C[i][j]
    return res

memo = {}
def rec(turn, state, alpha, beta):
    if state in memo:
        return memo[state]
    if turn == 9:
        res = calc(state)
        memo[state] = res
        return res
    state = list(state)
    if turn % 2 == 0:
        for i in range(9):
            if state[i] == '*':
                state[i] = 'o'
                alpha = max(alpha, rec(turn+1, ''.join(state), alpha, beta))
                state[i] = '*'
                if alpha >= beta:
                    break
        # memo[''.join(state)] = alpha
        return alpha
    else:
        for i in range(9):
            if state[i] == '*':
                state[i] = 'x'
                beta = min(beta, rec(turn+1, ''.join(state), alpha, beta))
                state[i] = '*'
                if alpha >= beta:
                    break
        # memo[''.join(state)] = beta
        return beta

ans = rec(0, '*********', 0, total)
print(ans)
print(total-ans)
