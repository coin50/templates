MOD = 998244353
MAX = 6000
fact = [1]*(MAX+1)
for i in range(1,MAX+1): fact[i] = fact[i-1]*i%MOD
anti = [1]*(MAX+1)
anti[-1] = pow(fact[-1],-1,MOD)
for i in range(MAX-1,-1,-1): anti[i] = anti[i+1]*(i+1)%MOD
def cmb(n,k): return anti[n-k]*anti[k]%MOD*fact[n]%MOD if 0 <= k <= n else 0

#cat = [cmb(2*n,n)-cmb(2*n,n-1) for n in range(MAX//2 + 1)]
cat = [fact[2*n]*(anti[n]**2 - anti[n-1]*anti[n+1])%MOD for n in range(MAX//2 + 1)]
cat[0] = 1
