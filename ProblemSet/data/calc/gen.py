import sys, os
from random import *

for i in range(20):
    fname = 'calc%d' % i
    p = randint(10 ** 6, 10 ** 9)

    if (i < 3):
        l = r = randint(10 ** 5, 10**7)
    elif (i < 8):
        l = randint(1, 10 ** 5)
        r = randint(l, 10 ** 5)
    elif (i < 15):
        l = 1
        r = randint(1, 10 ** 7)
    else:
        l = randint(1, 10 ** 5)
        r = randint(l, 10 ** 7)

    print (l, r, p, file = open("%s.in" % fname, "w"))
    os.system("./calc < %s.in > %s.out" % (fname, fname))
