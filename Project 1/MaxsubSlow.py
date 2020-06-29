import random
import time

random.seed(1047028)
maxn = 2147483647
A=[]
def makeArray(num):
    A = [random.randint (-maxn, maxn) for i in range (num)]
    return A

def makeSubArraySlowStart(A):
    num = len(A)
    m = 0
    makeSubArraySlowStart = time.time()
    for j in range(1, num):
        for k in range(1, num):
            total = 0
            for i in range(j, k+1):
                total += A[i]
            if total>m:
                m = total
    print ("makeSubArraySlow με n =", num, ": ", time.time() - makeSubArraySlowStart)
    return m

A = makeArray(1000)
print (makeSubArraySlowStart(A))
A = makeArray(2000)
print (makeSubArraySlowStart(A))
