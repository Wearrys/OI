import os
from random import *

for i in range(10):
    fname = "time%d" % (i+1)
    n = 0
    p = []

    if (i < 3):
        n = randint(9, 12)
        p = [randint(1, n) for i in range(n)]
    elif (i < 6):
        n = randint(80000, 100000)
        p = [i+1 for i in range(n)]
        shuffle(p)
    else:
        n = randint(80000, 100000)
        p = [randint(1, n) for i in range(n)]

    outp = "%d\n" % n
    for x in p:
        outp += "%d " % x

    print (outp, file = open("%s.in" % fname, "w"))
    os.system("./time < %s.in > %s.out" % (fname, fname))
