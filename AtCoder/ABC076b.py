# -*- coding: utf-8 -*-

N = int(input())
K = int(input())

ans = 1
for i in range(N):

    if ans * 2 <= ans + K:
        ans *= 2
    else:
        ans += K
print(ans)