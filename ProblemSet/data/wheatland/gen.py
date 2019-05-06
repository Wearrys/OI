import os
import math
from random import *

for i in range(10):
    fname = "wheatland%d" % i

    if i < 3:
        n = randint(3, 4)
        m = randint(3, 4)
    elif i < 5:
        n = randint(30, 50)
        m = randint(30, 50)
    else:
        n = randint(150, 200)
        m = randint(150, 200)

    k = randint((n+m)//3, (n+m)//2)
    outp = "%d %d %d\n" % (n, m, k)

    for j in range(n):
        d = min(j, m - 1 - j)

        if j < m - 1 - j:
            l = randint(d, m - 1)
            r = randint(l, m - 1)
        else:
            l = randint(0, m - 1 - d)
            r = randint(l, m - 1 - d)

        for t in range(m):
            if t >= l and t <= r:
                outp += '0'
            else:
                outp += '1'
        outp += "\n"

    print (outp, file = open("%s.in" % fname, "w"))

    os.system("./wheatland < %s.in > %s.out" % (fname, fname))
