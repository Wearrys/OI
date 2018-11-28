import sys
from random import *

sys.stdout = open("in", "w")

print (100)

lst = 0
for i in range(100):
    lst += randint(1, 1000)
    print (lst, end = ' ')
print ()
