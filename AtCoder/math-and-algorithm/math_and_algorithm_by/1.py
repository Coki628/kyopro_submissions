# ・これは結局WA。精度高めていくらかWAが減ったけど、
# 　これより精度高めるとTLEにもなるし、そもそもWAも減らなかった。

from decimal import Decimal, getcontext

getcontext().prec = 1000

a, b, c = map(Decimal, input().split())

log10a = a.log10() / Decimal(2).log10()
log10c = c.log10() / Decimal(2).log10()

if log10a < b*log10c:
    print("Yes")
else:
    print("No")
