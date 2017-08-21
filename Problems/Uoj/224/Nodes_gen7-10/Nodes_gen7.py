import sys
import math

sys.stdout = open("nodes7.out", "w")

print ("I")
print ("I")
print ("< 1 100")
print ("< 2 100")

A = 3
B = 4
lst = 4
lstans = 0

for i in range(31, -1, -1):

    print ("C", A, -(1 << (100+i)) + 1000)  # lst+1: (a << 100) - (1 << (100+i)) + 1000
    print ("S", lst+1)                      # lst+2: x 
                                            
    print ("C", B, -(1 << (100+i)) + 1000)  # lst+3: (b << 100) - (1 << (100+i)) + 1000
    print ("S", lst+3)                      # lst+4: y

    print ("+", lst+2, lst+4)               # lst+5: x + y
    print ("<", lst+5, 200)                 # lst+6: (x+y) << 200
    print ("C", lst+6, -(2 << 200) + 1000)  # lst+7: (x+y) << 200 - 2 << 200
    print ("S", lst+7)                      # lst+8: bool((x + y) >= 2)
    print ("<", lst+8, 1)                   # lst+9: x + y >= 2 ? 2 : 0
    print ("-", lst+9)                      # lst+10: - (x + y >= 2 ? 2 : 0)
    print ("+", lst+10, lst+5)              # lst+11: x + y - (x + y >= 2 ? 2 : 0)
    
    if(i < 31): 
        print("+", lstans, lst+11)          # lst+12: current_ans

    if(i == 0): 
        print("O", lst+12)                  # final_ans
        break

    lstans = lst + 12 + (i < 31)
    print("<", lstans-1, 1)                 # lstans (lst+12/13): nxt_ans

    print ("<", lst+2, 100+i)               # lstans+1: x << (i + 100) 
    print ("-", lstans+1)                   # lstans+2: deltax
    print ("+", A, lstans+2)                # lstans+3: nxt_A

    print ("<", lst+4, 100+i)               # lstans+4: y << (i + 100)
    print ("-", lstans+4)                   # lstans+5: deltay
    print ("+", B, lstans+5)                # lstans+6: nxt_B

    #print ("O", lst+3)                      # lstans+7: debug

    B = lstans+6
    A = lstans+3
    lst = lstans+6
