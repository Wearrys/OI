import os
from random import *

for i in range(20):
    fname = "game%d" % i

    if i < 3 :
        w = randint(1, 10)
        b = randint(1, 10)
    elif i < 10 :
        w = randint(1, 1000)
        b = randint(1, 1000)
    elif i < 13 : 
        w = b = randint(1, 100000)
    else:
        w = randint(1, 100000)
        b = randint(1, 100000)
    
    print (w, b, file = open("%s.in" % fname, "w"))
    os.system("./game < %s.in > %s.out" % (fname, fname))
