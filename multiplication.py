MOD = 0x3b800001
W = [31]
for _ in range(22): W.append( W[-1]**2%MOD )
def dft(poly,b):
    n = 1<<b
    v = poly + [0]*(n-len(poly))
    for loop in range(1,b+1):
        nv = [0]*n
        acc = 1
        space = n>>loop
        for q in range(0,n,space):
            for r in range(space):
                nv[q+r] = (v[2*q%n + r] + acc*v[2*q%n + space + r])%MOD
            acc = acc*W[-loop]%MOD
        v = nv
    return v
def mul(a,b):
    j = (len(a)+len(b)-2).bit_length()
    A,B = dft(a,j), dft(b,j)
    inv = pow(1<<j,-1,MOD)
    C = [A[i]*B[i]*inv%MOD for i in range(1<<j)]
    D = dft(C,j)
    return D[:1] + D[:-len(a)-len(b)+1:-1]

"""
N,M = [int(t) for t in input().split()]
a = [int(t) for t in input().split()]
b = [int(t) for t in input().split()]
c = mul(a,b)
print(*c)
"""