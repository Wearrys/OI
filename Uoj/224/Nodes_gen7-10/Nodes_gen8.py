import sys
import math
from decimal import *

getcontext().prec = 90
e = Decimal('2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382179')

def g(x):
    t = e ** -x
    return t * (1 + t) ** -2

def h(x):
    t = e ** -x
    return (e ** (-2 * x) - t) * (1 + t) ** -3

def solve(c):
    x = Decimal('2')
    for i in range(1000):
        x -= (g(x) - c) / h(x)
    return x

a = solve(Decimal('0.1'))
print (a)
