n = 100
fen = [0]*(n+1)
def update(i,x):
    while i <= n:
        fen[i] += x
        i += i&(-i)
def partial(i):
    S = 0
    while i:
        S += fen[i]
        i -= i&(-i)
    return S
def lower_bound(target):
    i,S = 0,0
    jump = 1<<n.bit_length()
    while jump:
        i += jump
        if i > n or S+fen[i] > target: i -= jump
        else: S += fen[i]
        jump >>= 1
    return i+1

"""
update(6,1)
update(24,1)
update(24,1)
update(19,1)
for j in [0,1,2,3,4]:
    print( j, lower_bound(j) )
"""