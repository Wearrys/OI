import os
from random import *

for i in range(10):
    
    fname = "game%d" % (i+1)

    if (i < 2):
        n = randint(5, 10)
    elif (i < 4):
        n = randint(2000, 3000)
    elif (i < 6):
        n = randint(5000, 6000)
    else:
        n = randint(80000, 100000)

    a = [randint(1, n) for i in range(n)]
    b = [randint(1, n) for i in range(n)]

    outp = "%d\n" % n
    for x in a:
        outp += "%d " % x
    outp += '\n'
    for y in b:
        outp += "%d " % y

    print (outp, file = open("%s.in" % fname, "w"))
    os.system("./game < %s.in > %s.out" % (fname, fname))
