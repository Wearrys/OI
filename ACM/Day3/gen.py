import os
from random import *
import sys

sys.stdout = open('in', 'w')

n = 100000
q = 100000

print (n)

for i in range(n):
    print (randint(1, 2 ** 62 - 1))

print (q)

for i in range(q):
    op = randint(1, 2)
    if (op == 1):
        l = randint(1, n)
        r = randint(1, 2 ** 62 - 1)
        print (op, l, r)
    else:
        l = randint(1, n)
        r = randint(l, n)
        print (op, l, r)

