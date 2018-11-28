import sys
from random import *

sys.stdout = open("in", "w")

n = 40
m = 500

print (n, m)

for i in range(m):
    x = randint(1, n)
    y = randint(1, n)

    if(x == y):
        print (x, y, 0)
    else:
        print (x, y, randint(0, 1000000000))

