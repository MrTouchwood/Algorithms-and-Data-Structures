import random
import time

random.seed(1047028)
maxn = 2147483647
A=[]
def makeArray(num):
    A = [random.randint (-maxn, maxn) for i in range (num)]
    return A

def makeSubArrayBest(A):
    num = len(A)
    M = [0 for x in range(num)]
    makeSubArrayBestStart = time.time()
    for t in range(1, num):
        M[t] = max(0, M[t-1] + A[t])
    m = 0
    for t in range(1, num):
    	m = max(m, M[t])
    print ("makeSubArrayBest με n =", num, ": ", time.time() - makeSubArrayBestStart)
    return m

A = makeArray(1000)
print (makeSubArrayBest(A))
A = makeArray(2000)
print (makeSubArrayBest(A))
