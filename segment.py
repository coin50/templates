n = 100
seg = [0]*(2*n)
def update(i,x):
    seg[n+i] = x
    i = (n+i)//2
    while i:
        seg[i] = max(seg[2*i],seg[2*i+1])
        i >>= 1
def rmq(l,r):
    l += n; r += n
    m = 0
    while l < r:
        #if l&1: m = max(m,seg[l])
        #if r&1: m = max(m,seg[r-1])
        m = max(m,seg[l],seg[r-1])
        l = (l+1)//2; r = r//2
    return m

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