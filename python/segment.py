n = 100
def f(a,b):
    return max(a,b)
default = 0
seg = [default]*(2*n)

def update(i,x):
    seg[i+n] = x
    i = (i+n)//2
    while i:
        seg[i] = f(seg[2*i],seg[2*i+1])
        i >>= 1
def rmq(l,r):
    l += n; r += n
    m1 = m2 = default
    while l < r:
        if l&1: m1 = f(m1,seg[l])
        if r&1: m2 = f(seg[r-1],m2)
        l = (l+1)//2; r = r//2
    return f(m1,m2)

"""
update(67,3)
update(71,2)
update(45,6)
print( rmq(66,68) )
print( rmq(66,99) )
print( rmq(46,66) )
print( rmq(20,90) )
print( rmq(67,71) )
print( rmq(68,71) )
print( rmq(68,72) )
"""