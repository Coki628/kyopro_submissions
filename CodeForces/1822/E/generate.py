#!/usr/bin/env python3
# usage: $ oj generate-input 'python3 generate.py'
# usage: $ oj generate-input --hack-actual=./a.out --hack-expected=./naive 'python3 generate.py'
import random

# generated by oj-template v4.8.1 (https://github.com/online-judge-tools/template-generator)
def main():
    testcases = random.randint(1, 1)  # TODO: edit here
    a = [None for _ in range(testcases)]
    b = [None for _ in range(testcases)]
    for i in range(testcases):
        a[i] = random.randint(4, 8)  # TODO: edit here
        b[i] = ''.join([random.choice('abcdefgh') for _ in range(a[i])])  # TODO: edit here
    print(testcases)
    for i in range(testcases):
        print(a[i])
        print(b[i])

if __name__ == "__main__":
    main()
