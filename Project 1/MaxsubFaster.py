import random
import time

random.seed(1047028)
maxn = 2147483647
def makeArray(num):
    A = [random.randint (-maxn, maxn) for i in range (num)]
    return A

def makeSubArrayStart(A):
    num = len(A)
    S = [0 for i in range(num)]
    makeSubArrayStart = time.time()
    for i in range(1, num):
        S[i] = S[i-1] + A[i]
    m = 0
    for j in range(1, num):
        for k in range(j, num):
            total = S[k] - S[j-1]
        if total>m:
             m = total
    print ("makeSubArray με n =", num, ": ", time.time() - makeSubArrayStart)
    return m

A = makeArray(1000)
print (makeSubArrayStart(A))
A = makeArray(2000)
print (makeSubArrayStart(A))
