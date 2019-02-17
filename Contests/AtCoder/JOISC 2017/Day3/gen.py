import sys
from random import *

sys.stdout = open("park.in", "w")

n = randint(100, 120)
m = randint(130, 250)

d = [0 for i in range(n)]
p = [[0 for i in range(n)] for j in range(n)]

print (1, n, m)

for i in range(1, n):
    x = i
    y = randint(max(0, i - 5), i - 1)

    d[x] += 1
    d[y] += 1
    p[x][y] = p[y][x] = 1

    print (x, y)

for i in range(m - n + 1):

    x = randint(0, n-1)
    y = randint(0, n-1)

    while (x == y or p[x][y] == 1 or d[x] >= 7 or d[y] >= 7):
        x = randint(0, n-1)
        y = randint(0, n-1)

    d[x] += 1
    d[y] += 1
    p[x][y] = p[y][x] = 1
    print (x, y)
