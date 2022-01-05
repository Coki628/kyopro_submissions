#!/usr/bin/env python3
# usage: $ oj generate-input 'python3 generate.py'
# usage: $ oj generate-input --hack-actual=./a.out --hack-expected=./naive 'python3 generate.py'
from random import randrange, randint

def main():
    N = randint(1, 30)
    Q = randint(1, 30)
    print(N, Q)
    for _ in range(Q):
        op = randint(1, 3)
        if op == 1:
            x = randint(1, N)
            y = randint(1, N)
            print(op, x, y)
        else:
            c = randrange(2)
            if c:
                c = 'A'
            else:
                c = 'B'
            print(op, c)

if __name__ == "__main__":
    main()
