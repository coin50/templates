MAX = 317000
primes = []
sieve = [0]*(MAX+1)
for i in range(2,MAX+1):
    if not sieve[i]: primes.append(i)
    for p in primes:
        if i*p > MAX: break
        sieve[i*p] = p
        if not i%p: break
        
def prime_factorization(n):
    pf = []
    for p in primes:
        if n%p == 0:
            e = 0
            while n%p == 0:
                n //= p
                e += 1
            pf.append( (p,e) )
        if p*p > n:
            break
    if n > 1:
        pf.append( (n,1) )
    return pf

def divisors(n):
    divs = [1]
    for (p,e) in prime_factorization(n):
        L = len(divs)
        for _ in range(L*e):
            divs.append( divs[-L]*p )
    #divs.sort()
    return divs