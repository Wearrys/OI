import sys, os
from random import *

def gen(l, r, s, c, d):
    global maxd
    maxd = max(maxd, d)

    if (s == 0):
        return []

    length = (r - l) // c 

    p = []
    st = l + randint(0, length)

    while (st + length <= r and s > 0):
        ed = min(st + randint(length, length + length // 2), r)
        t = randint(1, s // c + 1)
        s -= t
        p.append([st, ed, t - 1])
        st = ed + randint(1, length)

    if (len(p) < 1):
        maxd = max(maxd, d + s)
        return [[l, r - randint(0, r-l), 0] for i in range(s)]

    if (s > 0):
        p[0][2] += s

    q = []
    for x in p:
        q += gen(x[0], x[1], x[2], (c + 2) // 3, d + 1)

    return p + q

case = [5, 4, 5, 6]

nr = [[250000, 300000],
      [4000, 5000],
      [250000, 300000],
      [250000, 300000]]

mr = [[15, 20],
      [4000, 5000],
      [250000, 300000],
      [250000, 300000]]

tot = 0

for i in range(4):
    for j in range(case[i]):

        fname = "cover%d" % (tot + 1)
        tot += 1

        t = randint(1, 10 ** 9)
        n = randint(nr[i][0], nr[i][1])
        m = randint(mr[i][0], mr[i][1])
        a = [randint(1, 10 ** 9) if (i != 2) else t for x in range(m)]
        maxd = 0
        r = gen(1, n, m, max(int(m ** 0.2), 2), 0)
        shuffle(r)
        print (maxd)

        outp = "%d %d\n" % (n, m)

        for k in range(m):
            outp += "%d %d %d\n" % (r[k][0], r[k][1], a[k])

        print (outp, file = open("%s.in" % fname, "w"))
        os.system("./cover < ./%s.in > ./%s.out" % (fname, fname))
